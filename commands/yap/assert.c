/* Copyright (c) 1985 Ceriel J.H. Jacobs */

# ifndef lint
static char rcsid[] = "$Header: /cvsup/minix/src/commands/yap/assert.c,v 1.1.1.1 2005/04/21 14:55:38 beng Exp $";
# endif

# define _ASSERT_

# include "in_all.h"
# include "assert.h"
# if DO_ASSERT
# include "output.h"
# include "term.h"

/*
 * Assertion fails. Tell me about it.
 */

VOID
badassertion(ass,f,l) char *ass, *f; {

	clrbline();
	putline("Assertion \"");
	putline(ass);
	putline("\" failed ");
	putline(f);
	putline(", line ");
	prnum((long) l);
	putline(".\r\n");
	flush();
	resettty();
	abort();
}
# endif
