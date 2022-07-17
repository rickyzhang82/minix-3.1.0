/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

/* M I S C E L L A N E O U S */

/* $Id: misc.h,v 1.1 2005/09/01 12:13:21 beng Exp $ */

#define is_anon_idf(x)		((x)->id_text[0] == '#')
#define id_not_declared(x)	(not_declared("identifier", (x), ""))
