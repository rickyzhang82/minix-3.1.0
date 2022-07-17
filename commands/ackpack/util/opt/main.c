#ifndef NORCSID
static char rcsid[] = "$Id: main.c,v 1.3 2005/09/01 12:13:34 beng Exp $";
#endif

#include <stdio.h>
#include "param.h"
#include "prototypes.h"
#include "tes.h"
#include "alloc.h"
#include <em_spec.h>
#include "ext.h"

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#else
#include <unistd.h>
#endif

#ifdef __BORLANDC__
# define _setmode setmode
#endif

/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Hans van Staveren
 */

/*
 * Main program for EM optimizer
 */

void
flags(char * s)
{
	for (s++;*s;s++)
		switch(*s) {
		case 'L':	Lflag = TRUE; break;
		case 'n':	nflag = TRUE; break;
		case 'm':	if (*(s+1) == 'l') {
					s++;
					repl_longmuls = TRUE;
				}
				repl_muls = atoi(s+1); break;
		}
}

void
fileinit(void)
{
	if (readshort() != (short) sp_magic)
		error("wrong input file");
	if (Lflag) {
		char * fname = mktemp(tmplt);
		outfile = fopen(fname,"wb");
		if (outfile == NULL)
			error("can't create %s",tmplt);
	} else {
		outfile = stdout;
		outshort(sp_magic);
	}
}

int
main(int argc,char *argv[])
{
	int somespace[STACKROOM];
	char * tmp;

#ifdef _WIN32
	/* Always process files as binary */
	_setmode( 0, _O_BINARY );	/* stdin */
	_setmode( 1, _O_BINARY );	/* stdout */
#endif

	/* Initialise tmplt */
	tmp = getenv( "TMP" );
	if( 0 == tmp )
		tmp = getenv( "TEMP" );
	if( 0 == tmp )
		tmp = getenv( "TMPDIR" );
	if( 0 == tmp )
		tmp = "/usr/tmp";
	strcpy( tmplt, tmp );
	strcat( tmplt, "/emoptXXXXXX" );

	progname = argv[0];
	while (argc-->1 && **++argv == '-')
		flags(*argv);
	if (argc>1) {
		fprintf(stderr,"Usage: %s [-Ln] [-m<num>] [name]\n",progname);
		exit(-1);
	}
	if (argc)
		if (freopen(*argv,"rb",stdin) == NULL)
			error("Cannot open %s",*argv);
#if 0
fprintf( stderr, "stdin = %08x\n", &_stdin );
fprintf( stderr, "\t_count = %d\n", _stdin._count );
fprintf( stderr, "\t_flags = %d\n", _stdin._flags );
fprintf( stderr, "\t_bufsiz = %d\n", _stdin._bufsiz );
fprintf( stderr, "\t_fd = %d\n", _stdin._fd );
#endif
	fileinit();
	coreinit((short *)somespace,(short *)(somespace+STACKROOM));
	getlines();
	cleanup();
	return(0);
}

