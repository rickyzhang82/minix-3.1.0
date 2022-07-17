/* $Id: btscat.c,v 1.3 2005/09/01 12:13:27 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* btscat()
*/

#include "ack_string.h"

char *
btscat(char *b1,int n1,const char *b2,int n2)
{
	register char *b = b1 + n1;

	while (n2-- > 0)
		*b++ = *b2++;
	return b1;
}
