/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#ifndef lint
static char rcsid[] = "$Id: memory.c,v 1.3 2005/09/01 12:13:33 beng Exp $";
#endif

#include <stdio.h>
#include <arch.h>
#include <out.h>
#include <ranlib.h>
#include <object.h>
#include <system.h>
#include "const.h"
#include "assert.h"
#include "debug.h"
#include "memory.h"
#include "prototypes.h"

extern int	passnumber;
extern unsigned short	NLocals, NGlobals;
extern long		NLChars, NGChars;
extern int		flagword;
extern struct outhead	outhead;
extern struct outsect	outsect[];

#ifndef NOSTATISTICS
extern int statistics;
#endif

static size_t malloc_size;		/* Total block size */
char * malloc_base;
struct memory	mems[NMEMS];

bool	incore = TRUE;	/* TRUE while everything can be kept in core. */
ind_t	core_position = (ind_t)0;	/* Index of current module. */

#ifdef _DEBUG
char *
address(int piece,ind_t offset)
{
	return malloc_base+mems[piece].mem_offset+offset;
}

char * modulptr(ind_t offset)
{
	return malloc_base+mems[ALLOMODL].mem_offset+core_position+offset;
}
#endif

#define K 1024L
#define INCRSIZE 8192

static ind_t refused;

/*
 * Initialize some pieces of core. We hope that this will be our last
 * real allocation, meaning we've made the right choices.
 */
void
init_core(void)
{
	register ind_t		total_size;
	register struct memory	*mem;

#ifdef _MINIX
	/* 132k req'd */
	mems[ALLOEMIT + 0].mem_left = 32 * K;
	mems[ALLOEMIT + 1].mem_left = 4 * K;
	mems[ALLOEMIT + 2].mem_left = 8 * K;
	mems[ALLORELO].mem_left = 12 * K;
	mems[ALLOLOCL].mem_left = 8 * K;
	mems[ALLOGLOB].mem_left = 8 * K;
	mems[ALLOLCHR].mem_left = 8 * K;	/* Must be non-zero */
	mems[ALLOGCHR].mem_left = 8 * K;	/* Must be non-zero */
#ifdef SYMDBUG
	mems[ALLODBUG].mem_left = 16 * K;
#endif /* SYMDBUG */
	mems[ALLOSYMB].mem_left = 4 * K;
	mems[ALLOARCH].mem_left = 4 * K;
	mems[ALLOMODL].mem_left = 16 * K;
	mems[ALLORANL].mem_left = 4 * K;
#else
	/* Assume a 'big' machine: 288k req'd */
	mems[ALLOEMIT + 0].mem_left = 64 * K;
	mems[ALLOEMIT + 1].mem_left = 4 * K;
	mems[ALLOEMIT + 2].mem_left = 16 * K;
	mems[ALLORELO].mem_left = 24 * K;
	mems[ALLOLOCL].mem_left = 16 * K;
	mems[ALLOGLOB].mem_left = 16 * K;
	mems[ALLOLCHR].mem_left = 16 * K;	/* Must be non-zero */
	mems[ALLOGCHR].mem_left = 16 * K;	/* Must be non-zero */
#ifdef SYMDBUG
	mems[ALLODBUG].mem_left = 32 * K;
#endif /* SYMDBUG */
	mems[ALLOSYMB].mem_left = 8 * K;
	mems[ALLOARCH].mem_left = 4 * K;
	mems[ALLOMODL].mem_left = 64 * K;
	mems[ALLORANL].mem_left = 8 * K;
#endif

	total_size = (ind_t)0;	/* Will accumulate the sizes. */

	/* String areas are special-cased. The first byte is unused as a way to
	 * distinguish a name without string from a name which has the first
	 * string in the string area.
	 */
	for (mem = mems; mem < &mems[NMEMS]; mem++) {
		mem->mem_offset = total_size;
		mem->mem_full = (ind_t)0;
		total_size += mem->mem_left;
		if (mem == &mems[ALLOLCHR] || mem == &mems[ALLOGCHR]) {
			mem->mem_left--;
			mem->mem_full++;
		}
	}

	malloc_base = (char *)malloc( total_size );
	if( 0 == malloc_base )
	{
		incore = FALSE;	/* In core strategy failed. */

		/* Need tiny bit of space for strings */

#define ALIGN 8			/* minimum alignment for pieces */
#define AT_LEAST	(ind_t)2*ALIGN	/* See comment about string areas. */

		malloc_base = (char *)malloc( AT_LEAST );
		if (0 == malloc_base)
			fatal("no core at all");
		total_size = 0;
		for (mem = mems; mem < &mems[NMEMS]; mem++) {
			mem->mem_offset = total_size;
			if (mem == &mems[ALLOLCHR] || mem == &mems[ALLOGCHR]) {
				total_size += ALIGN;
				mem->mem_left = ALIGN - 1;
				mem->mem_full = 1;
			}
			else {
				mem->mem_full = (ind_t)0;
				mem->mem_left = 0;
			}
		}
	}
	malloc_size = total_size;
}

/* The bytes of `mem' must be moved `dist' up in the address space.
 * We copy the bytes from high to low, because the tail of the new area may
 * overlap with the old area, but we do not want to overwrite them before they
 * are copied.
 */
static
void
copy_up(struct memory *mem,ind_t dist)
{
	memmove( malloc_base + mem->mem_offset + dist, malloc_base + mem->mem_offset, mem->mem_full );
	mem->mem_offset += dist;
}

/* The bytes of `mem' must be moved `dist' down in the address space.
 * We copy the bytes from low to high, because the tail of the new area may
 * overlap with the old area, but we do not want to overwrite them before they
 * are copied.
 */
static
void
copy_down(struct memory *mem,ind_t dist)
{
	memmove( malloc_base + mem->mem_offset - dist, malloc_base + mem->mem_offset, mem->mem_full );
	mem->mem_offset -= dist;
}

/* Allocate an extra block of `incr' bytes and move all pieces with index
 * higher than `piece' up with the size of the block.
 * Move up as much as possible, if "incr" fails.
 */
static
ind_t
move_up(int piece,ind_t incr)
{
	register struct memory	*mem;
	char * rebase;

	debug("move_up(%d, %d)\n", piece, (int)incr, 0, 0);

	/* Try to claim more memory */
	rebase = realloc( malloc_base, malloc_size + incr );
	while( INCRSIZE < incr && 0 == rebase )
	{
		incr -= INCRSIZE;
		rebase = realloc( malloc_base, malloc_size + incr );
	}

	if (0 == rebase)
		return (ind_t) 0;

	malloc_base = rebase;
	malloc_size += incr;
#ifndef NOSTATISTICS
	if (statistics) fprintf(stderr,"moving up %lx\n", (long) incr);
#endif
	for (mem = &mems[NMEMS - 1]; mem > &mems[piece]; mem--)
		copy_up(mem, incr);

	mems[piece].mem_left += incr;
	return incr;
}

/* compact() flags */
#define NORMAL 0
#define FREEZE 1
#define FORCED 2

/*
 * This routine is called if `piece' needs `incr' bytes and the system won't
 * give them. We first steal the free bytes of all lower pieces and move them
 * and `piece' down. If that doesn't give us enough bytes, we steal the free
 * bytes of all higher pieces and move them up. We return whether we have
 * enough bytes, the first or the second time.
 */
static
bool
compact(int piece,ind_t incr,int flag)
{
	register ind_t		gain, size;
	register struct memory	*mem;
	int min = piece, max = piece;
#define SHIFT_COUNT 2		/* let pieces only contribute if their free
				   memory is more than 1/2**SHIFT_COUNT * 100 %
				   of its occupied memory
				*/

	debug("compact(%d, %d, %d)\n", piece, (int)incr, flag, 0);
	for (mem = &mems[0]; mem < &mems[NMEMS - 1]; mem++) {
		assert(mem->mem_offset + mem->mem_full + mem->mem_left == (mem+1)->mem_offset);
	}

	mem = &mems[piece];
	if (flag == NORMAL) {
		/* try and gain a bit more than needed */
		gain = (mem->mem_full + incr) >> SHIFT_COUNT;
		if (incr < gain) incr = gain;
	}
	
	/*
	 * First, check that moving will result in enough space
	 */
	if (flag != FREEZE) {
		gain = mem->mem_left;
		for (mem = &mems[piece-1]; mem >= &mems[0]; mem--) {
			/* 
			 * Don't give it all away! 
			 * If this does not give us enough, bad luck
			 */
			if (flag == FORCED)
				size = 0;
			else {
				size = mem->mem_full >> SHIFT_COUNT;
				if (size == 0) size = mem->mem_left >> 1;
			}
			if (mem->mem_left >= size)
				gain += (mem->mem_left - size) & ~(ALIGN - 1);
			if (gain >= incr) {
				min = mem - &mems[0];
				break;
			}
		}
		if (min == piece)
		    for (mem = &mems[piece+1]; mem <= &mems[NMEMS - 1]; mem++) {
			/* 
			 * Don't give it all away! 
			 * If this does not give us enough, bad luck
			 */
			if (flag == FORCED)
				size = 0;
			else {
				size = mem->mem_full >> SHIFT_COUNT;
				if (size == 0) size = mem->mem_left >> 1;
			}
			if (mem->mem_left >= size)
				gain += (mem->mem_left - size) & ~(ALIGN - 1);
			if (gain >= incr) {
				max = mem - &mems[0];
				break;
			}
		}
		if (min == piece) {
			min = 0;
			if (max == piece) max = 0;
		}
		if (gain < incr) return 0;
	}
	else {
		min = 0;
		max = NMEMS - 1;
	}

	gain = 0;
	for (mem = &mems[min]; mem != &mems[piece]; mem++) {
		/* Here memory is inserted before a piece. */
		assert(passnumber == FIRST || gain == (ind_t)0);
		if (gain) copy_down(mem, gain);
		if (flag == FREEZE || gain < incr) {
			if (flag != NORMAL) size = 0;
			else {
				size = mem->mem_full >> SHIFT_COUNT;
				if (size == 0) size = mem->mem_left >> 1;
			}
			if (mem->mem_left >= size) {
				size = (mem->mem_left - size) & ~(ALIGN - 1);
				gain += size;
				mem->mem_left -= size;
			}
		}
	}
	/*
	 * Now mems[piece]:
	 */
	if (gain) copy_down(mem, gain);
	gain += mem->mem_left;
	mem->mem_left = 0;

	if (gain < incr) {
		register ind_t	up = (ind_t)0;

		for (mem = &mems[max]; mem > &mems[piece]; mem--) {
			/* Here memory is appended after a piece. */
			if (flag == FREEZE || gain + up < incr) {
				if (flag != NORMAL) size = 0;
				else {
					size = mem->mem_full >> SHIFT_COUNT;
					if (size == 0) size = mem->mem_left >> 1;
				}
				if (mem->mem_left >= size) {
					size = (mem->mem_left - size) & ~(ALIGN - 1);
					up += size;
					mem->mem_left -= size;
				}
			}
			if (up) copy_up(mem, up);
		}
		gain += up;
	}
	mems[piece].mem_left += gain;
	assert(flag == FREEZE || gain >= incr);
	for (mem = &mems[0]; mem < &mems[NMEMS - 1]; mem++) {
		assert(mem->mem_offset + mem->mem_full + mem->mem_left == (mem+1)->mem_offset);
	}
	return gain >= incr;
}

static int alloctype = NORMAL;

/* Add `size' bytes to the bytes already allocated for `piece'. If it has no
 * free bytes left, ask them from memory or, if that fails, from the free
 * bytes of other pieces. The offset of the new area is returned. No matter
 * how many times the area is moved, because of another allocate, this offset
 * remains valid.
 */
ind_t
alloc(int piece,long size)
{
	register ind_t		incr = 0;
	ind_t			left = mems[piece].mem_left;
	register ind_t		full = mems[piece].mem_full;

	assert(passnumber == FIRST || (!incore && piece == ALLOMODL));
	if (size == (long)0)
		return full;
	if (size != (ind_t)size)
		return BADOFF;
	switch(piece) {
	case ALLOMODL:
	case ALLORANL:
		size = int_align(size);
	}

	if (size - left > 0)
		incr = ((size - left + (INCRSIZE - 1)) / INCRSIZE) * INCRSIZE;

	/* Space available? */
	if( 0 == incr )
		goto success;

	/* If asking for less than currently allocated, attempt to
	 * double the current allocation. */
	if( incr < left + full )
	{
		incr -= move_up( piece, left + full );
		if( incr <=0 )
			goto success;
	}

	/* Ask for precisely the right memory */
	if( move_up( piece, incr ) == incr )
		goto success;

	/* Last resort; compact existing memory */
	if( ! compact( piece, size, alloctype ) )
	{
		incore = FALSE;
		return BADOFF;
	}

success:
	mems[piece].mem_full += size;
	mems[piece].mem_left -= size;
	return full;
}

/* The piece of memory with index `piece' is no longer needed.
 * We take care that it can be used by compact() later, if needed.
 */
void
dealloc(int piece)
{
	/*
	 * Some pieces need their memory throughout the program.
	 */
	assert(piece != ALLOGLOB);
	assert(piece != ALLOGCHR);
	assert(piece != ALLOSYMB);
	assert(piece != ALLOARCH);
	mems[piece].mem_left += mems[piece].mem_full;
	mems[piece].mem_full = (ind_t)0;
}

/* We don't need the previous modules, so we put the current module
 * at the start of the piece allocated for module contents, thereby
 * overwriting the saved modules, and release its space.
 */
static
void
free_saved_moduls(void)
{
	register ind_t		size;
	register char		*old, *new;
	register struct memory	*mem = &mems[ALLOMODL];

	size = mem->mem_full - core_position;
	new = malloc_base + mem->mem_offset;
	old = new + core_position;
	while (size--)
		*new++ = *old++;
	mem->mem_full -= core_position;
	mem->mem_left += core_position;
	core_position = (ind_t)0;
}

/* Same as alloc() but for a piece which really needs it. If the first
 * attempt fails, release the space occupied by other pieces and try again.
 */
ind_t
hard_alloc(int piece,long size)
{
	register ind_t	ret;
	register int	i;

	if (size != (ind_t)size)
		return BADOFF;
	if ((ret = alloc(piece, size)) != BADOFF) {
		return ret;
	}

	/*
	 * Deallocate what we don't need.
	 */
	for (i = 0; i < NMEMS; i++) {
		switch (i) {
		case ALLOGLOB:
		case ALLOGCHR:
		case ALLOSYMB:
		case ALLOARCH:
		case ALLOMODL:
		case ALLORANL:
			break;	/* Do not try to deallocate this. */
		default:
			dealloc(i);
			break;
		}
	}
	free_saved_moduls();

	if ((ret = alloc(piece, size)) != BADOFF) {
		return ret;
	}

	alloctype = FORCED;
	ret = alloc(piece, size);
	alloctype = NORMAL;
	return ret;
}

char *
core_alloc(int piece,long size)
{
	register ind_t	off;

	if ((off = alloc(piece, size)) == BADOFF)
		return (char *)0;
	return address(piece, off);
}

void
core_free(int piece,char * p)
{
	char	*q = address(piece, mems[piece].mem_full);

	assert(p < q);
	switch(sizeof(unsigned) == sizeof(char *)) {
	case 1:
		mems[piece].mem_full -= (unsigned) (q - p);
		mems[piece].mem_left += (unsigned) (q - p);
		break;
	default:
		mems[piece].mem_full -= (ind_t) q - (ind_t) p;
		mems[piece].mem_left += (ind_t) q - (ind_t) p;
		break;
	}
}

/*
 * Reset index into piece of memory for modules and
 * take care that the allocated pieces will not be moved.
 */
void
freeze_core(void)
{
	register int	i;

	core_position = (ind_t)0;

	if (incore)
		return;

	for (i = 0; i < NMEMS; i++) {
		switch (i) {
		case ALLOGLOB:
		case ALLOGCHR:
		case ALLOSYMB:
		case ALLOARCH:
			break;	/* Do not try to deallocate this. */
		default:
			dealloc(i);
			break;
		}
	}
	compact(NMEMS - 1, (ind_t)0, FREEZE);
}

/* ------------------------------------------------------------------------- */

/*
 * To transform the various pieces of the output in core to the file format,
 * we must order the bytes in the unsigned shorts and longs as ACK prescribes.
 */
void
write_bytes(void)
{
	unsigned short		nsect;
	long			offchar;
	register struct memory	*mem;
	int			sectionno = 0;

	nsect = outhead.oh_nsect;
	offchar = OFF_CHAR(outhead);

	/*
	 * We allocated two areas: one for local and one for global names.
	 * Also, we used another kind of on_foff than on file.
	 * At the end of the global area we have put the section names.
	 */
	if (!(flagword & SFLAG)) {
		do_crs((struct outname *)(malloc_base + mems[ALLOLOCL].mem_offset), NLocals);
		namecpy((struct outname *)(malloc_base + mems[ALLOLOCL].mem_offset),
			NLocals,
			offchar
		);
		namecpy((struct outname *)(malloc_base + mems[ALLOGLOB].mem_offset),
			NGlobals + nsect,
			offchar + NLChars
		);
	}
	/*
	 * These pieces must always be written.
	 */
	wr_ohead(&outhead);
	wr_sect(outsect, nsect);
	for (mem = &mems[ALLOEMIT]; mem < &mems[ALLORELO]; mem++)
		wrt_emit(malloc_base + mem->mem_offset, sectionno++, mem->mem_full);
	/*
	 * The rest depends on the flags.
	 */
	if (flagword & (RFLAG|CFLAG))
		wr_relo((struct outrelo *) (malloc_base + mems[ALLORELO].mem_offset),
			outhead.oh_nrelo);
	if (!(flagword & SFLAG)) {
		wr_name((struct outname *) (malloc_base + mems[ALLOLOCL].mem_offset),
			NLocals);
		wr_name((struct outname *) (malloc_base + mems[ALLOGLOB].mem_offset),
			NGlobals+nsect);
		wr_string(malloc_base + mems[ALLOLCHR].mem_offset + 1, (long)NLChars);
		wr_string(malloc_base + mems[ALLOGCHR].mem_offset + 1, (long)NGChars);
#ifdef SYMDBUG
		wr_dbug(malloc_base + mems[ALLODBUG].mem_offset, mems[ALLODBUG].mem_full);
#endif /* SYMDBUG */
	}
}

void
namecpy(struct outname *name,unsigned int nname,long offchar)
{
	while (nname--) {
		if (name->on_foff)
			name->on_foff += offchar - 1;
		name++;
	}
}
