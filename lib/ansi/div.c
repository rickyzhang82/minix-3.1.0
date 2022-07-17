/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header: /cvsup/minix/src/lib/ansi/div.c,v 1.1.1.1 2005/04/21 14:56:04 beng Exp $ */

#include	<stdlib.h>

static int tmp = -1;

div_t
div(register int numer, register int denom)
{
	div_t r;

	/* The assignment of tmp should not be optimized !! */
	if (tmp == -1) {
		tmp = (tmp / 2 == 0);
	}
	if (numer == 0) {
		r.quot = numer / denom;		/* might trap if denom == 0 */
		r.rem = numer % denom;
	} else if ( !tmp && ((numer < 0) != (denom < 0))) {
		r.quot = (numer / denom) + 1;
		r.rem = numer - (numer / denom + 1) * denom;
	} else {
		r.quot = numer / denom;
		r.rem = numer % denom;
	}
	return r;
}
