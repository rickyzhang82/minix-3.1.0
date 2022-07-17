/* $Id: cs_entity.h,v 1.3 2005/09/01 12:13:30 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
extern lset	entities;	/* The pseudo-symboltable. */

entity_p	find_entity(valnum);
				/* Tries to find an entity with value number vn.
				 */

entity_p	en_enter(entity_p);
				/* Enter the entity in enp in the set of
				 * entities if it was not already there.
				 */

void	clr_entities(void);
				/* Release all space occupied by our
				 * pseudo-symboltable.
				 */
