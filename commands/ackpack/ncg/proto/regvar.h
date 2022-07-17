/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: regvar.h,v 1.1 2005/09/01 12:13:28 beng Exp $ */

struct regvar {
	struct regvar  *rv_next;
	long		rv_off;
	int		rv_size;
	int		rv_type;
	int		rv_score;
	int		rv_reg;
};

struct regassigned {
	struct regvar  *ra_rv;
	int		ra_score;
};

extern struct regvar *rvlist;
extern int nregvar[];
extern struct regassigned *regassigned[];
