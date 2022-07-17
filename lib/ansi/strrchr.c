/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header: /cvsup/minix/src/lib/ansi/strrchr.c,v 1.1.1.1 2005/04/21 14:56:06 beng Exp $ */

#include	<string.h>

char *
strrchr(register const char *s, int c)
{
	register const char *result = NULL;

	c = (char) c;

	do {
		if (c == *s)
			result = s;
	} while (*s++ != '\0');

	return (char *)result;
}
