/* $Id: cs_profit.h,v 1.3 2005/09/01 12:13:30 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include <stdio.h>

void	cs_machinit(FILE *);	/*
				 * Read phase-specific information from f.
				 */

bool	desirable(avail_p);	/*
				 * Return whether it is desirable to eliminate
				 * the recurrences of the expression in avp.
				 * At the same time delete the recurrences
				 * for which it is not allowed.
				 */
