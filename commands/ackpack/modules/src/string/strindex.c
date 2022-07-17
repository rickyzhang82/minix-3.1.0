/* $Id: strindex.c,v 1.3 2005/09/01 12:13:27 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* strindex() -- (86/03/18 EHB)
*/

#include "ack_string.h"

char *
strindex(char *s,int c)
{
	while (*s)
		if (*s++ == c)
			return --s;
	return (char *)0;
}
