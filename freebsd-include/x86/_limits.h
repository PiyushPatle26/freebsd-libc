/*-
 * x86/_limits.h - Missing FreeBSD x86 limits
 * Essential limits for x86 architecture
 */

#ifndef _X86_LIMITS_H
#define _X86_LIMITS_H

/* Word size for x86/x86_64 */
#ifdef __LP64__
#define __WORD_BIT      64
#else
#define __WORD_BIT      32
#endif

/* Character limits */
#define __CHAR_BIT      8
#define __UCHAR_MAX     255         /* max value for an unsigned char */
#define __SCHAR_MAX     127         /* max value for a signed char */
#define __SCHAR_MIN     (-128)      /* min value for a signed char */

/* Integer limits */
#define __USHRT_MAX     65535       /* max value for an unsigned short */
#define __UINT_MAX      4294967295U /* max value for an unsigned int */
#ifdef __LP64__
#define __ULONG_MAX     18446744073709551615UL  /* max value for an unsigned long (64-bit) */
#else
#define __ULONG_MAX     4294967295UL            /* max value for an unsigned long (32-bit) */
#endif

/* Long limits */
#ifdef __LP64__
#define __LONG_BIT      64
#define __LONG_MAX      9223372036854775807L
#define __LONG_MIN      (-9223372036854775807L-1L)
#else
#define __LONG_BIT      32
#define __LONG_MAX      2147483647L
#define __LONG_MIN      (-2147483647L-1L)
#endif

/* Standard limits */
#define __INT_MAX       2147483647
#define __INT_MIN       (-__INT_MAX-1)
#define __LONG_MAX      9223372036854775807L
#define __SSIZE_MAX     __LONG_MAX
#define __OFF_MAX       __LONG_MAX      /* max value for an off_t */

#endif /* _X86_LIMITS_H */
