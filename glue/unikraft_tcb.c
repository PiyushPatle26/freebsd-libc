#include <uk/tcb_impl.h>
#include <uk/alloc.h>
#include <uk/thread.h>
#include <uk/plat/tls.h>
#include <uk/arch/tls.h>
#include <stddef.h>
#include <string.h>

struct __pthread {
    struct __pthread *self;
    void *dtv;
    void *tsd;
    struct __pthread *next, *prev;
    int tid;
    int detach_state;
    void *stack;
    size_t stack_size;
    void *locale;
};

static const size_t __uk_tsd_size = 1024;
static int can_do_threads = 0;
static int global_locale = 0;

int uk_thread_uktcb_init(struct uk_thread *thread, void *tcb) {
    struct __pthread *td = (struct __pthread *)tcb;
    memset(td, 0, sizeof(*td));
    td->stack = thread->_mem.stack;
    td->stack_size = __STACK_SIZE;
    td->self = td;
    td->tsd = uk_memalign(uk_alloc_get_default(), __PAGE_SIZE, __uk_tsd_size);
    if (!td->tsd) return -1;
    memset(td->tsd, 0, __uk_tsd_size);
    td->locale = &global_locale;
    td->next = td->prev = td;
    return 0;
}

void uk_thread_uktcb_fini(struct uk_thread *thread, void *tcb) {
    struct __pthread *td = (struct __pthread *)tcb;
    if (!td) return;
    if (td->tsd) {
        uk_free(uk_alloc_get_default(), td->tsd);
        td->tsd = NULL;
    }
}

void ukarch_tls_tcb_init(void *tcb) {
    if (!can_do_threads) {
        can_do_threads = 1;
    }
}