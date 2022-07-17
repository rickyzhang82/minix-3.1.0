/* $Id: debug.h,v 1.3 2005/09/01 12:13:32 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* D E B U G G I N G   T O O L S */

/* TEMPORARY: */
/* #define DEBUG */

extern int		linecount;	/* # lines in this file */
extern bool		verbose_flag;  /* generate verbose output ? */

/* VARARGS 1 */
void error(char *,...);


#ifdef TRACE
extern OUTTRACE();
#else
#define OUTTRACE(s,n)
#endif
#ifdef VERBOSE
extern void OUTVERBOSE();
#else
#define OUTVERBOSE(s,n1,n2)
#endif
#ifdef DEBUG

/* Some (all?) Unix debuggers don't particularly like
 * static procedures and variables. Therefor we make everything
 * global when debugging.
 */

#define STATIC

void badassertion(char *file,unsigned int line);

#define assert(x) if(!(x)) badassertion(__FILE__,__LINE__)

void VA(short *a);
void VD(dblock_p d);
void VI(short i);
void VL(line_p l);
void VO(obj_p o);
void VP(proc_p p);

#else /*DEBUG*/

#define assert(b)

#define VI(i)
#define VL(l)
#define VD(d)
#define VA(a)
#define VO(o)
#define VP(p)


#define STATIC static
#endif
