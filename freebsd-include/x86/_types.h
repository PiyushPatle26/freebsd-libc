/*-
 * x86/_types.h - Missing FreeBSD x86 type definitions
 * Essential types for x86 architecture
 */

#ifndef _X86_TYPES_H
#define _X86_TYPES_H

/* Wide character type */
typedef int                ___wchar_t;

/* Fast integer types */
typedef signed char        __int_fast8_t;
typedef int                __int_fast16_t;
typedef int                __int_fast32_t;
typedef long long          __int_fast64_t;

typedef unsigned char      __uint_fast8_t;
typedef unsigned int       __uint_fast16_t;
typedef unsigned int       __uint_fast32_t;
typedef unsigned long long __uint_fast64_t;

/* Register types */
#ifdef __LP64__
typedef long               __register_t;
typedef unsigned long      __uregister_t;
#else
typedef int                __register_t;
typedef unsigned int       __uregister_t;
#endif

/* Size and pointer types */
#ifdef __LP64__
typedef long               __ptrdiff_t;
typedef unsigned long      __size_t;
typedef long               __ssize_t;
typedef unsigned long      __uintptr_t;
#else
typedef int                __ptrdiff_t;
typedef unsigned int       __size_t;
typedef int                __ssize_t;
typedef unsigned int       __uintptr_t;
#endif

/* Additional FreeBSD-specific types */
typedef long               __time_t;
typedef long               __clock_t;
typedef unsigned long      __critical_t;
typedef long               __segsz_t;
typedef unsigned long      __vm_paddr_t;
typedef unsigned long      __u_register_t;

#endif /* _X86_TYPES_H */