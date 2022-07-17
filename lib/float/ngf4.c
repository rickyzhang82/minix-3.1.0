/*
  (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
  See the copyright notice in the ACK home directory, in the file "Copyright".
*/

/* $Header: /cvsup/minix/src/lib/float/ngf4.c,v 1.1.1.1 2005/04/21 14:56:11 beng Exp $ */

/*
		NEGATE A FLOATING POINT (NGF 4)
*/
/********************************************************/

#include "FP_types.h"
#include "get_put.h"

#define OFF ((FL_MSW_AT_LOW_ADDRESS ? 0 : 2) + (FL_MSB_AT_LOW_ADDRESS ? 0 : 1))
void
ngf4(f)
SINGLE	f;
{
	unsigned char *p;

	if (f != (SINGLE) 0) {
		p = (unsigned char *) &f + OFF;
		*p ^= 0x80;
	}
}
