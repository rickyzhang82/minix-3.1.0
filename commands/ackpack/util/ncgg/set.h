/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: set.h,v 1.3 2005/09/01 12:13:34 beng Exp $ */

#define BIS(sp,n) (sp)[(n)>>4] |= 1<<((n)&0xF)
#define BIC(sp,n) (sp)[(n)>>4] &= ~(1<<((n)&0xF))
#define BIT(sp,n) (((sp)[(n)>>4]&(1<<((n)&0xF)))!=0)
