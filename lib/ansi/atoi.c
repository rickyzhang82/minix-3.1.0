/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header: /cvsup/minix/src/lib/ansi/atoi.c,v 1.1.1.1 2005/04/21 14:56:04 beng Exp $ */

#include	<ctype.h>
#include	<stdlib.h>

int
atoi(register const char *nptr)
{
	return strtol(nptr, (char **) NULL, 10);
}
