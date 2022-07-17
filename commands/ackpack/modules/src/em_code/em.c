/* $Id: em.c,v 1.3 2005/09/01 12:13:25 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* EM CODE OUTPUT ROUTINES */

/*	I/O part of em_code module.
	Also contains C_open, C_close
*/
#include <alloc.h>
#include <em_arith.h>
#include <stdio.h>
#include <stdlib.h>
#include "insert.h"
#include "em_private.h"
#include "ack_string.h"

/* Always binary files */
#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

int		C_ontmpfile = 0;
int		C_sequential = 1;
Part		*C_curr_part;
void		(*C_outpart)(int), (*C_swtout)(void), (*C_swttmp)(void);

#ifdef INCORE
char		*C_BASE;
#endif

FILE		*C_ofp;

#ifndef INCORE
FILE		*C_tfr;
char		*C_tmpfile;
char		*strcpy(), *strcat();
char		*C_ibuf = 0;
long		C_current_out;
#endif

#if ACK_BUFSIZ <= 1024 && BIGMACHINE
#define BUFFERSIZ	8*ACK_BUFSIZ
#else
#define BUFFERSIZ	ACK_BUFSIZ
#endif

static char	obuf[BUFFERSIZ];
char		*C_top = &obuf[BUFFERSIZ];
#ifdef INCORE
char		*C_current_out = obuf;
#else
char		*C_opp = obuf;
#endif

void
C_flush(void)
{
#ifdef INCORE
	static unsigned int bufsiz;

	if (C_ontmpfile) {
		if (C_BASE == 0) {
			C_BASE = Malloc(BUFFERSIZ);
			bufsiz = BUFFERSIZ;
			C_current_out = C_BASE;
		}
		else {
			C_BASE = Realloc(C_BASE, (bufsiz << 1));
			C_current_out = C_BASE + bufsiz;
			bufsiz <<= 1;
		}
		C_top = C_BASE + bufsiz;
		return;
	}
#endif
	if (C_opp != obuf && sys_write(C_ofp, obuf, (size_t)(C_opp - obuf)) == 0) {
		C_ofp = 0;
		C_failed();
	}
	C_opp = obuf;
}

#ifndef INCORE
#define Xputbyte(c) if (C_ontmpfile) C_current_out++; put(c)
#else
#define Xputbyte(c) put(c)
#endif

void
C_putbyte(int c)
{
	Xputbyte(c);
}

#if BIGMACHINE
# define C_putbyte Xputbyte
#endif

/*ARGSUSED*/
void
C_init(arith w_ignored,arith p_ignored)
{
}

int
C_open(const char *nm)
{
	/*	Open file "nm" for output
	*/

	if (nm == 0)
	{
		C_ofp = stdout;	/* standard output	*/
#ifndef READABLE_EM
#ifdef _WIN32
		setmode( 1, _O_BINARY );
#endif
#endif
	}
	else
	{
#ifdef READABLE_EM
		C_ofp = fopen( nm, "w" );
#else
		C_ofp = fopen( nm, "wb" );
#endif
		if( 0 == C_ofp )
			return 0;
	}
	return 1;
}

void
C_close(void)
{
	/*	Finish the code-generation.
	*/

#ifndef INCORE
	C_flush();
	if (C_tmpfile) {
		(*C_swttmp)();
		fclose(C_ofp);
#else
	if (C_BASE) {
#endif
		if (C_curr_part) {
			C_curr_part->p_parts->pp_end = C_current_out - C_BASE;
		}
		(*C_swtout)();
		if (! C_sequential) {
			(*C_outpart)(0);
		}
#ifndef INCORE
		fclose(C_tfr);
		unlink(C_tmpfile);
		if (C_ibuf) free(C_ibuf);
#else
		free(C_BASE);
#endif
	}
	C_flush();
	if (C_ofp != stdout)
		fclose(C_ofp);
	C_ofp = 0;
}

int
C_busy(void)
{
	return C_ofp != 0; /* true if code is being generated */
}

#ifdef READABLE_EM
/*
	The C_pt_*() functions serve as formatting functions of the
	various EM language constructs.
	See "Description of a Machine Architecture for use with
	Block Structured Languages" par. 11.2 for the meaning of these
	names.
*/

void
C_magic(void)
{
}

/***    the readable code generating routines	***/

static
void
wrs(const char *s)
{
	while (*s) {
		C_putbyte(*s++);
	}
}

void
C_pt_dnam(const char *s)
{
	wrs(s);
}

void
C_pt_ilb(label l)
{
	char buf[16];

	sprintf(buf, "*%ld", (long) l);
	wrs(buf);
}

extern char em_mnem[][4];
extern char em_pseu[][4];

void
C_pt_op(int x)
{
	C_putbyte(' ');
	wrs(em_mnem[x - sp_fmnem]);
	C_putbyte(' ');
}

void
C_pt_cst(arith l)
{
	char buf[16];

	sprintf(buf, "%ld", (long) l);
	wrs(buf);
}

void
C_pt_scon(const char *x,arith y)
{
	char xbuf[1024];
	register const char *p;

	C_putbyte('\'');
	p = bts2str(x, (int) y, xbuf);
	while (*p) {
		if (*p == '\'') {
			C_putbyte('\\');
		}
		C_putbyte(*p++);
	}
	C_putbyte('\'');
}

void
C_pt_ps(int x)
{
	C_putbyte(' ');
	wrs(em_pseu[x - sp_fpseu]);
	C_putbyte(' ');
}

void
C_pt_dlb(label l)
{
	char buf[16];

	sprintf(buf, ".%ld", (long) l);
	wrs(buf);
}

void
C_pt_doff(label l,arith v)
{
	char buf[16];

	C_pt_dlb(l);
	if (v != 0) {
		sprintf(buf,"+%ld", (long) v);
		wrs(buf);
	}
}

void
C_pt_noff(const char *s,arith v)
{
	char buf[16];

	wrs(s);
	if (v != 0) {
		sprintf(buf,"+%ld", (long) v);
		wrs(buf);
	}
}

void
C_pt_pnam(const char *s)
{
	C_putbyte('$');
	wrs(s);
}

void
C_pt_dfilb(label l)
{
	char buf[16];

	sprintf(buf, "%ld", (long) l);
	wrs(buf);
}

void
C_pt_wcon(int sp,const char *v,arith sz) /* sp_icon, sp_ucon or sp_fcon with int repr	*/
{
	int ch = sp == sp_icon ? 'I' : sp == sp_ucon ? 'U' : 'F';

	wrs(v);
	C_putbyte(ch);
	C_pt_cst(sz);
}

void
C_pt_nl(void)
{
	C_putbyte('\n');
}

void
C_pt_comma(void)
{
	C_putbyte(',');
}

void
C_pt_ccend(void)
{ 
	C_putbyte('?');
}

#else /* READABLE_EM */

#define	put8(x)		C_putbyte(x)
#define	put16(x)	put8((int) x); put8((int) (x >> 8))
#define	put32(x)	put16((int) x); put16((int) (x >> 16))

/*
	The C_pt_*() functions serve as formatting functions of the
	various EM language constructs.
	See "Description of a Machine Architecture for use with
	Block Structured Languages" par. 11.2 for the meaning of these
	names.
*/

void
C_magic(void)
{
	put16(sp_magic);
}

/***    the compact code generating routines	***/
#define	fit16i(x)	((x) >= (long)0xFFFF8000 && (x) <= (long)0x00007FFF)
#define	fit8u(x)	((x) <= 0xFF)		/* x is already unsigned */

void
C_pt_ilb(label l)
{
	if (fit8u(l))	{
		put8(sp_ilb1);
		put8((int)l);
	}
	else	{
		put8(sp_ilb2);
		put16((int)l);
	}
}

void
C_pt_dlb(label l)
{
	if (fit8u(l))	{
		put8(sp_dlb1);
		put8((int)l);
	}
	else	{
		put8(sp_dlb2);
		put16((int)l);
	}
}

void
C_pt_cst(arith l)
{
	if (l >= (arith) -sp_zcst0 && l < (arith) (sp_ncst0 - sp_zcst0)) {
		/*	we can convert 'l' to an int because its value
			can be stored in a byte.
		*/
		put8((int)l + (sp_zcst0 + sp_fcst0));
	}
	else
	if (fit16i(l)) { /* the cast from long to int causes no trouble here */
		put8(sp_cst2);
		put16((int) l);
	}
	else	{
		put8(sp_cst4);
		put32(l);
	}
}

void
C_pt_doff(label l,arith v)
{
	if (v == 0) {
		C_pt_dlb(l);
	}
	else	{
		put8(sp_doff);
		C_pt_dlb(l);
		C_pt_cst(v);
	}
}

void
C_pt_str(const char *s)
{
	register int len;

	C_pt_cst((arith) (len = strlen(s)));
	while (--len >= 0) {
		put8(*s++);
	}
}

void
C_pt_dnam(const char *s)
{
	put8(sp_dnam);
	C_pt_str(s);
}

void
C_pt_noff(const char *s,arith v)
{
	if (v == 0) {
		C_pt_dnam(s);
	}
	else	{
		put8(sp_doff);
		C_pt_dnam(s);
		C_pt_cst(v);
	}
}

void
C_pt_pnam(const char *s)
{
	put8(sp_pnam);
	C_pt_str(s);
}

void
C_pt_wcon(int sp,const char *v,arith sz) /* sp_icon, sp_ucon or sp_fcon with int repr	*/
{
	/* how 'bout signextension int --> long ???	*/
	put8(sp);
	C_pt_cst(sz);
	C_pt_str(v);
}

void
C_pt_scon(const char *b,arith n)
{
	put8(sp_scon);
	C_pt_cst(n);
	while (--n >= 0) {
		put8(*b++);
	}
}
#endif /* READABLE_EM */
