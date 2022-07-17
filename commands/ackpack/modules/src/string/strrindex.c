/* $Id: strrindex.c,v 1.3 2005/09/01 12:13:27 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include "ack_string.h"

char *
strrindex(char *str,int chr)
{
	register char *retptr = 0;

	while (*str)
		if (*str++ == chr)
			retptr = &str[-1];
	return retptr;
}
