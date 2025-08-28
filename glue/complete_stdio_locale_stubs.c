/*
 * Complete stdio and locale stubs for FreeBSD libc compatibility
 * Provides ALL missing symbols needed for c-hello to build successfully
 */

#include <stddef.h>
#include <stdarg.h>
#include <uk/essentials.h>

/* ===== STDIO STUBS ===== */

/* Threading stubs */
int __isthreaded = 0;

/* Simplified FILE structure */
struct __sFILE {
    char dummy[128];  /* Opaque structure */
};

/* Global file handles */
struct __sFILE __sF[3];
struct __sFILE *__stdoutp = &__sF[1];

/* Thread locking stubs */
void _flockfile(void *fp)
{
    /* No-op for single-threaded unikernel */
}

void __stdio_cancel_cleanup(void *arg)
{
    /* No-op */
}

void ___pthread_cleanup_push_imp(void *routine, void *arg, void *cleanup_info)
{
    /* No-op */
}

void ___pthread_cleanup_pop_imp(int execute)
{
    /* No-op */
}

/* Basic I/O stub - simplified implementation */
int __sfvwrite(void *fp, void *uio)
{
    /* Simple stub - for puts() we just need to return success */
    return 0;
}

/* ===== LOCALE STUBS ===== */

/* Global locale structures - opaque pointers */
void *__xlocale_C_locale = (void*)0x1;
void *__xlocale_global_locale = (void*)0x2;

/* Thread-local locale support - disabled for unikernel */
int __has_thread_locale = 0;
__thread void *__thread_locale = (void*)0;  /* TLS variable */

/* Current rune locale pointer - simple stub */
void *_CurrentRuneLocale = (void*)0;

/* ===== ADDITIONAL STDIO FUNCTIONS ===== */

/* Simple puts implementation to replace FreeBSD's complex version */
int puts(const char *s)
{
    if (!s) return -1;
    
    /* Simple console output using uk_printd */
    while (*s) {
        uk_printd(NULL, "%c", *s);
        s++;
    }
    uk_printd(NULL, "\n");  /* puts() adds newline */
    
    return 1;  /* Non-negative on success */
}

/* Basic printf implementations */
int printf(const char *format, ...)
{
    va_list args;
    char buf[1024];
    int ret;
    
    va_start(args, format);
    ret = vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);
    
    if (ret > 0 && ret < (int)sizeof(buf)) {
        /* Output to console */
        for (int i = 0; i < ret; i++) {
            uk_printd(NULL, "%c", buf[i]);
        }
    }
    
    return ret;
}