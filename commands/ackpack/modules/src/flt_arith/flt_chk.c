/*
  (c) copyright 1989 by the Vrije Universiteit, Amsterdam, The Netherlands.
  See the copyright notice in the ACK home directory, in the file "Copyright".
*/

/* $Id: flt_chk.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */

#include "flt_misc.h"

int	flt_status = 0;

void
flt_chk(flt_arith *e)
{
	if (e->flt_exp >= EXT_MAX) {
		flt_status = FLT_OVFL;
		e->flt_exp = EXT_MAX;
		e->m1 = 0x80000000;
		e->m2 = 0;
	}
	if (e->flt_exp <= EXT_MIN) {
		flt_status = FLT_UNFL;
		e->flt_exp = 0;
		e->m1 = 0;
		e->flt_sign = 0;
		e->m2 = 0;
	}
}
