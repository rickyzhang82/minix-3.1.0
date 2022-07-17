/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Header: /cvsup/minix/src/lib/ansi/labs.c,v 1.1.1.1 2005/04/21 14:56:05 beng Exp $ */

#include	<stdlib.h>

long
labs(register long l)
{
	return l >= 0 ? l : -l;
}
