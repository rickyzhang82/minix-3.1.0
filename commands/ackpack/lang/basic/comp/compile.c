/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include "bem.h"

#ifndef NORSCID
static char rcs_id[] = "$Id: compile.c,v 1.1 2005/09/01 12:13:17 beng Exp $" ;
#endif


/* compile the next program in the list */
/* Here we should open the input file. (for the future) */

FILE *yyin;
extern int basicline;

/* defined by basic.g */
void LLparse(void);

/* defined in basic.lex, included by basic.g */
int getline(void);

void
compileprogram(void)
{
	prologcode();
	prolog2(); /* Some statements are moved from prolog2 to 
                      epilogcode in the new version of the compiler */

	while( basicline = 0, getline())
		(void) LLparse();
	epilogcode(); 
	fclose(yyin);
}
