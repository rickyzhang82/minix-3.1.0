/* $Id: btszero.c,v 1.3 2005/09/01 12:13:27 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* btszero()
*/

#include "ack_string.h"

char *
btszero(char *b,int n)
{
	register char *s = b;

	while (n-- > 0)
		*s++ = '\0';
	
	return b;
}
