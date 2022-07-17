/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: LLmessage.c,v 1.1 2005/09/01 12:13:20 beng Exp $ */
/*		PARSER ERROR ADMINISTRATION		*/

#include	"prototypes.h"
#include	"Lpars.h"

char *symbol2str(int tok);

void
LLmessage(int tk)
{
	if (tk < 0)
		error("garbage at end of line");
	else if (tk)	{
		error("%s missing", symbol2str(tk));
		if (DOT != EOF) SkipToNewLine();
		DOT = EOF;
	}
	else
		error("%s deleted", symbol2str(DOT));
}
