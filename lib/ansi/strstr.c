/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header: /cvsup/minix/src/lib/ansi/strstr.c,v 1.1.1.1 2005/04/21 14:56:06 beng Exp $ */

#include	<string.h>

char *
strstr(register const char *s, register const char *wanted)
{
	register const size_t len = strlen(wanted);

	if (len == 0) return (char *)s;
	while (*s != *wanted || strncmp(s, wanted, len))
		if (*s++ == '\0')
			return (char *)NULL;
	return (char *)s;
}
