/* $Id: btscmp.c,v 1.3 2005/09/01 12:13:27 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* btscmp()
*/

#include "ack_string.h"

int
btscmp(const char *b1,int n1,const char *b2,int n2)
{
	register int n = (n1 <= n2) ? n1 : n2;

	while (n-- > 0) {
		if (*b1++ != *b2++)
			return *--b1 - *--b2;
	}
	return n2 - n1;
}
