#include <stdio.h>
#include "bc_string.h"
#include "internal.h"

/* $Id: oct.c,v 1.1 2005/09/01 12:13:18 beng Exp $ */

String *
_oct(int i)
{
	char buffer[30];
	sprintf(buffer,"%o",i);
	return( (String *)_newstr(buffer));
}

String *
_hex(int i)
{
	char buffer[30];

	sprintf(buffer,"%x",i);
	return( (String *)_newstr(buffer));
}

String *
_nstr(double f)
{
	char buffer[80];

	_str(f, buffer);
	return (String *) _newstr(buffer);
}
