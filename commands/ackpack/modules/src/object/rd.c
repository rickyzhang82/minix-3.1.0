/* $Id: rd.c,v 1.3 2005/09/01 12:13:26 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#include "obj.h"
#include "system.h"

/*
 * Parts of the output file.
 */
#undef PARTEMIT
#undef PARTRELO
#undef PARTNAME
#undef PARTCHAR
#undef PARTDBUG
#undef NPARTS

#define	PARTEMIT	0
#define	PARTRELO	1
#define	PARTNAME	2
#define	PARTCHAR	3
#ifdef SYMDBUG
#define PARTDBUG	4
#else
#define PARTDBUG	3
#endif
#define	NPARTS		(PARTDBUG + 1)

static long		offset[MAXSECT];

static FILE		*outfile;
static long		outseek[NPARTS];
static long		currpos;
static long		rd_base;
#define OUTSECT(i) \
	(outseek[PARTEMIT] = offset[i])
#define BEGINSEEK(p, o) \
	(outseek[(p)] = (o))

static int sectionnr;

static
void
OUTREAD(int p,char *b,long n)
{
	register long l = outseek[p];

	if (currpos != l) {
		fseek( outfile, l, SEEK_SET );
	}
	rd_bytes(outfile, b, n);
	l += n;
	currpos = l;
	outseek[p] = l;
}

/*
 * Open the output file according to the chosen strategy.
 */
int
rd_open(char *f)
{
	outfile = fopen( f, "rb" );
	if( 0 == outfile )
		return 0;
	return rd_Fileopen(outfile);
}

static int offcnt;

int
rd_Fileopen(FILE *fp)
{
	register int i;

	for (i = 0; i < NPARTS; i++) outseek[i] = 0;
	offcnt = 0;
	if( 0 == sys_seek( fp, 0L, 1, &rd_base ) )
		return 0;
	currpos = rd_base;
	outseek[PARTEMIT] = currpos;
	outfile = fp;
	sectionnr = 0;
	return 1;
}

void
rd_close(void)
{
	fclose(outfile);
	outfile = 0;
}

FILE *
rd_File(void)
{
	return outfile;
}

void
rd_ohead(struct outhead *head)
{
	register long off;

	OUTREAD(PARTEMIT, (char *) head, (long) SZ_HEAD);
#if ACK_BYTE_ORDER == 0x0123
	if (sizeof(struct outhead) != SZ_HEAD)
#endif
	{
		register char *c = (char *) head + (SZ_HEAD-4);
		
		head->oh_nchar = get4(c);
		c -= 4; head->oh_nemit = get4(c);
		c -= 2; head->oh_nname = uget2(c);
		c -= 2; head->oh_nrelo = uget2(c);
		c -= 2; head->oh_nsect = uget2(c);
		c -= 2; head->oh_flags = uget2(c);
		c -= 2; head->oh_stamp = uget2(c);
		c -= 2; head->oh_magic = uget2(c);
	}
	off = OFF_RELO(*head) + rd_base;
	BEGINSEEK(PARTRELO, off);
	off += (long) head->oh_nrelo * SZ_RELO;
	BEGINSEEK(PARTNAME, off);
	off += (long) head->oh_nname * SZ_NAME;
	BEGINSEEK(PARTCHAR, off);
#ifdef SYMDBUG
	off += head->oh_nchar;
	BEGINSEEK(PARTDBUG, off);
#endif
}

void
rd_rew_relo(struct outhead *head)
{
	register long off = OFF_RELO(*head) + rd_base;

	BEGINSEEK(PARTRELO, off);
}

void
rd_sect(struct outsect *sect,unsigned int cnt)
{
	register char *c = (char *) sect + cnt * SZ_SECT;

	OUTREAD(PARTEMIT, (char *) sect, (long)cnt * SZ_SECT);
	sect += cnt;
	offcnt += cnt;
	while (cnt--) {
		sect--;
#if ACK_BYTE_ORDER == 0x0123
		if (sizeof(struct outsect) != SZ_SECT)
#endif
		{
			c -= 4; sect->os_lign = get4(c);
			c -= 4; sect->os_flen = get4(c);
			c -= 4; sect->os_foff = get4(c);
			c -= 4; sect->os_size = get4(c);
			c -= 4; sect->os_base = get4(c);
		}
		offset[--offcnt] = sect->os_foff + rd_base;
	}
}

void
rd_outsect(int s)
{
	OUTSECT(s);
	sectionnr = s;
}

/*
 * We don't have to worry about byte order here.
 */
void
rd_emit(char *emit,long cnt)
{
	OUTREAD(PARTEMIT, emit, cnt);
	offset[sectionnr] += cnt;
}

void
rd_relo(struct outrelo *relo,unsigned int cnt)
{

	OUTREAD(PARTRELO, (char *) relo, (long) cnt * SZ_RELO);
#if ACK_BYTE_ORDER == 0x0123
	if (sizeof(struct outrelo) != SZ_RELO)
#endif
	{
		register char *c = (char *) relo + (long) cnt * SZ_RELO;

		relo += cnt;
		while (cnt--) {
			relo--;
			c -= 4; relo->or_addr = get4(c);
			c -= 2; relo->or_nami = uget2(c);
			relo->or_sect = *--c;
			relo->or_type = *--c;
		}
	}
}

void
rd_name(struct outname *name,unsigned int cnt)
{

	OUTREAD(PARTNAME, (char *) name, (long) cnt * SZ_NAME);
#if ACK_BYTE_ORDER == 0x0123
	if (sizeof(struct outname) != SZ_NAME)
#endif
	{
		register char *c = (char *) name + (long) cnt * SZ_NAME;

		name += cnt;
		while (cnt--) {
			name--;
			c -= 4; name->on_valu = get4(c);
			c -= 2; name->on_desc = uget2(c);
			c -= 2; name->on_type = uget2(c);
			c -= 4; name->on_foff = get4(c);
		}
	}
}

void
rd_string(char *addr,long len)
{
	
	OUTREAD(PARTCHAR, addr, len);
}

#ifdef SYMDBUG
void
rd_dbug(char *buf,long size)
{
	OUTREAD(PARTDBUG, buf, size);
}
#endif
