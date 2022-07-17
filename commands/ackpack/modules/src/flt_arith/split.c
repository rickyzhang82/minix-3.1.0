/* $Id: split.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */

#include "flt_misc.h"

void
flt_split(flt_arith *e,unsigned short *p)
{
	/*	Split mantissa of e into the array p
	*/

	p[0] = (int)(e->m1 >> 16) & 0xFFFF;
	p[1] = (int)(e->m1) & 0xFFFF;
	p[2] = (int)(e->m2 >> 16) & 0xFFFF;
	p[3] = (int)(e->m2) & 0xFFFF;
}
