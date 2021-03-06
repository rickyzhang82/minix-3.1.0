/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: pragma.c,v 1.1 2005/09/01 12:13:20 beng Exp $ */
/* PREPROCESSOR: PRAGMA INTERPRETER */

#include	"prototypes.h"

#define P_UNKNOWN	0
#define NR_PRAGMAS	0

struct pkey {
	char *pk_name;
	int pk_key;
} pragmas[NR_PRAGMAS + 1] = {
	{0,		P_UNKNOWN}
};

void
do_pragma(void)
{
#if	NR_PRAGMAS
	register struct pkey *pkp = &pragmas[0];
#endif
	register struct idf *id = GetIdentifier(1);

	if (id != (struct idf *)0) {
#if	NR_PRAGMAS
		while(pkp->pk_name) {
			if (strcmp(pkp->pk_name, id->id_text) == 0)
				break;
			pkp++;
		}

		switch (pkp->pk_key) {
		case P_UNKNOWN:
		default:
			break;
		}
#endif
		SkipToNewLine();
	}
}
