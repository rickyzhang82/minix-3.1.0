/* $Id: sr_aux.h,v 1.3 2005/09/01 12:13:32 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*  S R _ A U X . H  */


bool is_loopconst(line_p l,lset vars);
				/* See if l is a loop-constant. vars is the
				 * set of variables changed in the loop.
				 */
bool is_caddress(line_p lnp,lset vars);
				/* See if l loads a loop-invariant entity of
				 * size pointer-size.
				 */
int elemsize(line_p l);
				/* l is an instruction that loads an array
				 * descriptor. Try to determine the size
				 * of the array elements.
				 */
void concatenate(line_p list1,line_p list2);
				/* Append list2 to the end of list1
				 */
#define is_const(l)	(INSTR(l) == op_loc)
