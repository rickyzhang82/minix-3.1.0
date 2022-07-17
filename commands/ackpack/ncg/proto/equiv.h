/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: equiv.h,v 1.1 2005/09/01 12:13:27 beng Exp $ */

#define MAXCREG 4

struct perm {
	struct perm *p_next;
	int p_rar[MAXCREG];
};
