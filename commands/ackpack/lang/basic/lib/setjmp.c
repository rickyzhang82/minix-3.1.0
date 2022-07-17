#include <setjmp.h>

/* $Id: setjmp.c,v 1.1 2005/09/01 12:13:18 beng Exp $ */

/* setjmp() is defined as a macro in <setjmp.h>, but the basic compiler
 * emits calls to setjmp. Redirect the basic 'setjmp' through to the
 * Minix system setjmp.
 */

int (setjmp)(jmp_buf env)
{
  return setjmp( env );
}

