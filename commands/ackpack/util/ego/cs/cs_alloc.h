/* $Id: cs_alloc.h,v 1.3 2005/09/01 12:13:30 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
occur_p	newoccur(line_p,line_p,bblock_p);	/*
				 * Returns a pointer to a new struct occur
				 * and initializes it.
				 */

void	oldoccur(occur_p);	/*
				 * Release the struct occur ocp points to.
				 */

avail_p	newavail(void);		/*
				 * Return a pointer to a new struct avail.
				 */

void	oldavail(avail_p);	/*
				 * Release the struct avail avp points to.
				 */

entity_p newentity(void);	/* ()
				 * Return a pointer to a new struct entity.
				 */

void	oldentity(entity_p);	/*
				 * Release the struct entity enp points to.
				 */
