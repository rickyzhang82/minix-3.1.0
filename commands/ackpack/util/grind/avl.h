/* $Id: avl.h,v 1.1 2005/09/01 12:13:33 beng Exp $ */

/* AVL-trees: trees in which the difference in depth
   of the left branch and the right branch is at most one.
   Information in the nodes is represented by a pointer, which is to
   be supplied by the user. The user is also expected to supply a
   comparison routine for each AVL tree. This routine is offered two
   parameters, both pointers, and is expected to return:
   a negative number	if the comparison result is <
   0 			if the comparison result is =
   a positive number	if the comparison result is >
*/

typedef struct avl_tree	*AVL_tree;

/* extern AVL_tree create_avl_tree(int (*cmp)());
   Returns a fresh avl_tree structure. 'cmp' will be used as comparison
   routine for this tree.
*/
AVL_tree create_avl_tree(int (*)(char*,char*));

/* extern add_to_avl_tree(AVL_tree tree, char *n);
   Adds the information indicated by 'n' to the avl_tree indicated by 'tree'.
*/
void add_to_avl_tree(AVL_tree,char *);

/* extern char *find_ngt(AVL_tree tree, char *n);
   Returns the information in the largest node that still compares <= to 'n',
   or 0 if not present.
*/
char *find_ngt(AVL_tree,char *);

/* extern char *find_nlt(AVL_tree tree, char *n);
   Returns the information in the largest node that still compares >= to 'n',
   or 0 if not present.
*/
char *find_nlt(AVL_tree,char *);

/* extern char *find_eq(AVL_tree tree, char *n);
   Returns the information in the node that compares equal to 'n',
   or 0 if not present.
*/
char *find_eq(AVL_tree,char *);
