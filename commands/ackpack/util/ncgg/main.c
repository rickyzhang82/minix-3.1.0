/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#ifndef NORCSID
static char rcsid[]= "$Id: main.c,v 1.3 2005/09/01 12:13:34 beng Exp $";
#endif

#include <stdio.h>
#include <stdlib.h>
#include "extern.h"

#if defined( __CYGWIN__ )
# include <fcntl.h>
#endif

char *filename;
#ifdef HAVE_SBRK
char *beg_sbrk;
extern char *sbrk();
#endif

int
main(int argc,char *argv[])
{
	extern int nerrors;
	extern int code_in_c;
	extern int tabledebug;
	extern int verbose;

#ifdef HAVE_SBRK
	beg_sbrk = sbrk(0);
#endif

	while (argc >1 && argv[1][0]=='-') {
		switch(argv[1][1]) {
		case 'c':
			code_in_c = 0;
			break;
		case 'd':
			tabledebug++;
			break;
		case 'v':
			verbose++;
			break;
		default:
			error("Unknown flag -%c",argv[1][1]);
		}
		argc--; argv++;
	}
	if (argc==2) {
		if (freopen(argv[1],"r",stdin)==NULL) {
			error("Can't open %s",argv[1]);
			exit(-1);
		}
		filename = argv[1];
	}
	else if (argc == 1) {
		filename = "";
	} else
		error("Usage: %s [-c] [-d] [-v] [table]",argv[0]);
#if defined( __CYGWIN__ )
	setmode( fileno( stdin ), O_TEXT );
#endif
	initemhash();
	enterkeyw();
	initnodes();
	initio();
	yyparse();
	if (nerrors==0) {
		finishio();
		statistics();
		if (verbose)
			hallverbose();
	} else {
		errorexit();
	}
	return nerrors==0 ? 0 : -1;
}
