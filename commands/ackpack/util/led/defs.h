/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: defs.h,v 1.3 2005/09/01 12:13:33 beng Exp $ */

/*
 * We need the S_EXT because we leave locals alone.
 */
#define ISUNDEFINED(n)	(((n)->on_type & (S_TYP | S_EXT)) == (S_UND | S_EXT))
#define ISABSOLUTE(n)	(((n)->on_type & (S_TYP | S_EXT)) == (S_ABS | S_EXT))
#define ISCOMMON(n)	(((n)->on_type & (S_COM | S_EXT)) == (S_COM | S_EXT))

#define mustsavelocal(name)	(!((name)->on_type & S_SCT))
