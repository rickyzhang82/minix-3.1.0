/* $Id: sr_iv.h,v 1.3 2005/09/01 12:13:32 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* S R _ I V . H  */

void induc_vars(loop_p loop,lset *ivars,lset *vars);
				/* Find the set of induction variables
				 * of the loop. Also find the set of (local)
				 * variables that are changed.
				 */
