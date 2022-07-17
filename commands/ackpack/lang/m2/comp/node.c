/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 * Author: Ceriel J.H. Jacobs
 */

/* N O D E   O F   A N   A B S T R A C T   P A R S E T R E E */

/* $Id: node.c,v 1.1 2005/09/01 12:13:21 beng Exp $ */

#include	"debug.h"

#include	<em_label.h>
#include	<em_arith.h>
#include	<alloc.h>
#include	<system.h>

#include	"prototypes.h"
#include	"main.h"

static int	nsubnodes[] = {
	0,
	2,
	2,
	2,
	2,
	2,
	1,
	1,
	2,
	1,
	2,
	1,
	2
};

t_node *
getnode(int class)
{
	register t_node *nd = new_node();

	if (options['R']) nd->nd_flags |= ROPTION;
	if (options['A']) nd->nd_flags |= AOPTION;
	nd->nd_class = class;
	return nd;
}

t_node *
dot2node(int class,t_node *left,t_node *right)
{
	register t_node *nd = getnode(class);

	nd->nd_symb = dot.tk_symb;
	nd->nd_lineno = dot.tk_lineno;
	nd->nd_LEFT = left;
	nd->nd_RIGHT = right;
	return nd;
}

t_node *
dot2leaf(int class)
{
	register t_node *nd = getnode(class);

	nd->nd_token = dot;
	switch(nsubnodes[class]) {
	case 1:
		nd->nd_NEXT = 0;
		break;
	case 2:
		nd->nd_LEFT = 0;
		nd->nd_RIGHT = 0;
		break;
	}
	return nd;
}

void
FreeNode(t_node *nd)
{
	/*	Put nodes that are no longer needed back onto the free
		list
	*/
	if (!nd) return;
	switch(nsubnodes[nd->nd_class]) {
	case 2:
		FreeNode(nd->nd_LEFT);
		FreeNode(nd->nd_RIGHT);
		break;
	case 1:
		FreeNode(nd->nd_NEXT);
		break;
	}
	free_node(nd);
}

/*ARGSUSED*/
int
NodeCrash(t_node *expp,label ignored1,int ignored2)
{
	crash("(NodeCrash) Illegal node");
	/* Never returns; but conform to the interface */
	return 0;
}

/*ARGSUSED*/
int
PNodeCrash(t_node **expp,int ignored)
{
	crash("(PNodeCrash) Illegal node");
	/* Never returns; but conform to the interface */
	return 0;
}

#ifdef DEBUG

void
indnt(int lvl)
{
	while (lvl--) {
		print("  ");
	}
}

void
printnode(t_node *nd,int lvl)
{
	indnt(lvl);
	print("Class: %d; Symbol: %s; Flags: %d\n", nd->nd_class, symbol2str(nd->nd_symb), nd->nd_flags);
	if (nd->nd_type) {
		indnt(lvl);
		print("Type: ");
		DumpType(nd->nd_type);
		print("\n");
	}
}

void
PrNode(t_node *nd,int lvl)
{
	if (! nd) {
		indnt(lvl); print("<nilnode>\n");
		return;
	}
	printnode(nd, lvl);
	switch(nsubnodes[nd->nd_class]) {
	case 1:
		PrNode(nd->nd_LEFT, lvl + 1);
		PrNode(nd->nd_RIGHT, lvl + 1);
		break;
	case 2:
		PrNode(nd->nd_NEXT, lvl + 1);
		break;
	}
}
#endif /* DEBUG */
