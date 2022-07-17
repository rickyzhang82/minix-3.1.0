/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header: /cvsup/minix/src/lib/ansi/wctomb.c,v 1.1.1.1 2005/04/21 14:56:06 beng Exp $ */

#include	<stdlib.h>
#include	<limits.h>

int
/* was: wctomb(char *s, wchar_t wchar) 
 * This conflicts with prototype, so it was changed to:
 */
wctomb(char *s, wchar_t wchar)
{
	if (!s) return 0;		/* no state dependent codings */

	*s = wchar;
	return 1;
}
