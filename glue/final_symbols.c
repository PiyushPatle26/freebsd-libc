/*
 * Final symbol definitions for FreeBSD libc compatibility
 * Minimal implementation with explicit external linkage
 */

#include <uk/print.h>

/* STDIO symbols with explicit external linkage */
extern int __isthreaded;
extern void *__stdoutp;
extern void _flockfile(void *fp);
extern void __stdio_cancel_cleanup(void *arg);
extern void ___pthread_cleanup_push_imp(void *routine, void *arg, void *cleanup_info);
extern void ___pthread_cleanup_pop_imp(int execute);
extern int __sfvwrite(void *fp, void *uio);

/* LOCALE symbols with explicit external linkage */
extern void *__xlocale_C_locale;
extern void *__xlocale_global_locale;
extern int __has_thread_locale;
extern __thread void *__thread_locale;
extern void *_CurrentRuneLocale;

/* IMPLEMENTATIONS */
int __isthreaded = 0;
void *__stdoutp = (void*)0x1;
void _flockfile(void *fp) { }
void __stdio_cancel_cleanup(void *arg) { }
void ___pthread_cleanup_push_imp(void *routine, void *arg, void *cleanup_info) { }
void ___pthread_cleanup_pop_imp(int execute) { }
int __sfvwrite(void *fp, void *uio) { return 0; }

void *__xlocale_C_locale = (void*)0x2;
void *__xlocale_global_locale = (void*)0x3;  
int __has_thread_locale = 0;
__thread void *__thread_locale = (void*)0;
void *_CurrentRuneLocale = (void*)0x4;

/* REPLACEMENT FUNCTIONS */
int puts(const char *s)
{
    if (!s) return -1;
    uk_printk("%s\n", s);
    return 1;
}

