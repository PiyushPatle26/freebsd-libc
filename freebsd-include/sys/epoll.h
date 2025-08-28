/*-
 * sys/epoll.h - Minimal epoll compatibility for FreeBSD
 */

#ifndef _SYS_EPOLL_H
#define _SYS_EPOLL_H

#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

/* epoll event structure */
typedef union epoll_data {
    void *ptr;
    int fd;
    uint32_t u32;
    uint64_t u64;
} epoll_data_t;

struct epoll_event {
    uint32_t events;
    epoll_data_t data;
};

/* Event types - must match FreeBSD poll constants exactly */
#define EPOLLIN     0x0001    /* POLLIN - any readable data available */
#define EPOLLPRI    0x0002    /* POLLPRI - OOB/Urgent readable data */
#define EPOLLOUT    0x0004    /* POLLOUT - file descriptor is writeable */
#define EPOLLERR    0x0008    /* POLLERR - some poll error occurred */
#define EPOLLHUP    0x0010    /* POLLHUP - file descriptor was "hung up" */
#define EPOLLRDHUP  0x4000    /* POLLRDHUP - half shut down */

/* Additional epoll constants - must match poll constants */
#define EPOLLRDNORM    0x0040    /* POLLRDNORM - non-OOB/URG data available */
#define EPOLLRDBAND    0x0080    /* POLLRDBAND - OOB/Urgent readable data */
#define EPOLLWRNORM    0x0004    /* POLLWRNORM = POLLOUT - no write type differentiation */
#define EPOLLWRBAND    0x0100    /* POLLWRBAND - OOB/Urgent data can be written */
#define EPOLLMSG       0x400
#define EPOLLET        (1 << 31)    /* Edge Triggered */
#define EPOLLONESHOT   (1 << 30)    /* One-shot behavior */

/* epoll_create1() flags */
#define EPOLL_CLOEXEC   O_CLOEXEC

/* epoll_ctl() operations */
#define EPOLL_CTL_ADD   1
#define EPOLL_CTL_DEL   2
#define EPOLL_CTL_MOD   3

/* Function declarations */
int epoll_create(int size);
int epoll_create1(int flags);
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);


__END_DECLS

#endif /* _SYS_EPOLL_H */
