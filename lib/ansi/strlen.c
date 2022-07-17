/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header: /cvsup/minix/src/lib/ansi/strlen.c,v 1.1.1.1 2005/04/21 14:56:06 beng Exp $ */

#include	<string.h>

size_t
strlen(const char *org)
{
	register const char *s = org;

	while (*s++)
		/* EMPTY */ ;

	return --s - org;
}
