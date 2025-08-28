/*
 * Standard I/O stubs for FreeBSD libc compatibility
 * Provides minimal stdio infrastructure for Unikraft
 */

#include <stddef.h>
#include <stdarg.h>
#include <uk/essentials.h>

/* Forward declarations to avoid header conflicts */
typedef struct __sFILE FILE;

struct __siov {
    void *iov_base;
    size_t iov_len;
};

struct __suio {
    struct __siov *uio_iov;
    int uio_iovcnt;
    int uio_resid;
};

/* FILE structure simplified for Unikraft */
struct __sFILE {
    unsigned char *_p;
    int _r;
    int _w;
    short _flags;
    short _file;
};

/* Global file handles - simplified implementation */
FILE __sF[3] = {
    [0] = { ._p = NULL, ._r = 0, ._w = 0, ._flags = 0, ._file = 0 },  /* stdin */
    [1] = { ._p = NULL, ._r = 0, ._w = 0, ._flags = 0, ._file = 1 },  /* stdout */
    [2] = { ._p = NULL, ._r = 0, ._w = 0, ._flags = 0, ._file = 2 }   /* stderr */
};

FILE *__stdoutp = &__sF[1];  /* stdout pointer */
FILE *__stderrp = &__sF[2];  /* stderr pointer */
FILE *__stdinp = &__sF[0];   /* stdin pointer */

/* Threading support stubs */
int __isthreaded = 0;  /* Single-threaded for now */

void _flockfile(FILE *fp __unused)
{
    /* No-op for single-threaded environment */
}

void __stdio_cancel_cleanup(void *arg __unused)
{
    /* No-op cleanup function */
}

void ___pthread_cleanup_push_imp(void (*routine)(void *), void *arg, void *cleanup_info)
{
    /* No-op pthread cleanup for unikernel */
}

void ___pthread_cleanup_pop_imp(int execute)
{
    /* No-op pthread cleanup for unikernel */
}

/* Basic I/O operations */
int __sfvwrite(FILE *fp, const struct __suio *uio)
{
    /* Simple implementation that writes to console */
    const struct __siov *iov;
    int ret = 0;
    
    if (!fp || !uio) {
        return -1;
    }
    
    for (int i = 0; i < uio->uio_iovcnt; i++) {
        iov = &uio->uio_iov[i];
        if (iov->iov_base && iov->iov_len > 0) {
            /* For now, just use uk_printd for console output */
            for (size_t j = 0; j < iov->iov_len; j++) {
                uk_printd(NULL, "%c", ((const char*)iov->iov_base)[j]);
            }
            ret += iov->iov_len;
        }
    }
    
    return ret;
}

int fflush(FILE *stream __unused)
{
    /* No-op for unikernel console output */
    return 0;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    if (!ptr || size == 0 || nmemb == 0) {
        return 0;
    }
    
    /* Simple console output */
    const char *buf = (const char *)ptr;
    size_t total = size * nmemb;
    
    for (size_t i = 0; i < total; i++) {
        uk_printd(NULL, "%c", buf[i]);
    }
    
    return nmemb;
}

/* Printf implementation using existing vfprintf functionality */
int vfprintf(FILE *stream, const char *format, va_list ap)
{
    /* This should be implemented by FreeBSD's vfprintf - adding stub */
    return __vfprintf(format, ap);
}

int vfprintf_l(FILE *stream, void *locale, const char *format, va_list ap)
{
    /* Ignore locale for now */
    return vfprintf(stream, format, ap);
}

int __vfprintf(const char *format, va_list ap)
{
    /* Use uk_vsnprintf for formatting then output */
    char buf[1024];  /* Stack buffer for formatted output */
    int ret = vsnprintf(buf, sizeof(buf), format, ap);
    
    if (ret > 0 && ret < (int)sizeof(buf)) {
        for (int i = 0; i < ret; i++) {
            uk_printd(NULL, "%c", buf[i]);
        }
    }
    
    return ret;
}