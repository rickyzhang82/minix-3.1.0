/*
  (c) copyright 1989 by the Vrije Universiteit, Amsterdam, The Netherlands.
  See the copyright notice in the ACK home directory, in the file "Copyright".
*/

/* $Id: flt_nrm.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */

#include "flt_misc.h"

void
flt_nrm(flt_arith *e)
{
	if ((e->m1 | e->m2) == 0L) {
		e->flt_exp = 0;
		e->flt_sign = 0;
		return;
	}

	/* if top word is zero mov low word	*/
	/* to top word, adjust exponent value	*/
	if (e->m1 == 0L)	{
		e->m1 = e->m2;
		e->m2 = 0L;
		e->flt_exp -= 32;
	}
	if ((e->m1 & 0x80000000) == 0) {
		long l = 0x40000000;
		int cnt = -1;

		while (! (l & e->m1)) {
			l >>= 1;
			cnt--;
		}
		e->flt_exp += cnt;
		flt_b64_sft(&(e->flt_mantissa), cnt);
	}
}
