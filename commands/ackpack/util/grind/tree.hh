/* $Id: tree.hh,v 1.1 2005/09/01 12:13:33 beng Exp $ */

#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>

#include "position.h"

#define MAXARGS	3

typedef struct tree {
  short	t_oper;		/* tree operator */
  short t_whichoper;	/* expression operator */
  t_addr t_address;	/* some operators use an address */
  union {
	long tt_ival;
	char *tt_sval;
	double tt_fval;
	struct {
		struct idf *tt_idf;
		char *tt_str;
	} tt_x;
	struct tree *tt_args[MAXARGS];
	t_position tt_pos;
  } t_xxxx;
#define t_ival	t_xxxx.tt_ival
#define t_sval	t_xxxx.tt_sval
#define t_fval	t_xxxx.tt_fval
#define t_idf	t_xxxx.tt_x.tt_idf
#define t_str	t_xxxx.tt_x.tt_str
#define t_args	t_xxxx.tt_args
#define t_lino t_xxxx.tt_pos.lineno
#define t_filename t_xxxx.tt_pos.filename
#define t_pos	t_xxxx.tt_pos
} t_tree, *p_tree;

void freenode( p_tree );
p_tree mknode( int, ... );
t_addr get_addr_from_node( p_tree );
void print_node( FILE *, p_tree, int );
int repeatable( p_tree );
int in_status( p_tree );
void eval( p_tree );
void newfile( struct idf * );
void perform( p_tree, t_addr );
void list_position( p_position );

/* ALLOCDEF "tree" 100 */

#if __STDC__
extern p_tree	mknode(int, ...);
#else
extern p_tree	mknode();
#endif

#endif /* _TREE_H */
