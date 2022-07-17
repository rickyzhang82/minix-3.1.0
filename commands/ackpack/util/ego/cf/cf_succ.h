/* $Id: cf_succ.h,v 1.3 2005/09/01 12:13:30 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*  C O N T R O L   F L O W
 *
 *  S U C C E S S O R  /  P R E D E C E S S O R   R E L A T I O N S
 */

void control_flow(bblock_p);
				/* Compute for every basic block
				 * its successors and predecessors
				 * in the control flow graph.
				 */
