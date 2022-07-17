/* $Id: alloc.c,v 1.3 2005/09/01 12:13:32 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*  S H A R E D   F I L E
 *
 *  A L L O C . C
 */



#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "debug.h"
#include "alloc.h"


void * myalloc(size_t);

#ifdef DEBUG

STATIC unsigned int maxuse, curruse;

void *
newcore(int size)
{
	if ((curruse += (unsigned)(size+2)) > maxuse) maxuse = curruse;
	return myalloc(size);
}

void
oldcore(void *p,int size)
{
	curruse -= (size+2);
	free(p);
}

void
coreusage(void)
{
	fprintf(stderr,"Maximal core usage (excl. buffers):%u\n",maxuse);
}

#endif


/*
 * The following two sizetables contain the sizes of the various kinds
 * of line and argument structures.
 * The assumption when making the tables was that every non-byte object
 * had to be aligned on an even boundary. On machines where alignment
 * is worse ( for example a long has to be aligned on a longword bound )
 * these tables should be revised.
 * A wasteful but safe approach is to replace every line of them by
 *  sizeof(line_t)
 * and
 *  sizeof(arg_t)
 * respectively.
 *
 * Table index defined in types.h:
 *  #define OPNO		0
 *  #define OPSHORT		1
 *  #define OPOFFSET	2
 *  #define OPINSTRLAB	3
 *  #define OPOBJECT	4
 *  #define OPPROC		5
 *  #define OPLIST		6
 */

#ifndef NOTCOMPACT

static
int
lsizetab[] = {
	2*sizeof(line_p)+2*sizeof(byte),
	2*sizeof(line_p)+2*sizeof(byte)+sizeof(short),
	2*sizeof(line_p)+2*sizeof(byte)+sizeof(offset),
	2*sizeof(line_p)+2*sizeof(byte)+sizeof(lab_id),
	2*sizeof(line_p)+2*sizeof(byte)+sizeof(obj_p),
	2*sizeof(line_p)+2*sizeof(byte)+sizeof(proc_p),
	2*sizeof(line_p)+2*sizeof(byte)+sizeof(arg_p),
};

static
int
asizetab[] = {
	sizeof(arg_p)+sizeof(short)+sizeof(offset),
	sizeof(arg_p)+sizeof(short)+sizeof(lab_id),
	sizeof(arg_p)+sizeof(short)+sizeof(obj_p),
	sizeof(arg_p)+sizeof(short)+sizeof(proc_p),
	sizeof(arg_p)+sizeof(short)+sizeof(argb_t),
	sizeof(arg_p)+sizeof(short)+sizeof(short)+sizeof(argb_t),
	sizeof(arg_p)+sizeof(short)+sizeof(short)+sizeof(argb_t),
	sizeof(arg_p)+sizeof(short)+sizeof(short)+sizeof(argb_t)
};

#else

static
int
lsizetab[] = {
	sizeof(struct line),
	sizeof(struct line),
	sizeof(struct line),
	sizeof(struct line),
	sizeof(struct line),
	sizeof(struct line),
	sizeof(struct line)
};

static
int
asizetab[] = {
	sizeof (struct arg),
	sizeof (struct arg),
	sizeof (struct arg),
	sizeof (struct arg),
	sizeof (struct arg),
	sizeof (struct arg),
	sizeof (struct arg),
	sizeof (struct arg)
};

#endif

/*
 * alloc routines:
 * Two parts:
 *   1)	typed alloc and free routines
 *   2) untyped raw core allocation
 */

/*
 * PART 1
 */

line_p
newline(int optyp)
{
	register line_p lnp;

	lnp = (line_p) newcore(lsizetab[optyp]);
	TYPE(lnp) = optyp;
	return(lnp);
}

void
oldline(line_p lnp)
{
	register int kind=TYPE(lnp)&BMASK;

	if (kind == OPLIST)
		oldargs(ARG(lnp));
	oldcore(lnp,lsizetab[kind]);
}

arg_p
newarg(int kind)
{
	register arg_p ap;

	ap = (arg_p) newcore(asizetab[kind]);
	ap->a_type = kind;
	return(ap);
}

void
oldargs(arg_p ap)
{
	register arg_p	next;

	while (ap != (arg_p) 0) {
		next = ap->a_next;
		switch(ap->a_type) {
		case ARGSTRING:
			oldargb(ap->a_a.a_string.ab_next);
			break;
		case ARGICN:
		case ARGUCN:
		case ARGFCN:
			oldargb(ap->a_a.a_con.ac_con.ab_next);
			break;
		}
		oldcore(ap,asizetab[ap->a_type]);
		ap = next;
	}
}

void
oldargb(argb_p abp)
{
	register argb_p next;

	while (abp != (argb_p) 0) {
		next = abp->ab_next;
		oldcore(abp,sizeof (argb_t));
		abp = next;
	}
}

void
oldobjects(obj_p op)
{
	register obj_p next;

	while (op != (obj_p) 0) {
		next = op->o_next;
		oldcore(op, sizeof(struct obj));
		op = next;
	}
}

void
olddblock(dblock_p dbl)
{
	oldobjects(dbl->d_objlist);
	oldargs(dbl->d_values);
	oldcore(dbl, sizeof(struct dblock));
}


void **
newmap(short length)
{
	return (void **)newcore((length+1) * sizeof(void *));
}

/* More strictly, have an array of pointers */
void
oldmap(void *mp,short length)
{
	oldcore( mp, (length+1) * sizeof(void *));
}


cset
newbitvect(int n)
{
	return((cset) newcore((n-1)*sizeof(int) + sizeof(struct bitvector)));
	/* sizeof(struct bitvector) equals to the size of a struct with
	 * one short, followed by one ALLIGNED int. So the above statement
	 * also works e.g. on a VAX.
	 */
}

/*ARGSUSED1*/
void
oldbitvect(cset s,int n)
{
	oldcore((void *) s, (n-1)*sizeof(int) + sizeof(struct bitvector));
}


short*
newtable(short length)
{
	return (short*)newcore((length+1) * sizeof(short));
}

/*ARGSUSED1*/
void
oldtable(short*mp,short length)
{
	oldcore(mp, (length+1) * sizeof(short));
}

cond_p
newcondtab(int l)
{
	return (cond_p) newcore(l * (sizeof (struct cond_tab)));
}

void
oldcondtab(cond_p tab)
{
	int i;
	for (i = 0; tab[i].mc_cond != DEFAULT; i++);
	oldcore(tab,((i+1) * sizeof (struct cond_tab)));
}


void *
myalloc(size_t size)
{
	register void *p;

	p = calloc(size, 1);
	if (p == 0)
		error("out of memory");
	return(p);
}
