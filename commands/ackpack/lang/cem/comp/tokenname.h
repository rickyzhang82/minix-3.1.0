/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: tokenname.h,v 1.1 2005/09/01 12:13:20 beng Exp $ */
/* TOKENNAME DEFINITION */

struct tokenname	{	/*	Used for defining the name of a
					token as identified by its symbol
				*/
	int tn_symbol;
	char *tn_name;
};
