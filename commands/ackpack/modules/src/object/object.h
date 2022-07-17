/* $Id: object.h,v 1.3 2005/09/01 12:13:26 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#ifndef __OBJECT_INCLUDED__
#define __OBJECT_INCLUDED__

#include "system.h"

/* Structures defined in arch.h, ranlib.h */
struct outhead;
struct outsect;
struct outrelo;
struct outname;
struct ar_hdr;
struct ranlib;

int wr_open(char *f);
void wr_close(void);
void wr_ohead(struct outhead *h);
void wr_sect(struct outsect *s, unsigned int c);
void wr_outsect(int sectno);
void wr_emit(char *b, long c);
void wr_putc(int c);
void wr_relo(struct outrelo *r, unsigned int c);
void wr_name(struct outname *n, unsigned int c);
void wr_string(char *s, long c);
void wr_arhdr(FILE * fp, struct ar_hdr *a);
void wr_ranlib(FILE * fp, struct ranlib *r, long cnt);
void wr_int2(FILE * fp, int i);
void wr_long(FILE * fp, long l);
void wr_bytes(FILE * fp, char *buf, long l);
int rd_open(char *f);
int rd_Fileopen(FILE *f);
void rd_close(void);
void rd_ohead(struct outhead *h);
void rd_sect(struct outsect *s, unsigned int c);
void rd_outsect(int sectno);
void rd_emit(char *b, long c);
void rd_relo(struct outrelo *r, unsigned int c);
void rd_rew_relo(struct outhead *head);
void rd_name(struct outname *n, unsigned int c);
void rd_string(char *s, long c);
int rd_arhdr(FILE * fp, struct ar_hdr *a);
void rd_ranlib(FILE * fp, struct ranlib *r, long cnt);
int rd_int2(FILE * fp);
long rd_long(FILE * fp);
void rd_bytes(FILE * fp, char *buf, long l);
FILE * rd_File(void);
unsigned int rd_unsigned2(FILE * fp);

/* Code linking to this module is expected to implement: */
void rd_fatal(void);		/* FATAL error during reading */
void wr_fatal(void);		/* FATAL error during writing */

#endif /* __OBJECT_INCLUDED__ */
