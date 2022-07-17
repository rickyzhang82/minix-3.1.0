/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: assert.h,v 1.3 2005/09/01 12:13:24 beng Exp $ */
/*	 A S S E R T I O N    M A C R O   D E F I N I T I O N		*/

/* This 'assert' definition can be used in a ,-expression. */

#ifndef	NDEBUG
int _BadAssertion(const char *, int, const char *);
#define	assert(exp)	((void)((exp) || _BadAssertion(__FILE__, __LINE__, #exp)))
#else
#define	assert(exp)	((void)0)
#endif	/* NDEBUG */

