/*-
 * x86/signal.h - Missing FreeBSD x86 signal definitions
 * Essential signal definitions for x86 architecture
 */

#ifndef _X86_SIGNAL_H
#define _X86_SIGNAL_H

/* Signal context for x86_64 */
struct sigcontext {
    long sc_rax;
    long sc_rbx;
    long sc_rcx;
    long sc_rdx;
    long sc_rsi;
    long sc_rdi;
    long sc_rbp;
    long sc_rsp;
    long sc_r8;
    long sc_r9;
    long sc_r10;
    long sc_r11;
    long sc_r12;
    long sc_r13;
    long sc_r14;
    long sc_r15;
    long sc_rip;
    long sc_rflags;
    long sc_cs;
    long sc_ss;
    long sc_ds;
    long sc_es;
    long sc_fs;
    long sc_gs;
};

#endif /* _X86_SIGNAL_H */