/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: lookup.h,v 1.3 2005/09/01 12:13:34 beng Exp $ */

#define IDL	100

struct sym {
	sym_p	s_next;
	offset	*s_rom;
	short	s_flags;
	short	s_frag;
	offset	s_value;
	char	s_name[2];	/* to be extended up to IDL */
};

/* contents of .s_flags */
#define SYMPRO		000001
#define SYMGLOBAL	000002
#define SYMKNOWN	000004
#define SYMOUT		000010
#define SYMDEF		000020
#define SYMSEEN		000040

#define NSYMHASH	127
extern sym_p symhash[NSYMHASH];

sym_p symlookup(char * name,int status,int flags);
#define OCCURRING	0
#define DEFINING	1
#define NOTHING		2
