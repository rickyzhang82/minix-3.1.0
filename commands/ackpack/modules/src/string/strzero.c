/* $Id: strzero.c,v 1.3 2005/09/01 12:13:27 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* strzero()
*/

#include "ack_string.h"

char *
strzero(char *s)
{
	*s = '\0';
	return s;
}
