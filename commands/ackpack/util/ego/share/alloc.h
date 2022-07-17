/* $Id: alloc.h,v 1.3 2005/09/01 12:13:32 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*  I N T E R M E D I A T E   C O D E
 *
 *  C O R E   A L L O C A T I O N   A N D   D E A L L O C A T I O N
 */

#include <stdlib.h>		/* size_t */

#ifdef DEBUG
void *newcore(int);
void oldcore(void *,int);
#else
void *myalloc(size_t);
#define newcore(size) myalloc(size)
#define oldcore(p,size) free(p)
#endif

#define newstruct(t)	((struct t *) newcore (sizeof (struct t)))
#define oldstruct(t,p)	oldcore(p,sizeof (struct t))

line_p	newline(int optype);
arg_p	newarg(int kind);
void	**newmap(short length);
cset	newbitvect(int nrbytes);
cond_p 	newcondtab(int l);


void oldline(line_p) ;
void oldargs(arg_p) ;
void oldargb(argb_p) ;
void oldobjects(obj_p) ;
void olddblock(dblock_p) ;
void oldmap(void *mp,short length);	/* Release array of pointers */
void oldbitvect(cset,int);
void oldcondtab(cond_p);

short *newtable(short);
void oldtable(short*mp,short length);

#define newdblock()	(dblock_p) newstruct(dblock)
#define newobject()	(obj_p) newstruct(obj)
#define newproc()	(proc_p) newstruct(proc)
#define newargb()	(argb_p) newstruct(argbytes)
#define newbblock()	(bblock_p) newstruct(bblock)
#define newelem()	(elem_p) newstruct(elemholder)
#define newloop()	(loop_p) newstruct(loop)
#define newuse()	(use_p) newstruct(use)
#define newchange()	(change_p) newstruct(change)
#define newlocal()	(local_p) newstruct(local)

#define oldproc(x)	oldstruct(proc,x)
#define oldbblock(x)	oldstruct(bblock,x)
#define oldelem(x)	oldstruct(elemholder,x)
#define oldloop(x)	oldstruct(loop,x)
#define olduse(x)	oldstruct(use,x)
#define oldchange(x)	oldstruct(change,x)
#define oldlocal(x)	oldstruct(local,x)
