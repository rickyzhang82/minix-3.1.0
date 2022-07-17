/* $Id: wr_arhdr.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include "obj.h"

void
wr_arhdr(FILE *fd,struct ar_hdr *arhdr)
{
	char buf[AR_TOTAL];
	register char *c = buf;
	register char *p = arhdr->ar_name;
	register int i = 14;

	while (i--) {
		*c++ = *p++;
	}
	put2((int)(arhdr->ar_date>>16),c); c += 2;
	put2((int)(arhdr->ar_date),c); c += 2;
	*c++ = arhdr->ar_uid;
	*c++ = arhdr->ar_gid;
	put2(arhdr->ar_mode,c); c += 2;
	put2((int)(arhdr->ar_size>>16),c); c += 2;
	put2((int)(arhdr->ar_size),c);
	wr_bytes(fd, buf, (long) AR_TOTAL);
}
