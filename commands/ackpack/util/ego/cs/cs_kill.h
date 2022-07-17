/* $Id: cs_kill.h,v 1.3 2005/09/01 12:13:30 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
void kill_call(proc_p);	/*
			 * Kill all entities that might have an other value
			 * after execution of the procedure in pp.
			 */

void kill_much(void);	/*
			 * Kill all killable entities except those for which
			 * a register message was generated.
			 * Constants, addresses, etc are not killable.
			 */

void kill_indir(entity_p);/*
			 * Kill all entities that might have an other value
			 * after indirect assignment to the entity in enp.
			 */

void kill_direct(entity_p);/*
			 * Kill all entities that might have an other value
			 * after direct assignment to the entity in enp.
			 */

void kill_all(void);	/*
			 * Kill all entities.
			 */
