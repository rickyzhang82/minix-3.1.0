/* $Id: wr_ranlib.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include "obj.h"

void
wr_ranlib(FILE *fd,struct ranlib *ran,long cnt1)
{
#if ACK_BYTE_ORDER == 0x0123
	if (sizeof (struct ranlib) != SZ_RAN)
#endif
	{
		register long cnt = cnt1;
		register struct ranlib *r = ran;
		register char *c = (char *) r;

		while (cnt--) {
			put4(r->ran_off,c); c += 4;
			put4(r->ran_pos,c); c += 4;
			r++;
		}
	}
	wr_bytes(fd, (char *) ran, cnt1 * SZ_RAN);
}
