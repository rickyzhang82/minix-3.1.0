/*
  (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
  See the copyright notice in the ACK home directory, in the file "Copyright".
*/

/*
  Module:	block moves
  Author:	Ceriel J.H. Jacobs
  Version:	$Header: /cvsup/minix/src/lib/libm2/blockmove.c,v 1.1.1.1 2005/04/21 14:56:22 beng Exp $
*/

#if _EM_WSIZE==_EM_PSIZE
typedef unsigned pcnt;
#else
typedef unsigned long pcnt;
#endif

blockmove(siz, dst, src)
	pcnt siz;
	register char *dst, *src;
{
	while (siz--) *dst++ = *src++;
}
