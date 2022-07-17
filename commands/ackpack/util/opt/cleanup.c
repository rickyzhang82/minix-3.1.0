#ifndef NORCSID
static char rcsid[] = "$Id: cleanup.c,v 1.3 2005/09/01 12:13:34 beng Exp $";
#endif

#include <stdio.h>
#include <system.h>
#include "param.h"
#include "prototypes.h"
#include "assert.h"
#include <em_pseu.h>
#include <em_spec.h>
#include <em_mes.h>
#include "lookup.h"
#include "ext.h"

#ifndef _WIN32
# include <unistd.h>
#else
# include <io.h>
#endif

/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Hans van Staveren
 */


void
cleanup(void)
{
	FILE *infile;
	register int c;
	register sym_p *spp,sp;

 	for (spp=symhash;spp< &symhash[NSYMHASH];spp++)
 		for (sp = *spp; sp != (sym_p) 0; sp = sp->s_next)
 			if ((sp->s_flags & SYMOUT) == 0)
 				outdef(sp);
	if(!Lflag)
		return;
	c=fclose(outfile);
	assert(c != EOF);
	outfile = stdout;
	infile = fopen(tmplt,"rb");
	if (infile == NULL)
		error("temp file disappeared");
	outshort(sp_magic);
	/* Attempt to first output the word_size message */
	while ((c = getc(infile)) != sp_cend && c != EOF) {
		putc(c, outfile);
	}
	if (c == sp_cend) putc(c, outfile);
	outinst(ps_mes);
	outint(ms_ext);
	for (spp=symhash;spp< &symhash[NSYMHASH];spp++)
		for (sp = *spp; sp != (sym_p) 0; sp = sp->s_next)
			if ((sp->s_flags&(SYMDEF|SYMGLOBAL)) == (SYMDEF|SYMGLOBAL))
				outsym(sp);
	putc(sp_cend,outfile);
	while ( (c=getc(infile)) != EOF)
		putc(c,outfile);
	c=fclose(infile);
	assert(c != EOF);
	c=unlink(tmplt);
	assert(c != 0);
}
