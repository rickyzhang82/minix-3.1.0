#include "bc_string.h"

/* $Id: mki.c,v 1.1 2005/09/01 12:13:18 beng Exp $ */

String *
_mki(long i)
{
	char *buffer ="    ";
	String *s;

	s= _newstr(buffer);
	* ( (long *)s->strval ) = i ;
	return(s);
}

String *
_mkd(double d)
{
	char *buffer ="        ";
	String *s;

	s= _newstr(buffer);
	* ( (double *)s->strval ) = d ;
	return(s);
}

long
_cvi(String *s)
{
	return *( (long *) s->strval) ;
}

double
_cvd(String *s)
{
	return *( (double *) s->strval) ;
}
