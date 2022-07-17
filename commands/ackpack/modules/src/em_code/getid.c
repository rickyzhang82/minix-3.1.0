/* $Id: getid.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */

/*	Get a unique id for C_insertpart, etc.
*/

int
C_getid(void)
{
	static int id = 0;

	return ++id;
}
