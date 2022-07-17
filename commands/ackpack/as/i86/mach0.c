/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#define RCSID0 "$Id: mach0.c,v 1.1 2005/09/01 12:13:16 beng Exp $"

/*
 * INTEL 8086 options
 */
#define	THREE_PASS	/* branch and offset optimization */
#define	LISTING		/* enable listing facilities */
#define RELOCATION	/* generate relocation info */
#define DEBUG 0

#undef valu_t
#define valu_t long

#undef ALIGNWORD
#define ALIGNWORD 2
#undef ALIGNSECT
#define ALIGNSECT 2
