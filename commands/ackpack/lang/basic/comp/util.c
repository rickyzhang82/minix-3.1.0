/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include "bem.h"

#ifndef NORSCID
static char rcs_id[] = "$Id: util.c,v 1.1 2005/09/01 12:13:17 beng Exp $" ;
#endif

#define abs(X)  (X>=0?X:-X)
/* Miscelaneous routines can be found here */

int	errorcnt;


extern int listing;
extern int basicline;

static
void
Xerror(const char *type,const char * str)
{
	if( !listing) fprintf(stderr, "LINE %d:",basicline);
	fprintf(stderr, "%s:%s\n",type, str);
}


void
warning(const char *str)
{
	 if (wflag) return;
	 Xerror("WARNING", str);
}


void
error(const char *str)
{
	Xerror("ERROR", str);
	errorcnt++;
}

void
fatal(char *str)
{
	Xerror("FATAL",str);
	C_close();
	exit( 1 );
}


void
notyetimpl(void)
{
	warning("not yet implemented");
}


void
illegalcmd(void)
{
	warning("illegal command");
}



char *
myitoa(int i)
{
	static char buf[30];

	sprintf(buf,"%d",i);
	return(buf);
}






char *
salloc(unsigned int length)
{		
	char *s,*c;

	s=c=malloc(length);
	if ( !s ) fatal("Out of memory") ;
	while(length--)*c++ =0;
	return(s);
}



