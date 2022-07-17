/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: glosym.h,v 1.1 2005/09/01 12:13:27 beng Exp $ */

typedef struct glosym {
	struct glosym *gl_next;
	string	       gl_name;
	word	       gl_rom[MAXROM+1];
} glosym_t,*glosym_p;
