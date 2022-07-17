/*
  (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
  See the copyright notice in the ACK home directory, in the file "Copyright".
*/

/* $Header: /cvsup/minix/src/lib/float/zrf4.c,v 1.1.1.1 2005/04/21 14:56:11 beng Exp $ */

/*
	return a zero float (ZRF 4)
*/

#include "FP_types.h"

void
zrf4(l)
SINGLE	*l;
{
	*l = 0L;
}
