/*
  (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
  See the copyright notice in the ACK home directory, in the file "Copyright".
*/

/*
  Module:	program termination routines
  Author:	Ceriel J.H. Jacobs
  Version:	$Header: /cvsup/minix/src/lib/libm2/halt.c,v 1.1.1.1 2005/04/21 14:56:22 beng Exp $
*/
#define MAXPROCS 32

static int callindex = 0;
static int (*proclist[MAXPROCS])();

_cleanup()
{
	while (--callindex >= 0)
		(*proclist[callindex])();
	callindex = 0;
}

CallAtEnd(p)
	int (*p)();
{
	if (callindex >= MAXPROCS) {
		return 0;
	}
	proclist[callindex++] = p;
	return 1;
}

halt()
{
	_cleanup();
	_exit(0);
}
