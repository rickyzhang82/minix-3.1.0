/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include "bem.h"

#ifndef NORSCID
static char rcs_id[] = "$Id: parsepar.c,v 1.1 2005/09/01 12:13:17 beng Exp $" ;
#endif


int	listing;		/* -l listing required */
int	debug;			/* -d compiler debugging */
int	wflag=0;		/* -w no warnings */
int	traceflag=0;		/* generate line tracing code */
int	nolins=0;		/* generate no LIN statements */


void
parseparams(int argc,char ** argv)
{
	int files=0 ;
	int i;
	register char *p;

	if(argc< 4)
	{
		fprintf(stderr,"usage %s <flags> <file> <file> <source>\n", 
			argv[0]);
		exit( 1 );
	}

	for(i=1;i<argc;i++)
		if( argv[i][0]=='-')
			switch(argv[i][1])
			{
				case 'D': yydebug++;
					  break;	/* parser debugging */
				case 't': traceflag++; 
					  break;	/* line tracing */
				case 'h': /* split EM file */
					  fprintf(stderr,
                                                 "h option not implemented\n");
					  break;
				case 'd': debug++; 
					  break;
				case 'L': nolins++; 
					  break; /* no EM lin statements */
				case 'E': listing++; 
					  break; /* generate full listing */
				case 'w': wflag++;
					  break; /* no warnings */
				case 'V':
					  p = &argv[i][2];
					  while (*p) switch(*p++) {
					  case 'w':
						BEMINTSIZE = *p++ - '0';
						break;
					  case 'p':
						BEMPTRSIZE = *p++ - '0';
						break;
					  case 'f':
						BEMFLTSIZE = *p++ - '0';
						break;
					  default:
						p++;
						break;
					  }
			} else {
				/* new input file */
				switch ( files++ ) {
					case 0: inpfile= argv[i]; break;
					case 1: outfile= argv[i]; break;
					case 2: /* should be the source file 
						   name */
						program= argv[i]; 
						break;
					default:fatal("Too many file arguments") ;
				}
			}
		if (files < 3) fatal("Too few file arguments");
}
