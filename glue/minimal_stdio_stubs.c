/*
 * Minimal stdio stubs - avoiding all header conflicts
 * Provides only the essential symbols needed for FreeBSD libc
 */

#include <stddef.h>
#include <uk/essentials.h>

/* Threading stubs */
int __isthreaded = 0;

/* Simplified FILE structure */
struct __sFILE {
    char dummy[128];  /* Opaque structure, don't need real implementation */
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

/* Basic I/O stub */
int __sfvwrite(void *fp, void *uio)
{
    /* No-op for now */
    return -1;
}