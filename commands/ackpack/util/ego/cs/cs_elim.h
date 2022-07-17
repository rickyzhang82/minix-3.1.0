/* $Id: cs_elim.h,v 1.3 2005/09/01 12:13:30 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
void  eliminate(proc_p);
			/* Eliminate some of the recurrences of expressions
			 * that were found by the valuenumbering
			 * algorithm.
			 */
