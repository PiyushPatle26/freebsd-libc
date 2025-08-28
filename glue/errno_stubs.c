/*
 * Errno stubs for FreeBSD libc compatibility
 * Provides __error function using Unikraft's errno
 */

#include <errno.h>
#include <uk/essentials.h>

/* FreeBSD's errno accessor function */
int *__error(void)
{
    return &errno;
}