#include <time.h>

/* $Id: now.c,v 1.1 2005/09/01 12:13:23 beng Exp $ */

extern int deadlock;

long
now(void)
{
	deadlock = 0;
	return time((long *) 0);
}
