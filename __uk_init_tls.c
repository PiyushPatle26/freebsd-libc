// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright (c) 2023, Unikraft GmbH and The FreeBSD Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <uk/tcb_impl.h>
#include <uk/alloc.h>
#include <uk/assert.h>
#include <uk/print.h>
#include <string.h>

/*
 * This callback is called for every thread to initialize the TCB.
 * For the main thread, this is the first point where we can initialize
 * libc-internal data structures.
 */
void ukarch_tls_tcb_init(void *tcb)
{
	uk_pr_debug("Initializing TCB for main thread at %p\n", tcb);

	/*
	 * For the main thread, we must initialize the TLS pointer.
	 * On x86_64, this sets the %fs register.
	 */
	ukplat_tlsp_set((__uptr) tcb);

	/*
	 * Zero out the TCB area. This is a minimal initialization that
	 * will suffice for single-threaded applications. A real multi-threaded
	 * application will require a more sophisticated initialization here.
	 */
	memset(tcb, 0, ukarch_tls_area_size());
}

/*
 * This callback is called for threads that are managed by Unikraft's
 * scheduler but are still expected to be compatible with the C library.
 */
int uk_thread_uktcb_init(struct uk_thread *thread, void *tcb)
{
	uk_pr_debug("Initializing TCB for uk_thread %p at %p\n", thread, tcb);

	/*
	 * This is where we would initialize the FreeBSD pthread structure
	 * for a Unikraft-managed thread. For c-hello, this is not needed.
	 */
	return 0;
}

/*
 * This callback is called when a Unikraft-managed thread is destroyed.
 */
void uk_thread_uktcb_fini(struct uk_thread *thread, void *tcb)
{
	uk_pr_debug("Finalizing TCB for uk_thread %p at %p\n", thread, tcb);

	/*
	 * This is where we would clean up any resources allocated for the
	 * FreeBSD pthread structure. For c-hello, this is not needed.
	 */
}
