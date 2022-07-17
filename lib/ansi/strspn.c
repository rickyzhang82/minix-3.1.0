/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header: /cvsup/minix/src/lib/ansi/strspn.c,v 1.1.1.1 2005/04/21 14:56:06 beng Exp $ */

#include	<string.h>

size_t
strspn(const char *string, const char *in)
{
	register const char *s1, *s2;

	for (s1 = string; *s1; s1++) {
		for (s2 = in; *s2 && *s2 != *s1; s2++)
			/* EMPTY */ ;
		if (*s2 == '\0')
			break;
	}
	return s1 - string;
}
