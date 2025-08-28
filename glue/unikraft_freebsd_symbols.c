/*
 * Complete FreeBSD libc symbol definitions for Unikraft
 * This file provides ALL symbols needed by FreeBSD libc code to link successfully
 */

#include <stddef.h>
#include <stdarg.h>
#include <uk/essentials.h>
#include <uk/print.h>

/* ==== STDIO SYMBOLS ==== */

/* Threading support */
int __isthreaded = 0;

/* FILE structure - simplified for embedded use */
typedef struct {
    unsigned char *_p;
    int _r, _w;
    short _flags, _file;
    char _bf[1];
    int _lbfsize;
    void *_cookie;
    int (*_close)(void *);
    int (*_read)(void *, char *, int);
    int (*_seek)(void *, long, int);
    int (*_write)(void *, const char *, int);
    char _ub[1];
    char _up[1];
    int _ur;
    unsigned char _ubuf[3];
    unsigned char _nbuf[1];
    void *_lb;
    int _blksize;
    long _offset;
} FILE;

/* Standard file pointers */
static FILE __stdin_file = {0};
static FILE __stdout_file = {0};  
static FILE __stderr_file = {0};

FILE __sF[3] = {
    [0] = __stdin_file,   /* stdin */
    [1] = __stdout_file,  /* stdout */
    [2] = __stderr_file   /* stderr */
};

FILE *__stdoutp = &__sF[1];
FILE *__stderrp = &__sF[2];
FILE *__stdinp = &__sF[0];

/* Thread locking functions - no-ops for unikernel */
void _flockfile(FILE *fp) { /* no-op */ }
void _funlockfile(FILE *fp) { /* no-op */ }
void __stdio_cancel_cleanup(void *arg) { /* no-op */ }
void ___pthread_cleanup_push_imp(void (*routine)(void *), void *arg, void *cleanup_info) { /* no-op */ }
void ___pthread_cleanup_pop_imp(int execute) { /* no-op */ }

/* Simple I/O operations */
int __sfvwrite(FILE *fp, const void *uio) 
{
    /* Simple success return for puts() */
    return 0;
}

int fflush(FILE *stream)
{
    return 0; /* Success */
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    if (!ptr || size == 0 || nmemb == 0) return 0;
    
    const char *buf = (const char *)ptr;
    size_t total = size * nmemb;
    
    /* Output to console using uk_printd */
    for (size_t i = 0; i < total; i++) {
        uk_printd(uk_pr_debug, "%c", buf[i]);
    }
    
    return nmemb;
}

/* ==== LOCALE SYMBOLS ==== */

/* Locale structures - opaque implementations */
static char __xlocale_c_locale_data[64] = {0};
static char __xlocale_global_locale_data[64] = {0};

void *__xlocale_C_locale = (void*)__xlocale_c_locale_data;
void *__xlocale_global_locale = (void*)__xlocale_global_locale_data;

/* Thread-local locale support - disabled */
int __has_thread_locale = 0;
__thread void *__thread_locale = NULL;

/* Rune locale support */
static char _default_rune_locale_data[64] = {0};
void *_CurrentRuneLocale = (void*)_default_rune_locale_data;

/* ==== STRING FUNCTIONS ==== */

char *strchr(const char *s, int c)
{
    while (*s != '\0') {
        if (*s == c) return (char *)s;
        s++;
    }
    return (c == '\0') ? (char *)s : NULL;
}

char *strerror(int errnum)
{
    static const char *errors[] = {
        "Success",
        "Operation not permitted",
        "No such file or directory",
        "No such process",
        "Interrupted system call",
        "I/O error"
    };
    
    if (errnum >= 0 && errnum < 6) {
        return (char*)errors[errnum];
    }
    return (char*)"Unknown error";
}

/* ==== MEMORY FUNCTIONS ==== */

void *malloc(size_t size)
{
    return uk_malloc(uk_alloc_get_default(), size);
}

void free(void *ptr)
{
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

char *strdup(const char *s)
{
    size_t len = strlen(s) + 1;
    char *dup = malloc(len);
    if (dup) memcpy(dup, s, len);
    return dup;
}

char *strndup(const char *s, size_t n)
{
    size_t len = strnlen(s, n);
    char *dup = malloc(len + 1);
    if (dup) {
        memcpy(dup, s, len);
        dup[len] = '\0';
    }
    return dup;
}

/* ==== ERROR HANDLING ==== */

int *__error(void)
{
    return &errno;
}

/* ==== VFS STUBS ==== */

int fstat(int fd, void *buf)
{
    errno = ENOSYS;
    return -1;
}

int close(int fd)
{
    return 0; /* Simple success */
}

int utimes(const char *path, const void *times)
{
    return 0; /* Simple success */
}

/* ==== REPLACEMENT STDIO FUNCTIONS ==== */

/* Simple puts implementation to replace FreeBSD's complex version */
int puts(const char *s)
{
    if (!s) return EOF;
    
    uk_printk("%s\n", s);  /* Use uk_printk for console output */
    
    return 1;  /* Success */
}

int printf(const char *format, ...)
{
    va_list args;
    int ret;
    
    va_start(args, format);
    ret = uk_vsnprintf(NULL, 0, format, args);  /* Get length */
    va_end(args);
    
    if (ret > 0) {
        va_start(args, format);
        uk_vprintk(format, args);  /* Actually print */
        va_end(args);
    }
    
    return ret;
}

/* Stub implementations for functions that might be called but aren't critical */
int asprintf(char **strp, const char *fmt, ...)
{
    *strp = NULL;
    errno = ENOSYS;
    return -1;
}

int vfprintf(FILE *stream, const char *format, va_list ap)
{
    return uk_vprintk(format, ap);
}

int __vfprintf(const char *format, va_list ap)
{
    return uk_vprintk(format, ap);
}

int vfprintf_l(FILE *stream, void *locale, const char *format, va_list ap)
{
    return uk_vprintk(format, ap);
}