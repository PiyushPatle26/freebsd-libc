#include <uk/tcb_impl.h>
#include <uk/alloc.h>
#include <uk/thread.h>

int uk_thread_uktcb_init(struct uk_thread *thread, void *tcb) {
    return 0;
}

void uk_thread_uktcb_fini(struct uk_thread *thread, void *tcb) {
    return;
}

void ukarch_tls_tcb_init(void *tcb) {
    return;
}