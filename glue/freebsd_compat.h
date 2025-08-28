/*
 * FreeBSD libc Compatibility Layer for Unikraft
 * 
 * This header defines the "truth" according to Unikraft's x86_64 architecture,
 * preventing conflicts between FreeBSD's multi-architecture headers and 
 * Unikraft's platform-specific definitions.
 * 
 * CRITICAL: This file must be included BEFORE any FreeBSD headers.
 */

#ifndef _FREEBSD_COMPAT_H_
#define _FREEBSD_COMPAT_H_

/* ============================================================================
 * ARCHITECTURE DEFINITIONS - Unikraft x86_64 Truth
 * ============================================================================ */

#ifndef __WORDSIZE
#define __WORDSIZE 64   /* Unikraft runs on x86_64 only - 64-bit words */
#endif

#ifndef __OFF_MAX
#define __OFF_MAX __LONG_LONG_MAX  /* Maximum file offset for 64-bit systems */
#endif

#ifndef CACHE_LINE_SIZE
#define CACHE_LINE_SIZE 64  /* x86_64 cache line size */
#endif

/* ============================================================================
 * SYSTEM LIMITS - Match Unikraft's definitions
 * ============================================================================ */

#ifndef __LONG_LONG_MAX
#define __LONG_LONG_MAX 9223372036854775807LL
#endif

#ifndef __UINTPTR_MAX
#define __UINTPTR_MAX 0xffffffffffffffffUL
#endif

#ifndef __SIZE_MAX
#define __SIZE_MAX __UINTPTR_MAX
#endif

/* ============================================================================
 * COMPILER HELPER MACROS - Only define if missing
 * ============================================================================ */

#ifndef __offsetof
#define __offsetof(type, field)  __builtin_offsetof(type, field)
#endif

#ifndef __containerof
#define __containerof(x, s, m) \
    ((s *)((char *)(x) - __offsetof(s, m)))
#endif

#ifndef __unused
#define __unused __attribute__((unused))
#endif

#ifndef __packed
#define __packed __attribute__((packed))
#endif

/* ============================================================================
 * PLATFORM COMPATIBILITY - Prevent FreeBSD platform detection
 * ============================================================================ */

/* Force FreeBSD headers to use 64-bit definitions */
#ifndef __LP64__
#define __LP64__ 1
#endif

/* Prevent 32-bit assumptions */
#ifdef __ILP32__
#undef __ILP32__
#endif

/* ============================================================================
 * TYPE COMPATIBILITY - Ensure consistent types
 * ============================================================================ */

#ifndef __SIZEOF_POINTER__
#define __SIZEOF_POINTER__ 8  /* 64-bit pointers */
#endif

#ifndef __SIZEOF_LONG__
#define __SIZEOF_LONG__ 8     /* 64-bit longs on x86_64 */
#endif

#ifndef __SIZEOF_SIZE_T__
#define __SIZEOF_SIZE_T__ 8   /* 64-bit size_t */
#endif

#endif /* _FREEBSD_COMPAT_H_ */