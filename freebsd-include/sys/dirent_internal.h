/*-
 * sys/dirent_internal.h - Internal DIR structure definition
 * Provides complete DIR structure for Unikraft compatibility
 */

#ifndef _SYS_DIRENT_INTERNAL_H
#define _SYS_DIRENT_INTERNAL_H

#include <sys/cdefs.h>
#include <sys/types.h>

/* Complete DIR structure definition for Unikraft vfscore compatibility */
struct _dirdesc {
    int     fd;         /* file descriptor for directory */
    long    loc;        /* offset in current buffer */
    long    size;       /* amount of data in buffer */
    char    *buf;       /* data buffer */
    int     len;        /* buffer length */
    long    seek;       /* magic cookie returned by getdirentries */
    long    rewind;     /* pos to rewind to */
    int     flags;      /* flags for opendir2 */
};

#endif /* _SYS_DIRENT_INTERNAL_H */