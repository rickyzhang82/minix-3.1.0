/* $Id: rd_bytes.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include "obj.h"

#define MININT		(1 << (sizeof(int) * 8 - 1))
#define MAXCHUNK	(~MININT)	/* Highest count we read(2).	*/
/* Unfortunately, MAXCHUNK is too large with some  compilers. Put it in
   an int!
*/

static int maxchunk = MAXCHUNK;

/*
 * We don't have to worry about byte order here.
 * Just read "cnt" bytes from file-descriptor "fd".
 */
void 
rd_bytes(FILE *fd,char *string,long cnt)
{

	while (cnt) {
		register size_t n = ( cnt >= maxchunk ) ? maxchunk : cnt;

		size_t got;
		if( 0 == sys_read(fd, string, n, & got) || n != got )
			rd_fatal();
		string += n;
		cnt -= n;
	}
}
