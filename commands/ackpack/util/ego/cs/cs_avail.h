/* $Id: cs_avail.h,v 1.3 2005/09/01 12:13:30 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
extern avail_p	avails;		/* The set of available expressions. */

avail_p	av_enter(avail_p,occur_p,int);
				/* Puts the available expression in avp
				 * in the list of available expressions,
				 * if it is not already there. Add ocp to set of
				 * occurrences of this expression.
				 * If we have a new expression, we test whether
				 * the result is saved. When this expression
				 * recurs,we test if we can still use the 
				 * variable into which it was saved.
				 * (Kind is the kind of the expression.)
				 * Returns a pointer into the list.
				 */

void	clr_avails(void);
				/* Release all space occupied by the old list
				 * of available expressions.
				 */
