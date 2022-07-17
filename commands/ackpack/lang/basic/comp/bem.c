/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include "bem.h"

#ifndef NORSCID
static char rcs_id[]	= "$Id: bem.c,v 1.1 2005/09/01 12:13:17 beng Exp $" ;
static char rcs_bem[]	= RCS_BEM ;
static char rcs_symb[]	= RCS_SYMB ;
static char rcs_graph[]	= RCS_GRAPH ;
#endif

/* Author: M.L. Kersten
**
** This is the main routine for the BASIC-EM frontend.
** Program parameters are decoded, the BASIC program is parsed
** and compiled to an executable program
**
** Bem expects at least three parameters. One ending with '.i' is considered
** the input to the compiler, '.e' denotes the file to be generated,
** and the last name denotes the name of the user supplied file name.
** The latter is used to store the data entries.
** Additional flags may be supplied, see parseparms.
*/

char	*program;

char	datfname[MAXFILENAME] ;

char	*inpfile, *outfile;
int	BEMINTSIZE = EMINTSIZE;
int	BEMPTRSIZE = EMPTRSIZE;
int	BEMFLTSIZE = EMFLTSIZE;

extern int errorcnt;

int
main(int argc,char **argv)
{
	/* parseparams */
	parseparams(argc,argv);
	/* initialize the system */
	initialize();
	/* compile source programs */
	compileprogram();
	linewarnings();
	C_close();
	if( errorcnt) exit( 1 );
	/* process em object files */
	return 0;   /* This was not done in the old compiler */
}
