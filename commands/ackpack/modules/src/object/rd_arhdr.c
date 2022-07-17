/* $Id: rd_arhdr.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include "obj.h"

int
rd_arhdr(FILE *fd,struct ar_hdr *arhdr)
{
	char buf[AR_TOTAL];
	register char *c = buf;
	register char *p = arhdr->ar_name;
	size_t i;

	if( 0 == sys_read(fd, c, AR_TOTAL, &i) || (0 != i && AR_TOTAL != i))
		rd_fatal();
	else
	if( 0 == i )
		return 0;
	i = 14;
	while (i--) {
		*p++ = *c++;
	}
	arhdr->ar_date = ((long) get2(c)) << 16; c += 2;
	arhdr->ar_date |= ((long) get2(c)) & 0xffff; c += 2;
	arhdr->ar_uid = *c++;
	arhdr->ar_gid = *c++;
	arhdr->ar_mode = get2(c); c += 2;
	arhdr->ar_size = (long) get2(c) << 16; c += 2;
	arhdr->ar_size |= (long) get2(c) & 0xffff;
	return 1;
}
