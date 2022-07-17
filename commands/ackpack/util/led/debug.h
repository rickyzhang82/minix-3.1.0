/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: debug.h,v 1.3 2005/09/01 12:13:33 beng Exp $ */

#ifdef NDEBUG

#define debug(s, a1, a2, a3, a4)

#else
extern int DEB;

#define debug(s, a1, a2, a3, a4)	(DEB && printf(s, a1, a2, a3, a4))

#endif

extern int Verbose;
#define verbose(s, a1, a2, a3, a4)	(Verbose && do_verbose(s, a1, a2, a3, a4))
