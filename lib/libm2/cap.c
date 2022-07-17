/*
  (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
  See the copyright notice in the ACK home directory, in the file "Copyright".
*/

/*
  Module:	cap; implementation of CAP
  Author:	Ceriel J.H. Jacobs
  Version:	$Header: /cvsup/minix/src/lib/libm2/cap.c,v 1.1.1.1 2005/04/21 14:56:22 beng Exp $
*/

cap(u)
	unsigned u;
{
	register unsigned *p = &u;

	if (*p >= 'a' && *p <= 'z') *p += 'A'-'a';
}
