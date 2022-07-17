/* $Header: /cvsup/minix/src/lib/libp/wdw.c,v 1.1.1.1 2005/04/21 14:56:24 beng Exp $ */
/*
 * (c) copyright 1983 by the Vrije Universiteit, Amsterdam, The Netherlands.
 *
 *          This product is part of the Amsterdam Compiler Kit.
 *
 * Permission to use, sell, duplicate or disclose this software must be
 * obtained in writing. Requests for such permissions may be sent to
 *
 *      Dr. Andrew S. Tanenbaum
 *      Wiskundig Seminarium
 *      Vrije Universiteit
 *      Postbox 7161
 *      1007 MC Amsterdam
 *      The Netherlands
 *
 */

#include	<pc_file.h>

extern struct file	*_curfil;
extern			_incpt();

char *_wdw(f) struct file *f; {

	_curfil = f;
	if ((f->flags & (WINDOW|WRBIT|0377)) == MAGIC)
		_incpt(f);
	return(f->ptr);
}
