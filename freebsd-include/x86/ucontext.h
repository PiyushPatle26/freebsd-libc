/*-
 * x86/ucontext.h - Missing FreeBSD x86 user context definitions
 */

#ifndef _X86_UCONTEXT_H
#define _X86_UCONTEXT_H

#include <sys/cdefs.h>

/* Basic x86_64 register context - minimal for compatibility */
#ifdef __LP64__
typedef struct {
    long r15, r14, r13, r12, rbp, rbx, r11, r10;
    long r9, r8, rax, rcx, rdx, rsi, rdi;
    long rip, cs, eflags, rsp, ss;
} mcontext_t;
#else
/* i386 registers */
typedef struct {
    int gs, fs, es, ds;
    int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    int eip, cs, eflags, esp_at_signal, ss;
} mcontext_t;
#endif

#endif /* _X86_UCONTEXT_H */