/*
 * Simple locale stubs - avoiding all header conflicts
 * Provides only essential locale symbols for FreeBSD libc
 */

/* Global locale structures - opaque pointers */
void *__xlocale_C_locale = (void*)0x1;
void *__xlocale_global_locale = (void*)0x2;

/* Thread-local locale support - disabled for unikernel */
int __has_thread_locale = 0;
__thread void *__thread_locale = (void*)0;  /* Fix TLS conflict - must be __thread */

/* Current rune locale pointer - simple stub */
void *_CurrentRuneLocale = (void*)0;