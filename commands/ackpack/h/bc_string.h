/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#

/* $Id: bc_string.h,v 1.1 2005/09/01 12:13:17 beng Exp $ */

/* Strings are allocated in a fixed string descriptor table 
** This mechanism is used to avoid string copying as much as possible
*/

typedef struct{
	char	*strval;
	int	strcount;
	int	strlength;
	} String;

String *_newstr(char *);
void _decstr(String *str);

#define MAXSTRING 1024
