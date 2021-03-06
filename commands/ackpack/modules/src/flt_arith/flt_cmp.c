/*
  (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
  See the copyright notice in the ACK home directory, in the file "Copyright".
*/

/* $Id: flt_cmp.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */

#include "flt_misc.h"

int
flt_cmp(flt_arith *e1,flt_arith *e2)
{
	flt_arith x;

	flt_sub(e1, e2, &x);
	if (x.m1 == 0 && x.m2 == 0) return 0;
	if (x.flt_sign) return -1;
	return 1;
}
