/*
 * poll.h - Minimal poll definitions for FreeBSD libc on Unikraft
 */

#ifndef _POLL_H_
#define _POLL_H_

#include <sys/poll.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Standard poll function declaration */
extern int poll(struct pollfd *fds, nfds_t nfds, int timeout);

#ifdef __cplusplus
}
#endif

#endif /* _POLL_H_ */