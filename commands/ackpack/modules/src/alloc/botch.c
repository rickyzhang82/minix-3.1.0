/* $Id: botch.c,v 1.3 2005/09/01 12:13:24 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*	botch - write garbage over a chunk of memory, useful if you want
		to check if freed memory is used inappopriately.
*/

#include "alloc.h"

void
botch(void *ptr,unsigned int n)
{
	register char * p = (char *)ptr;
	while (n >= sizeof (long))	{	
			/* high-speed botch loop */
		*(long *)p = 025252525252L;
		p += sizeof (long), n -= sizeof (long);
	}
	while (n--) *p++ = '\252';
}
