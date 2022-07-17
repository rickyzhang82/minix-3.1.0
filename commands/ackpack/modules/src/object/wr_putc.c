/* $Id: wr_putc.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include "obj.h"

extern int __sectionnr;
void __wr_flush(struct fil *ptr);

void
wr_putc(int ch)
{
	register struct fil *ptr = &__parts[PARTEMIT+getsect(__sectionnr)];

	if (ptr->cnt == 0) __wr_flush(ptr);
	ptr->cnt--; *ptr->pnow++ = ch;
}
