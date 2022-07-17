/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: main.c,v 1.1 2005/09/01 12:13:20 beng Exp $ */
/* MAIN PROGRAM */

#include	"debug.h"
#include	"ack_string.h"

#include	<alloc.h>
#include	<assert.h>
#include	<system.h>
#include	"idfsize.h"
#include	"idf.h"
#include	"macro.h"
#include	"prototypes.h"
#include	"input.h"

extern int err_occurred;
extern int do_dependencies;
extern char *dep_file;
int idfsize = IDFSIZE;
extern char options[];
static FILE *dep_fd;

arith ifval;

char *prog_name;

extern const char **inctable;
extern int inc_max, inc_total;

static void compile(int,char *[]);
static void list_dependencies(char *);
static void dependency(const char *,const char *);

int
main(int argc,char *argv[])
{
	dep_fd = stdout;

	/* parse and interpret the command line options	*/
	prog_name = argv[0];

	init_idf();

	inctable = (const char **) Malloc(10 * sizeof(char *));
	inc_max = 10;
	inc_total = 3;
	inctable[0] = ".";
	inctable[1] = "/usr/include";
	inctable[2] = (char *) 0;
	init_pp();	/* initialise the preprocessor macros	*/

	/*	Note: source file "-" indicates that the source is supplied
		as standard input.  This is only allowed if INP_READ_IN_ONE is
		not defined!
	*/
	while (argc > 1 && *argv[1] == '-' && argv[1][1] != '\0')	{
		char *par = &argv[1][1];

		if (*par == '-')
			par++;
		do_option(par);
		argc--, argv++;
	}
	compile(argc - 1, &argv[1]);
	return err_occurred ? 1 : 0;
}

static
void
compile(int argc,char *argv[])
{
	register char *source = 0;
	const char *dummy;

	switch (argc) {
	case 1:
		source = argv[0];
		FileName = source;
		break;
	case 0:
		FileName = "";
		WorkingDir = "";
		break;
	default:
		FileName = argv[0];
		fatal("use: %s [options] [source]", prog_name);
		break;
	}

	if (!InsertFile(source, 0, &dummy)) /* read the source file	*/
		fatal("%s: no source file %s\n", prog_name, 
			source ? source : "stdin");
	if (source) WorkingDir = getwdir(dummy);
	preprocess(source);
	if (do_dependencies) list_dependencies(source);
}

struct idf	*file_head;

static
void
list_dependencies(char *source)
{
	register struct idf *p = file_head;

	if (source) {
		register char *s = strrindex(source, '.');

		if (s && *(s+1)) {
			s++;
			*s++ = 'o';
			*s = '\0';
                        /* the source may be in another directory than the
                         * object generated, so don't include the pathname
                         * leading to it.
                         */
                        s = strrindex(source, '/');
                        if (s) {
                                source = s + 1;
                        }
		}
		else source = 0; 
	}
	if (dep_file)
	{
		dep_fd = fopen( dep_file, "w" );
		if( 0 == dep_fd )
			fatal("could not open %s", dep_file);
	}
	while (p) {
		assert(p->id_resmac == K_FILE);
		dependency(p->id_text, source);
		p = p->id_file;
	}
}

void
add_dependency(const char *s)
{
	register struct idf *p = str2idf(s, 0);

	if (! p->id_resmac) {
		p->id_resmac = K_FILE;
		p->id_file = file_head;
		file_head = p;
	}
}

static
void
dependency(const char *s,const char *source)
{
	if (options['i'] && !strncmp(s, "/usr/include/", 13)) {
		return;
	}
	if (options['m'] && source) {
		fprintf(dep_fd, "%s: %s\n", source, s);
	}
	else	fprintf(dep_fd, "%s\n", s);
}

void
No_Mem(void)				/* called by alloc package */
{
	fatal("out of memory");
}
