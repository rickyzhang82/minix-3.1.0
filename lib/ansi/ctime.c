/*
 * ctime - convers the calendar time to a string
 */
/* $Header: /cvsup/minix/src/lib/ansi/ctime.c,v 1.1.1.1 2005/04/21 14:56:04 beng Exp $ */

#include	<time.h>

char *
ctime(const time_t *timer)
{
	return asctime(localtime(timer));
}
