/* $Id: wr_bytes.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include "obj.h"

#define MININT		(1 << (sizeof(int) * 8 - 1))
#define MAXCHUNK	(~MININT)	/* Highest count we write(2).	*/
/* Notice that MAXCHUNK itself might be too large with some compilers.
   You have to put it in an int!
*/

static int maxchunk = MAXCHUNK;

/*
 * Just write "cnt" bytes to file-descriptor "fd".
 */
void
wr_bytes(FILE *fd,char *string,long cnt)
{

	while (cnt) {
		register size_t n = cnt >= maxchunk ? maxchunk : cnt;

		if( 0 == sys_write(fd, string, n) )
			wr_fatal();
		string += n;
		cnt -= n;
	}
}
