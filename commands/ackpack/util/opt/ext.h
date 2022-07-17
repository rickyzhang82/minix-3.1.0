/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: ext.h,v 1.3 2005/09/01 12:13:34 beng Exp $ */

#ifndef FILE
#include <stdio.h>
#endif
extern	unsigned linecount;
extern	int	prodepth;
extern	bool	Lflag;
extern	bool	nflag;
extern	int	repl_muls;
extern	bool	repl_longmuls;
extern	byte	em_flag[];
extern	line_p	instrs,pseudos;
extern	FILE	*outfile;
extern	char	tmplt[];
extern	offset	wordsize;
extern	offset	pointersize;
extern	char	*progname;
