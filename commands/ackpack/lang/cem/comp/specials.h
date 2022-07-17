/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: specials.h,v 1.1 2005/09/01 12:13:20 beng Exp $ */
/* OCCURANCES OF SPECIAL IDENTIFIERS */

#define	SP_SETJMP	1

#define	SP_TOTAL	1

struct sp_id	{
	char *si_identifier;	/* its name			*/
	int si_flag;		/* index into sp_occurred array	*/
};

extern char sp_occurred[];		/* idf.c	*/
extern struct sp_id special_ids[];	/* main.c	*/
