/*
 * VFS stubs for FreeBSD libc compatibility
 * Provides basic file system operations for Unikraft
 */

#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

int fstat(int fd, struct stat *buf)
{
    /* Simple stub - return error for now */
    errno = ENOSYS;
    return -1;
}

int close(int fd)
{
    /* Simple stub - assume success for now */
    return 0;
}

int utimes(const char *path, const struct timeval *times)
{
    /* Simple stub - assume success for now */
    return 0;
}