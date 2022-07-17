/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

/* E X P R E S S I O N   C H E C K I N G */

/* $Id: chk_expr.h,v 1.1 2005/09/01 12:13:21 beng Exp $ */

extern int	(*ExprChkTable[])(t_node **,int);	/* table of expression checking
					   functions, indexed by node class
					*/
extern int	(*DesigChkTable[])(t_node **,int);	/* table of designator checking
					   functions, indexed by node class
					*/

#define	ChkExpression(expp)	((*ExprChkTable[(*expp)->nd_class])(expp,D_USED))
#define ChkDesig(expp, flags)	((*DesigChkTable[(*expp)->nd_class])(expp,flags))

/* handle reference counts for sets */
#define inc_refcount(s)		(*((int *)(s) - 1) += 1)
#define dec_refcount(s)		(*((int *)(s) - 1) -= 1)
#define refcount(s)		(*((int *)(s) - 1))
