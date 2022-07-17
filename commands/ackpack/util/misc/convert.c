/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#ifndef NORCSID
static char rcsid[] = "$Id: convert.c,v 1.3 2005/09/01 12:13:34 beng Exp $";
#endif

/*	This program converts either human-readable or compact EM
	assembly code to calls of the procedure-interface.
	It must be linked with two libraries:
	- a library to read EM code, according to read_em(3)
	- a library implementing the em_code(3) interface.
	Thus, this program could serve as an EM_encoder, an
	EM_decoder, or some code generator, depending on how it is
	linked.
*/

#include	<stdarg.h>
#include	<system.h>
#include	<em_pseu.h>
#include	<em_mnem.h>
#include	<em_spec.h>
#include	<em_flag.h>
#include	<em_ptyp.h>
#include	<em.h>
#include	<em_comp.h>

char *filename;			/* Name of input file */
int errors;			/* Number of errors */
extern char *C_error;

int C_out(struct e_instr *);

/* VARARGS */
void
verror(const char *s,va_list va)
{
	fprintf(stderr,
		"%s, line %d: ",
		filename ? filename : "standard input",
		EM_lineno);
	vfprintf(stderr,s,va);
	fprintf(stderr, "\n");
	errors++;
}

/* VARARGS */
void
error(const char *s,...)
{
	va_list va;

	va_start(va,s);
	verror(s,va);
	va_end(va);
}

/* VARARGS */
void
fatal(const char *s,...)
{
	va_list va;
	if (C_busy()) C_close();
	va_start(va,s);
	verror(s,va);
	va_end(va);
	exit(1);
}

int
main(int argc,char *argv[])
{
	struct e_instr buf;
	register struct e_instr *p = &buf;

	if (argc >= 2) {
		filename = argv[1];
	}
	else	filename = 0;
	if (!EM_open(filename)) {
		fatal(EM_error);
	}
	EM_getinstr(p);
	C_init((arith) EM_wordsize, (arith) EM_pointersize);
	if (argc >= 3) {
		if (!C_open(argv[2])) {
			fatal("C_open failed");
		}
	}
	else	if (!C_open( (char *) 0)) fatal("C_open failed");
	C_magic();
	while (p->em_type != EM_EOF) {
		if (p->em_type == EM_FATAL) {
			fatal("%s", EM_error);
		}
		if (EM_error) {
			error("%s", EM_error);
		}
		if (p->em_type != EM_ERROR && !C_out(p)) {
			error("%s", C_error);
		}
		EM_getinstr(p);
	}
	C_close();
	EM_close();
	return errors;
}

