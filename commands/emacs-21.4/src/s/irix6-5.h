#define IRIX6
#define IRIX6_5
#include "irix5-0.h"

#if _MIPS_SZLONG == 64		/* -mabi=64 (gcc) or -64 (MIPSpro) */
#define _LP64			/* lisp.h takes care of the rest */
#endif /* _MIPS_SZLONG */

/* This macro definition, which we inherited from irix5-0.h,
   is needed in configure on Irix 5, but gets in the way there
   on Irix 6.  So get rid of it except in Makefile.in where we need it.  */
#ifndef THIS_IS_MAKEFILE
#undef C_SWITCH_SYSTEM
#endif

/* The only supported configuration of GCC under IRIX6.x produces
   n32 MIPS ABI binaries and also supports -g. */
#ifdef __GNUC__
#undef C_DEBUG_SWITCH
#define C_DEBUG_SWITCH -g
#else
/* Optimize, inaccurate debugging, increase limit on size of what's
   optimized.

   This should also be applicable other than on Irix 6.5, but I don't
   know for which compiler versions.  -- fx */
#define C_DEBUG_SWITCH -g3 -O -OPT:Olimit=3500
#endif

#undef SA_RESTART

/* Cancel the #define that is in irix5-0.h.  */
#undef ospeed

/* If we keep the #defines from usg5-4.h, we lose when using the X
   headers because (at least) the bzero definition breaks their use of
   strings.h.  Including strings.h here gets us prototypes for them.
   (They're in libc though also they seem to be intrinsics in the SGI
   (Cray) compiler at least at version 7.3).  -- fx  */
#undef bcopy
#undef bcmp
#undef bzero
#ifndef NOT_C_CODE
#include <strings.h>
#endif

#undef TIOCSIGSEND		/* defined in usg5-4.h */
