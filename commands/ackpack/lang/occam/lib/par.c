/* $Id: par.c,v 1.1 2005/09/01 12:13:23 beng Exp $ */
/*	par.c - Routines to simulate parallelism */
#include <stdlib.h>
#include <unistd.h>
#include "ocm_proc.h"

static
void
DEADLOCK(void)
{
	write(2, "DEADLOCK\n", 9);
	abort();
}

static
void
search_next(void)
/* Tries to resume the active process, if this is not possible, the process
 * tree will be searched for another process. If the process tree is fully
 * traversed, search will restart at the root of the tree.
 */
{
	while (*group->active==nil && group->up!=nil) {
		save_between(group);

		group=group->up;

		group->active= &(*group->active)->next;
	}

	if (*group->active==nil) {
		if (++deadlock>1) DEADLOCK();
		group->active= &group->first;
	}

	highest_group=group;

	while ((*group->active)->down!=nil) {
		group=(*group->active)->down;
		group->active= &group->first;
	}
	top_load((*group->active)->stack);
}

void
resumenext(void)
/* Stops the current process, by saving its stack,  and determines a new one
 * to restart. In case the root of the process tree is passed more then once,
 * without a process  having done something useful, we'll have a deadlock.
 */
{
	if (group!=nil) {
		register struct process *proc= *group->active;
		register wordsize size;

		size=top_size(group->s_brk);
		proc->stack=alloc((unsigned) size);

		if (top_save(size, proc->stack)) {
			group->active= &proc->next;
			search_next();
		} else {
			free(proc->stack);
			load_betweens();
		}
	} else
		if (++deadlock>1) DEADLOCK();
}

void
parend(void)
/* Deletes the current process from its process group and searches for a new
 * process to run. The entire group is removed if this is the last process in
 * the group, execution then continues with the process that set up this group
 * in the first place.
 */
{
	register struct process *junk;

	junk= *group->active;
	*group->active=junk->next;
	free((void *) junk);

	if (group->first==nil) {
		register struct procgroup *junk;

		delete_between(group);

		junk=group;
		group=group->up;
		free((void *) junk);

		if (group!=nil)
			(*group->active)->down=nil;
	} else {
		deadlock=0;
		search_next();
	}
}
