/*
 * tzset - set timezone information
 */
/* $Header: /cvsup/minix/src/lib/ansi/tzset.c,v 1.1.1.1 2005/04/21 14:56:06 beng Exp $ */

/* This function is present for System V && POSIX */

#include	<time.h>
#include	"loc_time.h"

void
tzset(void)
{
	_tzset();	/* does the job */
}
