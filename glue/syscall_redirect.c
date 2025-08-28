/*
 * FreeBSD libc to Unikraft Syscall Redirection Layer
 * 
 * This file redirects FreeBSD libc internal calls to Unikraft's syscall layer
 * instead of trying to override standard library functions.
 */

/* Completely self-contained definitions */
typedef unsigned long size_t;
typedef long ssize_t;
typedef int pid_t;

/* FILE type definition for stdio redirection */
typedef struct FILE {
    int fd;
    /* Minimal FILE structure for identification */
} FILE;

/* Standard definitions */
#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef EOF
#define EOF (-1)
#endif

/* Forward declarations to avoid complex includes */
extern long uk_syscall_r_write(int fd, const void *buf, size_t count);
extern int _uk_vprintk(int level, const char *libname, const char *srcname, unsigned int srcline, const char *fmt, __builtin_va_list ap);

/* Simple strlen implementation to avoid dependencies - implemented inline */
static inline size_t strlen(const char *s)
{
    size_t len = 0;
    if (!s) return 0;
    while (s[len]) len++;
    return len;
}

/* Global errno variable */
int errno = 0;

/* ============================================================================
 * ERRNO REDIRECTION - FreeBSD __error() to Unikraft errno
 * ============================================================================ */

int *__error(void)
{
    /* Redirect to Unikraft's errno location */
    return &errno;
}

/* ============================================================================  
 * LOCALE STUBS - Minimal for printf formatting
 * ============================================================================ */

/* Simple global locale structure */
struct __locale_t {
    int dummy;
};

static struct __locale_t global_locale = { 0 };

struct __locale_t *__xlocale_global_locale = &global_locale;
struct __locale_t *__xlocale_C_locale = &global_locale;  /* C locale same as global */
int __has_thread_locale = 0;
/* Use __thread for TLS consistency with FreeBSD expectations */
__thread struct __locale_t *__thread_locale = NULL;

/* ============================================================================
 * WRITE SYSCALL REDIRECTION - FreeBSD stdio to Unikraft VFS
 * ============================================================================ */

/* FreeBSD printf internally calls this for stdout/stderr */
long __sys_write(int fd, const void *buf, size_t count)
{
    /* Redirect to Unikraft syscall */
    return uk_syscall_r_write(fd, buf, count);
}

/* Alternative write interface that FreeBSD might use */
ssize_t write(int fd, const void *buf, size_t count)
{
    long result = uk_syscall_r_write(fd, buf, count);
    return (ssize_t)result;
}

/* Additional system calls needed for linking */
extern long uk_syscall_r_fstat(int fd, void *statbuf);
extern long uk_syscall_r_utimes(const char *pathname, const void *times);

int fstat(int fd, void *statbuf)
{
    long result = uk_syscall_r_fstat(fd, statbuf);
    return (int)result;
}

int utimes(const char *pathname, const void *times)
{
    long result = uk_syscall_r_utimes(pathname, times);
    return (int)result;
}

/* Additional system call stubs */
extern long uk_syscall_r_close(int fd);
extern long uk_syscall_r_futimesat(int dirfd, const char *pathname, const void *times);

int close(int fd)
{
    long result = uk_syscall_r_close(fd);
    return (int)result;
}

int futimesat(int dirfd, const char *pathname, const void *times)
{
    long result = uk_syscall_r_futimesat(dirfd, pathname, times);
    return (int)result;
}

/* qsort stub - not functional but allows linking */
void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    (void)base;
    (void)nmemb; 
    (void)size;
    (void)compar;
    /* Simple stub - not functional */
}

/* String function stubs */
char *strdup(const char *s)
{
    (void)s;
    return NULL; /* Simple stub - not functional */
}

int asprintf(char **strp, const char *fmt, ...)
{
    (void)strp;
    (void)fmt;
    return -1; /* Simple stub - not functional */
}

char *strndup(const char *s, size_t n)
{
    (void)s;
    (void)n;
    return NULL; /* Simple stub - not functional */
}

/* Standard stream definitions */
static FILE _stdout = {1}; /* stdout -> fd 1 */
static FILE _stderr = {2}; /* stderr -> fd 2 */

FILE *stdout = &_stdout;
FILE *stderr = &_stderr;

/* stdio function stub - use our FILE definition */
int vfprintf(FILE *stream, const char *format, __builtin_va_list ap)
{
    /* For stdout/stderr, use Unikraft's printing */
    if (stream == stdout || stream == stderr || stream == (FILE*)1 || stream == (FILE*)2) {
        return _uk_vprintk(6, "freebsd-libc", "syscall", 0, format, ap); /* KLVL_INFO = 6 */
    }
    
    /* For other streams, not supported yet */
    return -1;
}

/* ============================================================================
 * LOCALE STUBS - Minimal character type support
 * ============================================================================ */

/* Simple locale structure stubs */
static int dummy_rune_locale = 0;
__thread void *_ThreadRuneLocale = &dummy_rune_locale;
void *_CurrentRuneLocale = &dummy_rune_locale;

/* ============================================================================
 * STRING CONVERSION STUBS - Minimal for printf dependencies  
 * ============================================================================ */

long strtol(const char *nptr, char **endptr, int base)
{
    /* Minimal implementation for printf %d support */
    long result = 0;
    int negative = 0;
    
    if (!nptr) return 0;
    
    /* Skip whitespace */
    while (*nptr == ' ' || *nptr == '	') nptr++;
    
    /* Handle sign */
    if (*nptr == '-') {
        negative = 1;
        nptr++;
    } else if (*nptr == '+') {
        nptr++;
    }
    
    /* Convert decimal digits only (ignore base for simplicity) */
    while (*nptr >= '0' && *nptr <= '9') {
        result = result * 10 + (*nptr - '0');
        nptr++;
    }
    
    if (endptr) *endptr = (char*)nptr;
    return negative ? -result : result;
}

/* Locale-aware version - ignore locale for unikernel */
long strtol_l(const char *nptr, char **endptr, int base, void *locale)
{
    return strtol(nptr, endptr, base);
}

/* ============================================================================
 * STDIO FUNCTION REDIRECTIONS - FreeBSD stdio to Unikraft printing
 * ============================================================================ */

/* Forward declarations for Unikraft printing functions */
extern int uk_printk(const char *fmt, ...);
extern int uk_printd(const char *fmt, ...);

/* stdout and stderr already defined above */

/* Forward declaration */
int __vfprintf(FILE *stream, const char *format, __builtin_va_list ap);

/* Core vfprintf implementation - redirect to Unikraft print for stdout/stderr */
int __vfprintf(FILE *stream, const char *format, __builtin_va_list ap)
{
    /* For stdout/stderr, use Unikraft's printing */
    if (stream == stdout || stream == stderr || stream == (FILE*)1 || stream == (FILE*)2) {
        return _uk_vprintk(6, "freebsd-libc", "syscall", 0, format, ap); /* KLVL_INFO = 6 */
    }
    
    /* For other streams, not supported yet */
    return -1;
}

/* ============================================================================
 * PUTS FUNCTION - Simple implementation for original hello.c compatibility
 * ============================================================================ */

/* Simple puts implementation that works with original hello.c */
int puts(const char *s)
{
    if (!s) return EOF;
    
    /* Simple implementation: write to file descriptor 1 (stdout) */
    write(1, s, strlen(s));
    write(1, "\n", 1);
    return 1; /* Success - return non-negative value */
}

/* Alternative puts implementation for completeness */
int fputs(const char *s, FILE *stream)
{
    if (!s || !stream) return EOF;
    
    /* For stdout/stderr, write to appropriate file descriptor */
    if (stream == stdout || stream == stderr || stream == (FILE*)1 || stream == (FILE*)2) {
        int fd = (stream == stderr || stream == (FILE*)2) ? 2 : 1;
        write(fd, s, strlen(s));
        return 1; /* Success */
    }
    
    /* For other streams, not supported yet */
    return EOF;
}

/* strlen implementation provided above as inline function */

/* ============================================================================
 * ADDITIONAL STDIO FUNCTIONS - Required by Unikraft core libraries
 * ============================================================================ */

/* FreeBSD-style stdout variant */
FILE *__stdoutp = &_stdout;

/* String error function */
char *strerror(int errnum)
{
    static char error_msg[64];
    static char unknown_msg[] = "Unknown error";
    
    switch (errnum) {
        case 0: return "Success";
        case 1: return "Operation not permitted";  
        case 2: return "No such file or directory";
        case 12: return "Out of memory";
        case 22: return "Invalid argument";
        default:
            return unknown_msg;
    }
}

/* Formatted string printing functions */
int vsnprintf(char *str, size_t size, const char *format, __builtin_va_list ap)
{
    /* Simple stub - not fully functional but allows linking */
    (void)str; (void)size; (void)format; (void)ap;
    return 0; /* Return 0 to indicate no characters written */
}

int fprintf(FILE *stream, const char *format, ...)
{
    __builtin_va_list ap;
    __builtin_va_start(ap, format);
    int ret = vfprintf(stream, format, ap);
    __builtin_va_end(ap);
    return ret;
}

/* File buffer flush function */
int fflush(FILE *stream)
{
    /* Simple stub - no buffering in our minimal implementation */
    (void)stream;
    return 0; /* Success */
}

/* File write function */
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    if (!ptr || !stream) return 0;
    
    /* For stdout/stderr, write to appropriate file descriptor */
    if (stream == stdout || stream == stderr || stream == (FILE*)1 || stream == (FILE*)2) {
        int fd = (stream == stderr || stream == (FILE*)2) ? 2 : 1;
        ssize_t written = write(fd, ptr, size * nmemb);
        return (written > 0) ? (written / size) : 0;
    }
    
    return 0; /* Not supported for other streams */
}

/* ============================================================================
 * MULTIBYTE CHARACTER SUPPORT - Required by ctype functions
 * ============================================================================ */

/* Multibyte character limit - simple stub */
int __mb_sb_limit = 1; /* Single-byte limit for C locale */

/* ============================================================================
 * MEMORY ALLOCATION STUBS - Minimal implementation for linking
 * Note: hello.c doesn't use malloc/free, but other libraries might need them
 * ============================================================================ */

/* Simple memory allocation stubs - not functional but allows linking */
void *malloc(size_t size)
{
    (void)size;
    return NULL; /* Simple stub - not functional */
}

void free(void *ptr)
{
    (void)ptr;   /* Simple stub - not functional */
}

void *calloc(size_t nmemb, size_t size)
{
    (void)nmemb;
    (void)size;
    return NULL; /* Simple stub - not functional */
}

void *realloc(void *ptr, size_t size)
{
    (void)ptr;
    (void)size;
    return NULL; /* Simple stub - not functional */
}
