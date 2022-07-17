/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#ifndef lint
static char rcsid[] = "$Id: output.c,v 1.3 2005/09/01 12:13:33 beng Exp $";
#endif

#include <arch.h>
#include <out.h>
#include <ranlib.h>
#include <object.h>
#include "const.h"
#include "memory.h"
#include "prototypes.h"

extern struct outhead	outhead;
extern bool		incore;
extern int		flagword;
extern struct outsect	outsect[];
extern unsigned short	NLocals, NGlobals;
extern long	NLChars, NGChars;
extern char	*outputname;

/*
 * Generate names for all sections and put them after the global names.
 * Section names are used for relocation.
 */
static
void
generate_section_names(void)
{
	register struct outname	*name;
	register int		sectindex;
	register long		size;

	size = (long)outhead.oh_nsect * sizeof(struct outname); 
	name = (struct outname *)core_alloc(ALLOGLOB, size);
	if (name == (struct outname *)0)
		return;

	for (sectindex = 0; sectindex < outhead.oh_nsect; sectindex++, name++) {
		name->on_foff = (long)0;	/* No string name. */
		name->on_type = (S_MIN + sectindex) | S_SCT;
		name->on_desc = (unsigned short)0;
		name->on_valu = outsect[sectindex].os_base;
	}
}

/*
 * We have counted all relocation structs but we know only now if
 * these must be emitted.We add all names here,unless the -s(trip)
 * flag was given.
 * If this flag is given we don't need the string table either.
 */
void
beginoutput(void)
{
	if (! wr_open(outputname)) {
		fatal("can't create %s", outputname);
	}
	if (incore)
		generate_section_names();

	if (!(flagword & (CFLAG|RFLAG)))
		outhead.oh_nrelo = (unsigned short)0;
	if (flagword & SFLAG) {
		outhead.oh_nname = (unsigned short)0;
		outhead.oh_nchar = (long)0;
	} else {
		outhead.oh_nname = NLocals + NGlobals + outhead.oh_nsect;
		outhead.oh_nchar = NLChars + NGChars;
	}
	if (!incore)
		begin_write();
}

/*
 * If we didn't keep the whole output file in core, most of it has been
 * written out, and we just finish that.
 * If we did, we write out our pieces of core.
 */
void
endoutput(void)
{
	if (!incore) {
		if (!(flagword & SFLAG))
			end_write();
	} else {
		write_bytes();
	}
	wr_close();
}
