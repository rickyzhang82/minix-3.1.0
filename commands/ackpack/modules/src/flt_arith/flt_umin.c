/*
  (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
  See the copyright notice in the ACK home directory, in the file "Copyright".
*/

/* $Id: flt_umin.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */

#include "flt_misc.h"

void
flt_umin(flt_arith *e)
{
	/*	Unary minus
	*/
	flt_status = 0;
	e->flt_sign = ! e->flt_sign;
}
