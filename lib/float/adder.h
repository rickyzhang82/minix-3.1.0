/*
  (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
  See the copyright notice in the ACK home directory, in the file "Copyright".
*/

/* $Header: /cvsup/minix/src/lib/float/adder.h,v 1.1.1.1 2005/04/21 14:56:10 beng Exp $ */

/*
 *	include file for 32 & 64 bit addition
 */

typedef	struct	B64 {
	unsigned long	h_32;	/* higher 32 bits of 64 */
	unsigned long	l_32;	/* lower  32 bits of 64 */
}	B64;
