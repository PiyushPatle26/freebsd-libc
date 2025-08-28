/*-
 * sys/sysmacros.h - Linux compatibility macros for device numbers
 * FreeBSD traditionally puts these in sys/types.h
 */

#ifndef _SYS_SYSMACROS_H
#define _SYS_SYSMACROS_H

#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

/* Device number macros - typically in sys/types.h on FreeBSD */
#ifndef major
#define major(dev)      ((int)(((unsigned)(dev) >> 8) & 0xff))
#endif

#ifndef minor
#define minor(dev)      ((int)((dev) & 0xff))
#endif

#ifndef makedev
#define makedev(major, minor) (((major) << 8) | (minor))
#endif

__END_DECLS

#endif /* _SYS_SYSMACROS_H */