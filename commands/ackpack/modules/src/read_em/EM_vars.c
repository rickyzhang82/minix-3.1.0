/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: EM_vars.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */

/* Variables must be declared somewhere ... */

#include <em_arith.h>

char	*EM_error = 0;
char	*EM_filename = 0;
unsigned int EM_lineno = 0;
int	EM_wordsize = 0, EM_pointersize = 0;
arith	EM_holsize = 0;
int	EM_holinit = 0;
