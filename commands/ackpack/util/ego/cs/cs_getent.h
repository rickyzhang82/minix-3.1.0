/* $Id: cs_getent.h,v 1.3 2005/09/01 12:13:30 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
entity_p getentity(line_p,line_p*);
				/*
				 * Extract the entity lnp refers and enter it
				 * in the table of entities. The main entity
				 * lnp refers to is returned; sometimes there
				 * is more than one entity. The first line that
				 * was involved in pushing it is returned
				 * through l_out.
				 */
