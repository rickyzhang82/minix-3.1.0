/* $Id: bts2str.c,v 1.3 2005/09/01 12:13:27 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*	bts2str() turns a row of bytes b with length n into string s
	The ASCII set of characters is used.
	86/03/17 EHB
*/

#include "ack_string.h"

#define is_print(c)	((unsigned)((c) - ' ') <= '~' - ' ')

char *
bts2str(const char *b,int n,char *s)
{
	const char *f = b;
	char *t = s;

	while (n-- > 0) {
		if (is_print(*f)) {
			if (*f == '\\' || *f == '"') *t++ = '\\';
			*t++ = *f++;
		} else {
			*t++ = '\\';
			*t++ = ((*f >> 6) & 03) + '0';
			*t++ = ((*f >> 3) & 07) + '0';
			*t++ = (*f++ & 07) + '0';
		}
	}
	*t = '\000';
	return s;
}
