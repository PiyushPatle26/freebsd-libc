/*
 * fcntl.h - Minimal file control definitions for FreeBSD libc on Unikraft
 * 
 * This provides basic fcntl definitions needed for compilation.
 * Functionality is provided via Unikraft's VFS system.
 */

#ifndef _FCNTL_H_
#define _FCNTL_H_

#include <sys/fcntl.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Standard fcntl() function declaration */
extern int fcntl(int fd, int cmd, ...);

/* Standard open() function declaration */
extern int open(const char *pathname, int flags, ...);

#ifdef __cplusplus
}
#endif

#endif /* _FCNTL_H_ */