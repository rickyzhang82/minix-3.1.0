/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: align.h,v 1.1 2005/09/01 12:13:19 beng Exp $ */
/*	 A L I G N M E N T   D E F I N I T I O N S	*/

#include "nocross.h"
#include "trgt_sizes.h"

#ifndef NOCROSS
extern int
	short_align, word_align, int_align, long_align,
	float_align, double_align, lngdbl_align,
	pointer_align,
	struct_align, union_align;
#else /* NOCROSS */
#define short_align	((int)AL_SHORT)
#define word_align	((int)AL_WORD)
#define int_align	((int)AL_INT)
#define long_align	((int)AL_LONG)
#define float_align	((int)AL_FLOAT)
#define double_align	((int)AL_DOUBLE)
#define	lngdbl_align	((int)AL_LNGDBL)
#define pointer_align	((int)AL_POINTER)
#define struct_align	((int)AL_STRUCT)
#define union_align	((int)AL_UNION)
#endif /* NOCROSS */
