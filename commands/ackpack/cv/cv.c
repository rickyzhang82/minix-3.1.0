/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 *
 */

/*
 * This program converts ack.out format to PC/IX & Minix a.out format.
 * It uses ~em/modules/lib/libobject.a.
 *
 * Minix 2.0.x has the command line:
 *    cv [-S <size>] [-x] [-m$(ARCH)] [-g <sym>] <ack> <a.out>
 */

#include <stdio.h>
#include <stdarg.h>

#ifdef _WIN32
#include <fcntl.h>		/* _O_BINARY */
#include <io.h>
#else
#include <unistd.h>
#endif

struct exec {
	unsigned char   a_magic[2];
	unsigned char   a_flags;
	unsigned char   a_cpu;
	unsigned char   a_hdrlen;
	unsigned char   a_unused;
	unsigned short  a_version;
	long            a_text;
	long            a_data;
	long            a_bss;
	long            a_entry;
	long            a_total;	/* total memory allocated */
	long            a_syms;

	/* SHORT FORM ENDS HERE */
	long		a_trsize;	/* text relocation size */
	long		a_drsize;	/* data relocation size */
	long		a_tbase;	/* text relocation base */
	long		a_dbase;	/* data relocation base */
};

struct  nlist
{
    char            n_name[8];
	long            n_value; 
	unsigned char   n_sclass;
	unsigned char   n_numaux;
	unsigned short  n_type;
};

#include <system.h>
#include <object.h>
#include <out.h>

#ifndef NORCSID
static char rcs_id[] = "$Id: cv.c,v 1.3 2005/09/01 12:13:16 beng Exp $" ;
#endif

#define ENTRY 0x0	/* entry point */

/*
 * Header and section table of new format object file.
 */
struct outhead	outhead;
struct outsect	outsect[S_MAX];
struct outhead	symhead;

struct exec exec;

char	*output_file;
int	outputfile_created;
FILE	*output;

char	*symbol_file;

char *program;
char *chars;

char flag;

long stack;

/* Output file definitions and such */

#define TEXTSG	0
#define ROMSG	1
#define DATASG	2
#define BSSSG	3
#define LSECT	BSSSG+1
#define NSECT	LSECT+1

/* VARARGS1 */
void
fatal(const char * s,...)
{
	va_list args;

	fprintf(stderr,"%s: ",program) ;
	va_start( args, s );
	vfprintf(stderr, s, args);
	va_end( args );
	if (outputfile_created) {
		fclose(output);
		unlink(output_file);
	}
	exit(1);
}

void
rd_fatal(void)
{
	fatal("read error\n");
}

void
wr_fatal(void)
{
	fatal("write error\n");
}

long align(long a,long b)
{
        a += b - 1;
        return a - a % b;
}

int
follows(struct outsect * pa, struct outsect * pb)
{
        /* return 1 if pa follows pb */

        return pa->os_base == align(pb->os_base+pb->os_size, pa->os_lign);
}

void
my_wr_int2(int n)
{
	char buf[2];

	buf[0] = n;
	buf[1] = (n >> 8);
	fwrite(buf, 1, 2, output);
}

void
my_wr_long(long l)
{
	char buf[4];

	buf[0] = l;
	buf[1] = (l >> 8);
	buf[2] = (l >> 16);
	buf[3] = (l >> 24);
	fwrite(buf, 1, 4, output);
}

/*
 * Transfer the emitted bytes from one file to another.
 */
void
emits(struct outsect * section)
{
	register long	n ;
	register int	blk;
	char		buffer[BUFSIZ];

	n= section->os_flen ;
	rd_outsect(section - outsect);
	while (n > 0) {
		blk = n > BUFSIZ ? BUFSIZ : n;
		rd_emit(buffer, (long) blk);
		fwrite(buffer, 1, blk, output);
		n -= blk;
	}
	if ((n = section->os_size - section->os_flen) > 0) {
		for (blk = BUFSIZ - 1; blk >= 0; blk--) {
			buffer[blk] = 0;
		}
		while (n > 0) {
			blk = n > BUFSIZ ? BUFSIZ : n;
			fwrite(buffer, 1, blk, output);
			n -= blk;
		}
	}
}

void
emit_symtab(void)
{
	struct outname ACK_name;  /* symbol table entry in ACK format */
	struct nlist IX_name;	  /* symbol table entry in PC/IX format */
	register unsigned short i;

	long l;
	long off = OFF_CHAR(outhead);
	long adjust = OFF_CHAR(symhead) - OFF_CHAR(outhead);
	int j;
	char *p;

	rd_string(chars,outhead.oh_nchar);
	for (i = 0; i < outhead.oh_nname; i++) {
		rd_name(&ACK_name, 1);
		if( symbol_file )
		{
			l = ACK_name.on_foff;
		 	if( 0 != ACK_name.on_foff )
				ACK_name.on_foff += adjust;
			wr_name(&ACK_name, 1);
			ACK_name.on_foff = l;
		}

		/* Ignore debugger symbols in executable output, and
		 * and line/module symbols. */
		if( S_STB == ( ACK_name.on_type & S_ETC )
			|| S_LIN == ( ACK_name.on_type & S_ETC )
			|| S_FIL == ( ACK_name.on_type & S_ETC )
			|| S_MOD == ( ACK_name.on_type & S_ETC ) )
				continue;

		/* Symbol format gets changed; and strings truncated
		 * to 8 chars */
		switch(ACK_name.on_type & S_TYP) {
			case S_UND:
				IX_name.n_sclass = 0;
				break;
			case S_ABS:
				IX_name.n_sclass = 01;
				break;
			case S_MIN + TEXTSG:
				IX_name.n_sclass = 02; 
				break;
			case S_MIN + ROMSG:
			case S_MIN + DATASG:
				IX_name.n_sclass = 03;
				break;
			case S_MIN + BSSSG:
			case S_MIN + LSECT:
				IX_name.n_sclass = 04;
				break;
			default:
				fprintf(stderr,"warning: unknown s_type: %d\n",
					ACK_name.on_type & S_TYP);
		}
		if (ACK_name.on_type & S_EXT) IX_name.n_sclass |= 020;
		IX_name.n_value = ACK_name.on_valu;
		if (ACK_name.on_foff == 0) {
			p = "\0\0";
		}
		else {
			l = ACK_name.on_foff - off;
			if (l < 0 || l >= outhead.oh_nchar) {
				fatal("bad on_off: %ld\n",l);
			}
			p = &chars[l];
		}
		for (j = 0; j < 8; j++) {
			IX_name.n_name[j] = *p++;
			if (*p == '\0') break;
		}
		for (j++; j < 8; j++) {
			IX_name.n_name[j] = 0;
		}
		fwrite((char *) &IX_name, 1, 8, output);
		my_wr_long(IX_name.n_value);
		fwrite(&(IX_name.n_sclass), 1, 2, output);
		my_wr_int2((int) IX_name.n_type);
	}
}

/* c.f. /usr/include/a.out.h */
static struct _mflag { const char * sys; unsigned char cpu; } mflag[] =
{
    { "i386", 0x10 }, { "i86", 0x04 },
    /* { "sparc", 0x17 }, { "m68k", 0x0b } */
    { 0, 0 }
};

#ifndef AOUT_CPU
#define AOUT_CPU 0x10
#endif

int
main(int argc,char * argv[])
{
	register struct exec *e = &exec;
	char * end;
	unsigned char cpu = AOUT_CPU;
	struct _mflag * m = mflag;

	output = stdout;
	program= argv[0] ;
	while ( argc>1 && argv[1][0]=='-' ) {
		flag=argv[1][1] ;
		argc-- ; argv++ ;
		switch( flag )
		{
		case 'g':	/* Next arg is filename */
			--argc;
			++argv;
			symbol_file = *argv;
			break;
		case 'S':	/* Next arg is value */
			stack = strtol( argv[ 1 ], &end, 0 );
			if( 0 == stack )
				stack = -1;
			else
			{
				while( *end && 0 < stack)
				{
					switch( *end )
					{
					case 'm':
					case 'M':	stack *= (1024 * 1024); break;
					case 'k':
					case 'K':	stack *= 1024; break;
					case 'w':
					case 'W':	stack *= _EM_WSIZE; break;
					case 'b':
					case 'B':	break;
					default:	stack = -1; break;
					}
					++end;
				}
			}
			if( stack <= 0 )
				fatal( "Cannot interpret '%s' as a stack size\n", argv[ 1 ] );
			--argc;
			++argv;
			break;
		case 'm':
			for( ; m->sys ; ++m )
				if( 0 == strcmp( m->sys, *argv+2 ) )
				{
					cpu = m->cpu;
					break;
				}
			if( 0 == m->sys )
				fatal( "Unknown machine '%s'\n", *argv+2 );
			break;
		case 'x':	/* Ignored for now */
			break;
		}
	}
	switch (argc) {
#ifdef USE_NATIVE
	case 1: rd_fdopen(0);
#else
	case 1:
# ifdef _WIN32
		setmode( 0, _O_BINARY );	/* stdin */
# endif
		rd_Fileopen(stdin);
#endif
		break;
	case 3:	if ((output = fopen(argv[2], "w")) == 0) {
			fatal("Can't write %s.\n", argv[2]);
		}
		output_file = argv[2];
		outputfile_created = 1;
		/* FALLTHROUGH */
	case 2:
		if (! rd_open(argv[1]))
			fatal("Can't read %s.\n", argv[1]);
		break;
	default:fatal("Usage: %s <as object> <dl object>.\n", argv[0]);
	}
	rd_ohead(&outhead);
	if (BADMAGIC(outhead))
		fatal("Not an ack object file.\n");
	if (outhead.oh_flags & HF_LINK)
		fatal("Contains unresolved references.\n");
	if (outhead.oh_nrelo > 0)
		fprintf(stderr, "Warning: relocation information present.\n");
	if ( outhead.oh_nsect!=LSECT && outhead.oh_nsect!=NSECT )
		fatal("Input file must have %d sections, not %ld\n",
			NSECT,outhead.oh_nsect) ;
	rd_sect(outsect, outhead.oh_nsect);
	/* A few checks */
	if ( outsect[TEXTSG].os_base != ENTRY)
		fatal("text must start at %d not at 0x%lx\n", ENTRY,
			outsect[TEXTSG].os_base) ;
	if ( outsect[BSSSG].os_flen != 0 )
		fatal("bss space contains initialized data\n") ;
	if (! follows(&outsect[BSSSG], &outsect[DATASG]))
		fatal("bss segment must follow data segment\n") ;
	if (! follows(&outsect[DATASG], &outsect[ROMSG]))
		fatal("data segment must follow rom\n") ;

	outsect[ROMSG].os_size = outsect[DATASG].os_base - outsect[ROMSG].os_base;
	outsect[DATASG].os_size = outsect[BSSSG].os_base - outsect[DATASG].os_base;

	e->a_magic[0] = 0x01;
	e->a_magic[1] = 0x03;

	e->a_cpu = cpu;
	e->a_hdrlen = 32;
	e->a_data = outsect[BSSSG].os_base - outsect[ROMSG].os_base;
	e->a_bss = outsect[BSSSG].os_size;
	e->a_entry = outsect[TEXTSG].os_base;
	e->a_syms = (long) outhead.oh_nname * sizeof (struct nlist);
	/* Default to 32kw stack */
	e->a_total = e->a_data + e->a_bss + ( stack ? stack : 0x8000 * _EM_WSIZE );
	if ( outsect[ROMSG].os_base == 0x0 ) {
		/* Separate I/D */
		e->a_flags = 0x20;
		outsect[TEXTSG].os_size = e->a_text =
			align(outsect[TEXTSG].os_size,16L);
	} else {
		e->a_flags = 0x10;
		outsect[TEXTSG].os_size = e->a_text =
			outsect[ROMSG].os_base - outsect[TEXTSG].os_base;
		if (! follows(&outsect[ROMSG], &outsect[TEXTSG]))
			fatal("rom segment must follow text\n") ;
	}
	if ( outhead.oh_nsect==NSECT ) {
		if (! follows(&outsect[LSECT], &outsect[BSSSG]))
			fatal("end segment must follow bss\n") ;
		if ( outsect[LSECT].os_size != 0 )
			fatal("end segment must be empty\n") ;
	}

	if (((unsigned) outhead.oh_nchar != outhead.oh_nchar) ||
	     (outhead.oh_nchar != 0 &&
	      (chars = malloc((unsigned)outhead.oh_nchar)) == 0)) {
		fprintf(stderr, "%s: (warning) No name list generated\n", program);
		e->a_syms = 0;
	}

	if(symbol_file && e->a_syms)
	{
		if(0==wr_open(symbol_file))
		{
			fprintf(stderr, "%s: (warning) Cannot write to '%s'\n",
					program, symbol_file);
			symbol_file = 0;
		}
	}
	else
		symbol_file = 0;

	/* Action at last */
	fwrite((char *) e, 1, 6, output);
	my_wr_int2((int) e->a_version);
	my_wr_long(e->a_text);
	my_wr_long(e->a_data);
	my_wr_long(e->a_bss);
	my_wr_long(e->a_entry);
	my_wr_long(e->a_total);
	my_wr_long(e->a_syms);
	emits(&outsect[TEXTSG]) ;
	emits(&outsect[ROMSG]) ;
	emits(&outsect[DATASG]) ;
	if (e->a_syms)
	{
		if(symbol_file)
		{
			/* Write ACK format header for symbol file */
			symhead.oh_magic = O_MAGIC;
			symhead.oh_stamp = outhead.oh_stamp;
			symhead.oh_flags = outhead.oh_flags;
			symhead.oh_nsect = 0;
			symhead.oh_nrelo = 0;
			symhead.oh_nname = outhead.oh_nname;
			symhead.oh_nemit = 0;
			symhead.oh_nchar = outhead.oh_nchar;

			wr_ohead( &symhead );
		}
		emit_symtab();
		if(symbol_file)
		{
			wr_string(chars,outhead.oh_nchar);
			wr_close( );
			chmod(symbol_file,0644);
		}
	}
	fclose(output);
	if ( outputfile_created ) chmod(argv[2],0755);

	return 0;
}

