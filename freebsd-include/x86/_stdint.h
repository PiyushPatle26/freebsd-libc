/*-
 * x86/_stdint.h - Missing FreeBSD x86 integer type limits
 * Essential integer limits for x86 architecture
 */

#ifndef _X86_STDINT_H
#define _X86_STDINT_H

/* Limits for exact-width integer types */
#define __INT8_MIN    (-128)
#define __INT16_MIN   (-32767-1)
#define __INT32_MIN   (-2147483647-1)
#define __INT64_MIN   (-9223372036854775807LL-1)

#define __INT8_MAX    (127)
#define __INT16_MAX   (32767)
#define __INT32_MAX   (2147483647)
#define __INT64_MAX   (9223372036854775807LL)

#define __UINT8_MAX   (255)
#define __UINT16_MAX  (65535)
#define __UINT32_MAX  (4294967295U)
#define __UINT64_MAX  (18446744073709551615ULL)

/* Pointer-width integer limits */
#ifdef __LP64__
#define __INTPTR_MIN  __INT64_MIN
#define __INTPTR_MAX  __INT64_MAX
#define __UINTPTR_MAX __UINT64_MAX
#else
#define __INTPTR_MIN  __INT32_MIN
#define __INTPTR_MAX  __INT32_MAX
#define __UINTPTR_MAX __UINT32_MAX
#endif

#endif /* _X86_STDINT_H */