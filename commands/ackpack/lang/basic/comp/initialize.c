/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include "bem.h"

#ifndef NORSCID
static char rcs_id[] = "$Id: initialize.c,v 1.1 2005/09/01 12:13:17 beng Exp $";
#endif

/* defined in basic.lex, included by basic.g */
void fillkex(void);

/* generate temporary files etc */

FILE	*datfile;


void
initialize(void)
{
	register char *cindex, *cptr;
        int result;

	/* Find the basename */
	/* Strip leading directories */
	cindex= (char *)0;
	for ( cptr=program; *cptr; cptr++ ) if ( *cptr=='/' ) cindex=cptr;
	if ( !cindex ) cindex= program;
	else {
		cindex++;
		if ( !*cindex ) {
			warning("Null program name, assuming \"basic\"");
			cindex= "basic";
		}
	}
	cptr=datfname;
	while ( *cptr++ = *cindex++ );
	/* Strip trailing suffix */
	if ( cptr>datfname+3 && cptr[-3]=='.' ) cptr[-3]=0;
	strcat(datfname,".d");
	C_init((arith)BEMINTSIZE, (arith)BEMPTRSIZE);
	yyin = fopen(inpfile, "r");
	result = C_open(outfile);
	if ( yyin==0 || result== 0 )
		fatal("Improper file permissions");
	C_magic();
	fillkex();	/* initialize symbol table */
	C_ms_emx((arith)BEMINTSIZE,(arith)BEMPTRSIZE);
	initdeftype();	/* set default symbol declarers */
}
