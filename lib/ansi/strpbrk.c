/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header: /cvsup/minix/src/lib/ansi/strpbrk.c,v 1.1.1.1 2005/04/21 14:56:06 beng Exp $ */

#include	<string.h>

char *
strpbrk(register const char *string, register const char *brk)
{
	register const char *s1;

	while (*string) {
		for (s1 = brk; *s1 && *s1 != *string; s1++)
			/* EMPTY */ ;
		if (*s1)
			return (char *)string;
		string++;
	}
	return (char *)NULL;
}
