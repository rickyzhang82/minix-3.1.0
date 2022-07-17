/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: iocc.h,v 1.3 2005/09/01 12:13:34 beng Exp $ */

typedef struct iocc {
	unsigned short in_set[SETSIZE];
	int   in_index;
} iocc_t,*iocc_p;
