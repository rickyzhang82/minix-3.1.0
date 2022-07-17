/*
  (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
  See the copyright notice in the ACK home directory, in the file "Copyright".
*/

/*
  Module:	integer abs function
  Author:	Ceriel J.H. Jacobs
  Version:	$Header: /cvsup/minix/src/lib/libm2/absi.c,v 1.1.1.1 2005/04/21 14:56:22 beng Exp $
*/

absi(i)
{
	return i >= 0 ? i : -i;
}
