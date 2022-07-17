/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: property.h,v 1.3 2005/09/01 12:13:34 beng Exp $ */

typedef struct propinfo {
	int	pr_size;
	unsigned short	pr_regset[SZOFSET(MAXREGS)];
} propinfo;

extern struct propinfo l_props[];
