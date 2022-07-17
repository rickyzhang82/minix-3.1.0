/* $Id: em_ego.h,v 1.3 2005/09/01 12:13:17 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*
 * The various different hints as given after a mes ms_ego
 *
 * Yet to be stabilized
 */

#define ego_live    0	/* ,offset,size,regno */
#define ego_dead    1	/* ,offset,size,regno */
#define ego_assoc   2	/* ,offset,size,regno */
#define ego_unass   3	/* ,offset,size,regno */
#define ego_init    4	/* ,offset,size,regno */
#define ego_update  5	/* ,offset,size,regno */
