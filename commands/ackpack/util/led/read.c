/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#ifndef lint
static char rcsid[] = "$Id: read.c,v 1.3 2005/09/01 12:13:34 beng Exp $";
#endif

#include <stdio.h>

FILE *	infile;	/* The current input file. */

void fatal(char *,...);

void
rd_fatal(void)
{
	fatal("read error");
}
