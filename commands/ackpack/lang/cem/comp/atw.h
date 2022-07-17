/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: atw.h,v 1.1 2005/09/01 12:13:19 beng Exp $ */
/* Align To Word boundary Definition	*/

#include "sizes.h"

#define	ATW(arg)	((((arg) + ((int)word_size - 1)) / word_size) * word_size)
