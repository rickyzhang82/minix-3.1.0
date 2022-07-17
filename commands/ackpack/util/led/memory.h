/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* $Id: memory.h,v 1.3 2005/09/01 12:13:33 beng Exp $ */

/* Paged memory architecture.
 *
 * The ACK system was originally written for small machines, with limited
 * memory. This required carefully memory management; and memory gets
 * divided into NMEMS pieces. There is a struct for each piece recording
 * where it is located in memory, how many bytes are used, and how many
 * are left. If a request for core doesn't fit in the bytes left, an
 * attempt is made to allocate more memory for the process, and pieces
 * after the one that requested the growth are moved up. There is an
 * important assumption:
 *      - all blocks are contiguous in memory.
 *
 * Traditionally, sbrk() was used for requesting memory when possible
 * [Historical note: Unfortunately, we cannot use sbrk to request more
 * memory, because its result cannot be trusted. More specifically, it
 * does not work properly on 2.9 BSD, and probably does not work properly
 * on 2.8 BSD and V7 either. The problem is that "sbrk" adds the increment
 * to the current "break" WITHOUT testing the carry bit. So, if your break
 * is at 40000, and you "sbrk(30000)", it will succeed, but your break will
 * be at 4464 (70000 - 65536).]
 *
 * In this modern reimplementation, malloc() and realloc() are used to
 * claim core memory. It is not possible to know precisely where memory
 * 'begins' in the dynamic malloc() environment, and hence, all references
 * into the contiguous block are offsets against the base of the malloc'd
 * block.
 */

#define ALLOEMIT	0			/* Section contents. */
#define ALLORELO	(ALLOEMIT + MAXSECT)	/* Relocation table. */
#define ALLOLOCL	(ALLORELO + 1)		/* Saved local names. */
#define ALLOGLOB	(ALLOLOCL + 1)		/* Saved global names. */
#define ALLOLCHR	(ALLOGLOB + 1)		/* Strings of local names. */
#define ALLOGCHR	(ALLOLCHR + 1)		/* Strings of global names. */
#ifdef SYMDEBUG
#define ALLODBUG	(ALLOGCHR + 1)		/* Symbolic debugging info. */
#else /* SYMDEBUG */
#define ALLODBUG	ALLOGCHR
#endif /* SYMDEBUG */
#define ALLOSYMB	(ALLODBUG + 1)		/* Symbol table. */
#define ALLOARCH	(ALLOSYMB + 1)		/* Archive positions. */
#define ALLOMODL	(ALLOARCH + 1)		/* Modules. */
#define ALLORANL	(ALLOMODL + 1)		/* Ranlib information. */
#define NMEMS		(ALLORANL + 1)

#define BADOFF		((ind_t)-1)

typedef long		ind_t;

extern ind_t core_position;
extern char * malloc_base;

struct memory {
	ind_t	mem_offset;		/* Offset from malloc_base */
	ind_t	mem_full;       /* Amount used */
	ind_t	mem_left;
};
extern struct memory	mems[];

#ifndef _DEBUG
# define address(piece,offset)	(malloc_base+mems[(piece)].mem_offset+(offset))
# define modulptr(offset)	(malloc_base+mems[ALLOMODL].mem_offset+core_position+(offset))
#else
char * address(int,ind_t);
char * modulptr(ind_t);
#endif

#define int_align(sz)		(((sz)+(sizeof(int)-1))&~(int)(sizeof(int)-1))

void init_core(void);
ind_t alloc(int,long);
void dealloc(int);
ind_t hard_alloc(int,long);
char * core_alloc(int,long);
void core_free(int,char *);
void freeze_core(void);
void write_bytes(void);

