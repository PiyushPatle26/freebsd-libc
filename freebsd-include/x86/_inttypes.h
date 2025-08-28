/*-
 * x86/_inttypes.h - Missing FreeBSD x86 integer format definitions
 */

#ifndef _X86_INTTYPES_H
#define _X86_INTTYPES_H

/* Integer printf format definitions for x86/x86_64 */
#ifdef __LP64__
/* x86_64 - 64-bit */
#define __PRI64  "l"
#define __PRIptr "l"
#else  
/* i386 - 32-bit */
#define __PRI64  "ll"
#define __PRIptr ""
#endif

#endif /* _X86_INTTYPES_H */