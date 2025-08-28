/*
 * errno.h for FreeBSD libc on Unikraft
 * 
 * Minimal errno.h that redirects to Unikraft's errno implementation
 */

#ifndef _ERRNO_H_
#define _ERRNO_H_

#include <sys/errno.h>

#ifdef __cplusplus
extern "C" {
#endif

/* FreeBSD libc expects __error() function */
extern int *__error(void);

/* Standard errno access */
#ifndef errno
extern int errno;
#define errno (*__error())
#endif

#ifdef __cplusplus
}
#endif

#endif /* _ERRNO_H_ */