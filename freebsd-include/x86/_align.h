/*-
 * x86/_align.h - Missing FreeBSD x86 alignment definitions
 * Essential alignment definitions for x86 architecture
 */

#ifndef _X86_ALIGN_H
#define _X86_ALIGN_H

/* Alignment requirements for x86/x86_64 */
#ifdef __LP64__
#define _ALIGNBYTES     (sizeof(long) - 1)
#else
#define _ALIGNBYTES     (sizeof(int) - 1)
#endif

#define _ALIGN(p)       (((unsigned long)(p) + _ALIGNBYTES) & ~_ALIGNBYTES)

#endif /* _X86_ALIGN_H */