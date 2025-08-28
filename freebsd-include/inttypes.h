/*-
 * inttypes.h - Integer printf/scanf format macros
 * Compatibility header for FreeBSD
 */

#ifndef _INTTYPES_H
#define _INTTYPES_H

#include <sys/cdefs.h>
#include <stdint.h>

__BEGIN_DECLS

/* Printf format macros for fixed-width integers */
#ifdef __LP64__
/* 64-bit system */
#define PRId8       "d"
#define PRId16      "d" 
#define PRId32      "d"
#define PRId64      "ld"
#define PRIdMAX     "ld"
#define PRIdPTR     "ld"

#define PRIu8       "u"
#define PRIu16      "u"
#define PRIu32      "u"
#define PRIu64      "lu"
#define PRIuMAX     "lu"
#define PRIuPTR     "lu"

#define PRIx8       "x"
#define PRIx16      "x"
#define PRIx32      "x"
#define PRIx64      "lx"
#define PRIxMAX     "lx"
#define PRIxPTR     "lx"

#define PRIX8       "X"
#define PRIX16      "X"
#define PRIX32      "X"
#define PRIX64      "lX"
#define PRIXMAX     "lX"
#define PRIXPTR     "lX"

#else
/* 32-bit system */
#define PRId8       "d"
#define PRId16      "d"
#define PRId32      "d"
#define PRId64      "lld"
#define PRIdMAX     "lld"
#define PRIdPTR     "d"

#define PRIu8       "u"
#define PRIu16      "u"
#define PRIu32      "u"
#define PRIu64      "llu"
#define PRIuMAX     "llu"
#define PRIuPTR     "u"

#define PRIx8       "x"
#define PRIx16      "x"
#define PRIx32      "x"
#define PRIx64      "llx"
#define PRIxMAX     "llx"
#define PRIxPTR     "x"

#define PRIX8       "X"
#define PRIX16      "X"
#define PRIX32      "X"
#define PRIX64      "llX"
#define PRIXMAX     "llX"
#define PRIXPTR     "X"
#endif

/* Scanf format macros */
#define SCNd8       "hhd"
#define SCNd16      "hd"
#define SCNd32      "d"
#define SCNu8       "hhu"
#define SCNu16      "hu"
#define SCNu32      "u"

__END_DECLS

#endif /* _INTTYPES_H */