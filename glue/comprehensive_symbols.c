/*
 * Comprehensive symbol definitions for FreeBSD libc compatibility
 * Provides all missing symbols needed for c-hello application
 *
 * This file bridges FreeBSD libc functions to Unikraft services
 */

#include <stdio.h>      /* EOF, vsnprintf, snprintf */
#include <stdarg.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <errno.h>

#include <uk/print.h>    /* uk_printk, uk_vprintk, KLVL_* */
#include <uk/alloc.h>    /* uk_malloc/free/... */
#include <uk/essentials.h>

#include "freebsd_compat.h"
#include <sys/cdefs.h>
...

/* ============================================================================
 * MEMORY ALLOCATION FUNCTIONS - Bridge to Unikraft allocator
 * ============================================================================ */

void *malloc(size_t size)
{
    return uk_malloc(uk_alloc_get_default(), size);
}

void free(void *ptr)
{
    if (ptr)
        uk_free(uk_alloc_get_default(), ptr);
}

void *calloc(size_t nmemb, size_t size)
{
    return uk_calloc(uk_alloc_get_default(), nmemb, size);
}

void *realloc(void *ptr, size_t size)
{
    return uk_realloc(uk_alloc_get_default(), ptr, size);
}

/* ============================================================================
 * STRING UTILITY FUNCTIONS - Missing from FreeBSD string collection
 * ============================================================================ */

char *strdup(const char *s)
{
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char *result = malloc(len);
    if (result)
        memcpy(result, s, len);
    return result;
}

char *strndup(const char *s, size_t n)
{
    if (!s) return NULL;
    size_t len = strlen(s);
    if (len > n) len = n;
    char *result = malloc(len + 1);
    if (result) {
        memcpy(result, s, len);
        result[len] = '\0';
    }
    return result;
}

/* Simple asprintf implementation (fixed-size buffer) */
int asprintf(char **strp, const char *fmt, ...)
{
    va_list ap;
    int ret;

    if (!strp || !fmt) {
        errno = EINVAL;
        return -1;
    }

    /* Trivial implementation: 1 KiB temp buffer */
    *strp = malloc(1024);
    if (!*strp) {
        errno = ENOMEM;
        return -1;
    }

    va_start(ap, fmt);
    ret = vsnprintf(*strp, 1024, fmt, ap);
    va_end(ap);

    if (ret < 0) {
        free(*strp);
        *strp = NULL;
        return -1;
    }

    return ret;
}

/* ============================================================================
 * ERRNO ACCESS FUNCTION - Bridge to FreeBSD's __error()
 * ============================================================================ */

int *__error(void)
{
    /* NOTE: Real implementations are TLS-based; this stub suffices here. */
    return &errno;
}

/* ============================================================================
 * BASIC STDIO FUNCTIONS - Routed to uk_printk/uk_vprintk
 * ============================================================================ */

/* FreeBSD libc exposes these globals for std{in,out,err} */
void *__stdoutp = (void *)0x1;
void *__stderrp = (void *)0x2;
void *__stdinp  = (void *)0x3;

/* Choose printk level from "stream" placeholder */
static inline int __stream_lvl(void *stream)
{
    return (stream == __stderrp) ? KLVL_ERR : KLVL_INFO;
}

int puts(const char *s)
{
    if (!s) {
        errno = EINVAL;
        return EOF;
    }
    uk_printk(KLVL_INFO, "%s\n", s);
    /* C puts() returns nonnegative on success; return last byte written count is fine */
    return (int)strlen(s) + 1; /* including newline */
}

/* Minimal fwrite: only handles stdout/stderr placeholders */
size_t fwrite(const void *ptr, size_t size, size_t nmemb, void *stream)
{
    if (!ptr || size == 0 || nmemb == 0)
        return 0;

    size_t total = size * nmemb;
    int lvl = __stream_lvl(stream);

    /* uk_printk supports %.*s; print in one shot for efficiency */
    uk_printk(lvl, "%.*s", (int)total, (const char *)ptr);
    return nmemb;
}

int fprintf(void *stream, const char *format, ...)
{
    if (!format) {
        errno = EINVAL;
        return -1;
    }

    va_list args;
    va_start(args, format);
    int ret = uk_vprintk(__stream_lvl(stream), format, args);
    va_end(args);
    return ret;
}

int vfprintf(void *stream, const char *format, va_list ap)
{
    if (!format) {
        errno = EINVAL;
        return -1;
    }
    return uk_vprintk(__stream_lvl(stream), format, ap);
}

/* FreeBSD aliases that some components reference */
int __vfprintf(void *stream, const char *format, va_list ap)
{
    return vfprintf(stream, format, ap);
}

int vfprintf_l(void *stream, void *locale, const char *format, va_list ap)
{
    (void)locale; /* locale ignored */
    return vfprintf(stream, format, ap);
}

int fflush(void *stream)
{
    (void)stream; /* uk_printk is synchronous; nothing to flush */
    return 0;
}

/* ============================================================================
 * FREEBSD INTERNAL SYMBOLS - Stubs for FreeBSD libc internals
 * ============================================================================ */

/* Threading stubs */
int __isthreaded = 0;

/* Locale stubs */
void *_ThreadRuneLocale = NULL;
int __mb_sb_limit = 256;

void *__xlocale_C_locale = (void *)0x10;
void *__xlocale_global_locale = (void *)0x11;
int __has_thread_locale = 0;
__thread void *__thread_locale = NULL;
void *_CurrentRuneLocale = (void *)0x12;

/* File locking stubs (no-ops) */
void _flockfile(void *fp)   { (void)fp; }
void _funlockfile(void *fp) { (void)fp; }
void __stdio_cancel_cleanup(void *arg) { (void)arg; }

/* Pthread cleanup stubs */
void ___pthread_cleanup_push_imp(void *routine, void *arg, void *cleanup_info)
{
    (void)routine; (void)arg; (void)cleanup_info;
}
void ___pthread_cleanup_pop_imp(int execute) { (void)execute; }

/* Backend write helper used by some FreeBSD stdio paths (stub) */
int __sfvwrite(void *fp, void *uio)
{
    (void)fp; (void)uio;
    return 0;
}

/* ============================================================================
 * STRING CONVERSION FUNCTIONS - Required by FreeBSD stdlib
 * ============================================================================ */

long strtol(const char *nptr, char **endptr, int base)
{
    if (!nptr) {
        errno = EINVAL;
        return 0;
    }

    while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n')
        nptr++;

    int sign = 1;
    if (*nptr == '-') { sign = -1; nptr++; }
    else if (*nptr == '+') { nptr++; }

    if (base == 0) {
        if (*nptr == '0') {
            nptr++;
            if (*nptr == 'x' || *nptr == 'X') { base = 16; nptr++; }
            else base = 8;
        } else base = 10;
    } else if (base == 16 && *nptr == '0' && (nptr[1] == 'x' || nptr[1] == 'X')) {
        nptr += 2;
    }

    long result = 0;
    while (*nptr) {
        int digit;
        if (*nptr >= '0' && *nptr <= '9') digit = *nptr - '0';
        else if (*nptr >= 'a' && *nptr <= 'f') digit = *nptr - 'a' + 10;
        else if (*nptr >= 'A' && *nptr <= 'F') digit = *nptr - 'A' + 10;
        else break;

        if (digit >= base) break;
        result = result * base + digit;
        nptr++;
    }

    if (endptr) *endptr = (char *)nptr;
    return sign * result;
}

long strtol_l(const char *nptr, char **endptr, int base, void *locale)
{
    (void)locale;
    return strtol(nptr, endptr, base);
}

char *strerror(int errnum)
{
    static char error_buf[64];

    switch (errnum) {
    case 0: return (char *)"Success";
    case EPERM: return (char *)"Operation not permitted";
    case ENOENT: return (char *)"No such file or directory";
    case ESRCH: return (char *)"No such process";
    case EINTR: return (char *)"Interrupted system call";
    case EIO: return (char *)"I/O error";
    case ENXIO: return (char *)"No such device or address";
    case E2BIG: return (char *)"Argument list too long";
    case ENOEXEC: return (char *)"Exec format error";
    case EBADF: return (char *)"Bad file number";
    case ECHILD: return (char *)"No child processes";
    case EAGAIN: return (char *)"Try again";
    case ENOMEM: return (char *)"Out of memory";
    case EACCES: return (char *)"Permission denied";
    case EFAULT: return (char *)"Bad address";
    case EBUSY: return (char *)"Device or resource busy";
    case EEXIST: return (char *)"File exists";
    case EXDEV: return (char *)"Cross-device link";
    case ENODEV: return (char *)"No such device";
    case ENOTDIR: return (char *)"Not a directory";
    case EISDIR: return (char *)"Is a directory";
    case EINVAL: return (char *)"Invalid argument";
    case ENFILE: return (char *)"File table overflow";
    case EMFILE: return (char *)"Too many open files";
    case ENOTTY: return (char *)"Not a typewriter";
    case ETXTBSY: return (char *)"Text file busy";
    case EFBIG: return (char *)"File too large";
    case ENOSPC: return (char *)"No space left on device";
    case ESPIPE: return (char *)"Illegal seek";
    case EROFS: return (char *)"Read-only file system";
    case EMLINK: return (char *)"Too many links";
    case EPIPE: return (char *)"Broken pipe";
    case EDOM: return (char *)"Math argument out of domain of func";
    case ERANGE: return (char *)"Math result not representable";
    default:
        snprintf(error_buf, sizeof(error_buf), "Unknown error %d", errnum);
        return error_buf;
    }
}

/* ============================================================================
 * FILE SYSTEM STUBS - Basic implementations for VFS integration
 * ============================================================================ */

int fstat(int fd, void *buf)
{
    (void)fd; (void)buf;
    errno = ENOSYS;
    return -1;
}

int close(int fd)
{
    (void)fd;
    errno = ENOSYS;
    return -1;
}

int futimesat(int fd, const char *path, const void *times)
{
    (void)fd; (void)path; (void)times;
    errno = ENOSYS;
    return -1;
}

int utimes(const char *filename, const void *times)
{
    (void)filename; (void)times;
    errno = ENOSYS;
    return -1;
}
