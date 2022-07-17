/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

/* T O K E N N A M E   S T R U C T U R E */

/* $Id: tokenname.h,v 1.1 2005/09/01 12:13:22 beng Exp $ */

struct tokenname	{	/*	Used for defining the name of a
					token as identified by its symbol
				*/
	int tn_symbol;
	char *tn_name;
};
