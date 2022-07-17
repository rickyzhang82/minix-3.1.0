/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: arith.h,v 1.1 2005/09/01 12:13:20 beng Exp $ */
/* COMPILER ARITHMETIC */

/*	Normally the compiler does its internal arithmetics in longs
	native to the source machine, which is always good for local
	compilations, and generally OK too for cross compilations
	downwards and sidewards.  For upwards cross compilation and
	to save storage on small machines, SPECIAL_ARITHMETICS will
	be handy.
*/

/*	All preprocessor arithmetic should be done in longs.
*/
#define	arith	long				/* dummy */
