/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1988, 1989, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)termios.h	8.3 (Berkeley) 3/28/94
 */

#ifndef _TERMIOS_H_
#define	_TERMIOS_H_

#include <sys/cdefs.h>
#include <sys/_termios.h>
#include <sys/_types.h>
#if __BSD_VISIBLE
#include <sys/_winsize.h>
#endif

#ifndef _PID_T_DECLARED
typedef	__pid_t		pid_t;
#define	_PID_T_DECLARED
#endif

#if __BSD_VISIBLE
#define	OXTABS		TAB3
#define	MDMBUF		CCAR_OFLOW
#endif 

#if __BSD_VISIBLE
#define	CCEQ(val, c)	((c) == (val) && (val) != _POSIX_VDISABLE)
#endif

/*
 * Commands passed to tcsetattr() for setting the termios structure.
 */
#define	TCSANOW		0		/* make change immediate */
#define	TCSADRAIN	1		/* drain output, then change */
#define	TCSAFLUSH	2		/* drain output, flush input */
#if __BSD_VISIBLE
#define	TCSASOFT	0x10		/* flag - don't alter h.w. state */
#endif

#define	TCIFLUSH	1
#define	TCOFLUSH	2
#define	TCIOFLUSH	3
#define	TCOOFF		1
#define	TCOON		2
#define	TCIOFF		3
#define	TCION		4

__BEGIN_DECLS
speed_t	cfgetispeed(const struct termios *);
speed_t	cfgetospeed(const struct termios *);
int	cfsetispeed(struct termios *, speed_t);
int	cfsetospeed(struct termios *, speed_t);
int	tcgetattr(int, struct termios *);
int	tcsetattr(int, int, const struct termios *);
int	tcdrain(int);
int	tcflow(int, int);
int	tcflush(int, int);
int	tcsendbreak(int, int);

#if __POSIX_VISIBLE >= 200112
pid_t	tcgetsid(int);
#endif
#if __BSD_VISIBLE
int	tcsetsid(int, pid_t);

void	cfmakeraw(struct termios *);
void	cfmakesane(struct termios *);
int	cfsetspeed(struct termios *, speed_t);

int	tcgetwinsize(int, struct winsize *);
int	tcsetwinsize(int, const struct winsize *);
#endif
__END_DECLS

/* Linux compatibility definitions */
#ifndef VSWTC
#define VSWTC     7     /* Linux switch character - not used on FreeBSD */
#endif

#ifndef TCGETS
#define TCGETS    TIOCGETA     /* Get terminal attributes */
#define TCSETS    TIOCSETA     /* Set terminal attributes */
#define TCSETSW   TIOCSETAW    /* Set terminal attributes, drain output */
#define TCSETSF   TIOCSETAF    /* Set terminal attributes, drain output, flush input */
#endif

#ifndef TCSBRK
/* Linux terminal control compatibility - using unique values */
#define TCSBRK    0x5409      /* Send break */
#define TCSBRKP   0x5425      /* Send break with duration */
#define TCXONC    0x540A      /* Flow control */
#define TCFLSH    0x540B      /* Flush */
#define TIOCINQ   FIONREAD    /* Bytes available for reading */
#define TIOCGEXCL 0x80045440  /* Get exclusive access status */
#endif

#endif /* !_TERMIOS_H_ */

#if __BSD_VISIBLE
#include <sys/ttycom.h>
#include <sys/ttydefaults.h>
#endif
