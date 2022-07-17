/* $Id: BadAssert.c,v 1.3 2005/09/01 12:13:24 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* _BadAssertion: used for debugging purposes. It should give an error message
	indicated by the parameters, and then give a core dump
*/

#include <system.h>

static
void
wr_num(FILE *fd,size_t n)
{
	char s[2];

	s[1] = '\0';
	if (n >= 10) {
		wr_num(fd, n/10);
	}
	s[0] = (n % 10) + '0';
	sys_write(fd, s, 1);
}

int
_BadAssertion(const char *file,int lineno,const char *assertion)
{

	sys_write(stderr, file, strlen(file));
	sys_write(stderr, ", line ", 7);
	wr_num(stderr, lineno);
	sys_write(stderr, ": assertion \"", 13);
	sys_write(stderr, assertion, strlen(assertion));
	sys_write(stderr, "\" failed\n", 9);
	abort( );
	return 0;
}
