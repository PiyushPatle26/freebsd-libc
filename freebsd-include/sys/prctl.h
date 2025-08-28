/*-
 * sys/prctl.h - Linux process control compatibility header
 * FreeBSD doesn't have prctl, but provide minimal compatibility
 */

#ifndef _SYS_PRCTL_H
#define _SYS_PRCTL_H

#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

/* Process control options - minimal set */
#define PR_SET_NAME     15  /* Set process name */
#define PR_GET_NAME     16  /* Get process name */

/* Stub function declaration */
int prctl(int option, ...);

__END_DECLS

#endif /* _SYS_PRCTL_H */