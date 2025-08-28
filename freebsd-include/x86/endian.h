/*-
 * x86/endian.h - Missing FreeBSD x86 endian definitions
 * Essential endianness definitions for x86 architecture
 */

#ifndef _X86_ENDIAN_H
#define _X86_ENDIAN_H

/* x86 is little endian */
#define _LITTLE_ENDIAN  1234
#define _BIG_ENDIAN     4321
#define _PDP_ENDIAN     3412
#define _BYTE_ORDER     _LITTLE_ENDIAN

#endif /* _X86_ENDIAN_H */