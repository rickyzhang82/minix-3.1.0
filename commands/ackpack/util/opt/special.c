#ifndef NORCSID
static char rcsid[] = "$Id: special.c,v 1.3 2005/09/01 12:13:35 beng Exp $";
#endif

#include "param.h"
#include "types.h"

/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Hans van Staveren
 */

#ifdef ALLOWSPECIAL
bool special(lpp,bp,patlen)
line_p *lpp;
byte *bp;
int patlen;
{

	return(FALSE);
}
#endif
