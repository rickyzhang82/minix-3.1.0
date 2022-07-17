/* $Id: clear.c,v 1.3 2005/09/01 12:13:24 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*	clear - clear a block of memory, and try to do it fast.
*/

#include "alloc.h"

/* instead of Calloc: */

void
clear(void *ptr,unsigned int n)
{
	register long *q = (long *) ptr;
	register char *p;

	while (n >= 8*sizeof (long))	{
			/* high-speed clear loop */
		*q++ = 0;
		*q++ = 0;
		*q++ = 0;
		*q++ = 0;
		*q++ = 0;
		*q++ = 0;
		*q++ = 0;
		*q++ = 0;
		n -= 8*sizeof (long);
	}
	while (n >= sizeof (long))	{
			/* high-speed clear loop */
		*q++ = 0;
		n -= sizeof (long);
	}
	p = (char *) q;
	while (n--) *p++ = '\0';
}
