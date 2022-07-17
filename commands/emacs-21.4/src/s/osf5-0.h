#define OSF5
#include "osf1.h"

/* It's enough to define _OSF_SOURCE instead of _BSD.  */

/* -nointrinsics is required to avoid losing with definitions of POSIX
   stuff in regex.c, for instance, where regex_t isn't consistent
   with the system defintion.  This may be necessary also on OSF 4
   systems with dtk 6.4 installed.  */
#undef C_SWITCH_SYSTEM
#ifdef __GNUC__
#define C_SWITCH_SYSTEM	-D_OSF_SOURCE
#else
#define C_SWITCH_SYSTEM	-D_OSF_SOURCE -nointrinsics
#endif

#define WAIT_USE_INT
#define SYS_SIGLIST_DECLARED
#define sys_siglist __sys_siglist
#ifndef NSIG			/* _OSF_SOURCE seems to get us this */
#define NSIG __sys_nsig
#endif

/* We have missing/inconsistent prototypes on 5.0, at least.  */
#define INHIBIT_X11R6_XIM

#define USE_MMAP_FOR_BUFFERS	1
