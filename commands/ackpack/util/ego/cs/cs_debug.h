/* $Id: cs_debug.h,v 1.3 2005/09/01 12:13:30 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#ifdef VERBOSE

void SHOWOCCUR(occur_p);/*
			 * Shows all lines in an occurrence.
			 */

#else

#define SHOWOCCUR(x)

#endif

#ifdef TRACE

void OUTAVAILS();/* ()
			 * Prints all available expressions.
			 */

void OUTENTITIES();/* ()
			 * Prints all entities.
			 */

void SHOWAVAIL();/* (avail_p avp)
			 * Shows an available expression.
			 */

#else /* TRACE */

#define OUTAVAILS()
#define OUTENTITIES()
#define SHOWAVAIL(x)

#endif /* TRACE */
