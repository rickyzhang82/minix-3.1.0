/* $Id: btscpy.c,v 1.3 2005/09/01 12:13:27 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* btscpy()
*/

#include "ack_string.h"

char *
btscpy(char *b1,const char *b2,int n)
{
	char *b1s = b1;

	while (n-- > 0)
		*b1++ = *b2++;
	return b1s;
}
