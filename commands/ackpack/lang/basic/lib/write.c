#include "bc_string.h"
#include "bc_io.h"
#include "internal.h"

/* $Id: write.c,v 1.1 2005/09/01 12:13:18 beng Exp $ */

/* assume that the channel has been set */
void
_wrnl(void)
{
	if( fputc('\n',_chanwr) == EOF) error(29);
}

void
_wrcomma(void)
{
	if( fputc(',',_chanwr) == EOF) error(29);
}

void
_wrint(int i)
{
	if(i>0) 
		if( fputc(' ',_chanwr)==EOF) error(29);
	fprintf(_chanwr,"%d",i);
	if( ferror(_chanwr) ) error(29);
}

void
_wrflt(double f)
{
	fprintf(_chanwr,"%f",f);
	if( ferror(_chanwr) ) error(29);
}

void
_wrstr(String *s)
{
	fprintf(_chanwr,"\"%s\"",s->strval);
	if( ferror(_chanwr) ) error(29);
}
