/*-
 * stdint.h - Wrapper for FreeBSD sys/stdint.h
 */

#ifndef _STDINT_H
#define _STDINT_H
#include <sys/stdint.h>

/* Standard integer limits */
#define INT8_MIN    (-128)
#define INT16_MIN   (-32767-1)
#define INT32_MIN   (-2147483647-1)
#define INT64_MIN   (-9223372036854775807LL-1)

#define INT8_MAX    (127)
#define INT16_MAX   (32767)
#define INT32_MAX   (2147483647)
#define INT64_MAX   (9223372036854775807LL)

#define UINT8_MAX   (255)
#define UINT16_MAX  (65535)
#define UINT32_MAX  (4294967295U)
#define UINT64_MAX  (18446744073709551615ULL)

/* Size limits */
#ifdef __LP64__
#define SIZE_MAX    UINT64_MAX
#else
#define SIZE_MAX    UINT32_MAX
#endif

#endif /* _STDINT_H */
