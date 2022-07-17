/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: param.h,v 1.3 2005/09/01 12:13:35 beng Exp $ */

#define LONGOFF		/* if defined long offsets are used */

#define TRUE	1
#define FALSE	0

#define MAXROM	3

#define op_lab	(sp_lmnem+1)
#define op_last	op_lab
#define ps_sym	(sp_lpseu+1)
#define ps_last	ps_sym

#define BMASK	255	/* 0377 is unsigned, which may cause problems */
