/* $Header: /cvsup/minix/src/lib/libp/rln.c,v 1.1.1.1 2005/04/21 14:56:23 beng Exp $ */
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

extern		_rf();
extern		_incpt();

_rln(f) struct file *f; {

	_rf(f);
	while ((f->flags & ELNBIT) == 0)
		_incpt(f);
	f->flags &= ~WINDOW;
}
