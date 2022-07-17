/* src/config.h.  Generated automatically by configure.  */
/* GNU Emacs site configuration template file.  -*- C -*-
   Copyright (C) 1988, 1993, 1994, 1999, 2000 Free Software Foundation, Inc.

This file is part of GNU Emacs.

GNU Emacs is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Emacs is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Emacs; see the file COPYING.  If not, write to the
Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */


/* No code in Emacs #includes config.h twice, but some of the code
   intended to work with other packages as well (like gmalloc.c) 
   think they can include it as many times as they like.  */
#ifndef EMACS_CONFIG_H
#define EMACS_CONFIG_H

#define MINIX

/* These are all defined in the top-level Makefile by configure.
   They're here only for reference.  */

/* Define GNU_MALLOC if you want to use the GNU memory allocator. */
/*#define GNU_MALLOC 1*/

/* Define if you are using the GNU C Library. */
/*#define DOUG_LEA_MALLOC 1*/

/* Define REL_ALLOC if you want to use the relocating allocator for
   buffer space. */
#define REL_ALLOC 1
  
/* Define HAVE_X_WINDOWS if you want to use the X window system.  */
/* #undef HAVE_X_WINDOWS */

/* Define HAVE_X11 if you want to use version 11 of X windows.
   Otherwise, Emacs expects to use version 10.  */
/* #undef HAVE_X11 */

/* Define if using an X toolkit.  */
/* #undef USE_X_TOOLKIT */

/* Define this if you're using XFree386.  */
/* #undef HAVE_XFREE386 */

/* Define this if you have Motif 2.1 or newer.  */
/* #undef HAVE_MOTIF_2_1 */

/* Define HAVE_MENUS if you have mouse menus.
   (This is automatic if you use X, but the option to specify it remains.)
   It is also defined with other window systems that support xmenu.c.  */
/* #undef HAVE_MENUS */

/* Define if we have the X11R6 or newer version of Xt.  */
/* #undef HAVE_X11XTR6 */

/* Define if we have the X11R6 or newer version of Xlib.  */
/* #undef HAVE_X11R6 */

/* Define if we have the X11R5 or newer version of Xlib.  */
/* #undef HAVE_X11R5 */

/* Define if we have the XPM libary.  */
/* #undef HAVE_XPM */

/* Define if we have the PNG library.  */
/* #undef HAVE_PNG */

/* Define if we have the JPEG library (version 6b or later).  */
/* #undef HAVE_JPEG */

/* Define if we have the TIFF library.  */
/* #undef HAVE_TIFF */

/* Define if we have the GIF library (version 4.1.0b1 or later).  */
/* #undef HAVE_GIF */

/* Define if libXaw3d is available.  */
/* #undef HAVE_XAW3D */

/* Define if we should use toolkit scroll bars.  */
/* #undef USE_TOOLKIT_SCROLL_BARS */

/* Define if we should use XIM, if it is available.  */
/* #define USE_XIM 1 */

/* Define if netdb.h declares h_errno.  */
#define HAVE_H_ERRNO 1

/* If we're using any sort of window system, define some consequences.  */
#ifdef HAVE_X_WINDOWS
#define HAVE_WINDOW_SYSTEM
#define MULTI_KBOARD
#define HAVE_MOUSE
#endif

/* Define USER_FULL_NAME to return a string
   that is the user's full name.
   It can assume that the variable `pw'
   points to the password file entry for this user.

   At some sites, the pw_gecos field contains
   the user's full name.  If neither this nor any other
   field contains the right thing, use pw_name,
   giving the user's login name, since that is better than nothing.  */
#define USER_FULL_NAME pw->pw_gecos

/* Define AMPERSAND_FULL_NAME if you use the convention
   that & in the full name stands for the login id.  */
/* Turned on June 1996 supposing nobody will mind it.  */
#define AMPERSAND_FULL_NAME

/* Things set by --with options in the configure script.  */

/* Define to support POP mail retrieval.  */
#define MAIL_USE_POP 1

/* Define to support Kerberos-authenticated POP mail retrieval.  */
/* #undef KERBEROS */
/* Define to use Kerberos 5 instead of Kerberos 4 */
/* #undef KERBEROS5 */
/* Define to support GSS-API in addition to (or instead of) Kerberos */
/* #undef GSSAPI */

/* Define to support using a Hesiod database to find the POP server.  */
/* #undef HESIOD */
/* #undef HAVE_LIBHESIOD */

/* Header for Voxware or PCM sound card driver.  */
/* #undef HAVE_MACHINE_SOUNDCARD_H */
/*#define HAVE_SYS_SOUNDCARD_H 1*/
/* #undef HAVE_SOUNDCARD_H */

/* Define HAVE_SOUND if we have sound support.  We know it works
   and compiles only on the specified platforms.   For others,
   it probably doesn't make sense to try.  */

#if defined __FreeBSD__ || defined __NetBSD__ || defined __linux__
#ifdef HAVE_MACHINE_SOUNDCARD_H
#define HAVE_SOUND 1
#endif
#ifdef HAVE_SYS_SOUNDCARD_H
#define HAVE_SOUND 1
#endif
#ifdef HAVE_SOUNDCARD_H
#define HAVE_SOUND 1
#endif
#endif /* __FreeBSD__ || __NetBSD__ || __linux__  */

/* Some things figured out by the configure script, grouped as they are in
   configure.in.  */
#ifndef _ALL_SOURCE  /* suppress warning if this is pre-defined */
/* #undef _ALL_SOURCE */
#endif

/*#define HAVE_SYS_FILE_H 1*/
#define HAVE_SYS_SELECT_H 1
#define HAVE_SYS_TIMEB_H 1
/*#undef HAVE_SYS_TIME_H*/
#define HAVE_UNISTD_H 1
#define HAVE_UTIME_H 1
#define HAVE_LINUX_VERSION_H 1
/* #undef HAVE_SYS_SYSTEMINFO_H */
#define HAVE_TERMIOS_H 1
#define NO_TERMIO 1
#define HAVE_LIMITS_H 1
#define HAVE_STRING_H 1
#define HAVE_STDLIB_H 1
/* #undef HAVE_TERMCAP_H */
/* #undef HAVE_TERM_H */
/*#define HAVE_STDIO_EXT_H 1*/
#define STDC_HEADERS 1
/*#define TIME_WITH_SYS_TIME 1*/
#undef HAVE_VFORK_H
#define HAVE_FCNTL_H 1
/*#define HAVE_SETITIMER 1*/
/*#define HAVE_UALARM 1*/
#define HAVE_SYS_WAIT_H 1
#define HAVE_STRINGS_H 1

/* #undef HAVE_LIBDNET */
/* #undef HAVE_LIBPTHREADS */
/* #undef HAVE_LIBRESOLV */
/* #undef HAVE_LIBXMU */
/* #undef HAVE_LIBNCURSES */
/* #undef HAVE_LIBINTL */
/* #undef HAVE_LIBXP */

/* movemail Kerberos support */
/* libraries */
/* #undef HAVE_LIBKRB */
/* #undef HAVE_LIBKRB4 */
/* #undef HAVE_LIBDES */
/* #undef HAVE_LIBDES425 */
/* #undef HAVE_LIBKRB5 */
/* #undef HAVE_LIBCRYPTO */
/* #undef HAVE_LIBK5CRYPTO */
/* #undef HAVE_LIBCOM_ERR */
/* header files */
/* #undef HAVE_KRB5_H */
/* #undef HAVE_DES_H */
/* #undef HAVE_KRB_H */
/* #undef HAVE_KERBEROSIV_DES_H */
/* #undef HAVE_KERBEROSIV_KRB_H */
/* #undef HAVE_KERBEROS_DES_H */
/* #undef HAVE_KERBEROS_KRB_H */
/* #undef HAVE_COM_ERR_H */

/* GSS-API libraries and headers */
/* #undef HAVE_LIBGSSAPI_KRB5 */
/* #undef HAVE_LIBGSSAPI */
/* #undef HAVE_GSSAPI_H */

/* Mail-file locking */
/* #undef HAVE_LIBMAIL */
/* #undef HAVE_MAILLOCK_H */
/* #undef HAVE_TOUCHLOCK */

/*#define HAVE_ALLOCA_H 1*/

#define HAVE_DEV_PTMX 1

#define HAVE_GETTIMEOFDAY 1
/* If we don't have gettimeofday,
   the test for GETTIMEOFDAY_ONE_ARGUMENT may succeed,
   but we should ignore it.  */
#ifdef HAVE_GETTIMEOFDAY
/* #undef GETTIMEOFDAY_ONE_ARGUMENT */
#endif
#define HAVE_GETHOSTNAME 1
#define HAVE_GETDOMAINNAME 1
#define HAVE_DUP2 1
#define HAVE_RENAME 1
#define HAVE_CLOSEDIR 1

/* #undef TM_IN_SYS_TIME */
/*#define HAVE_TM_ZONE 1*/
#define HAVE_TZNAME 1
/*#define HAVE_TM_GMTOFF 1*/

/* #undef const */

#define HAVE_LONG_FILE_NAMES 1

/* #undef CRAY_STACKSEG_END */

#define UNEXEC_SRC unexec.c

/* #undef HAVE_LIBXBSD */
/* #undef HAVE_XRMSETDATABASE */
/* #undef HAVE_XSCREENRESOURCESTRING */
/* #undef HAVE_XSCREENNUMBEROFSCREEN */
/* #undef HAVE_XSETWMPROTOCOLS */
/* #undef HAVE_XKBGETKEYBOARD */

#define HAVE_MKDIR 1
#define HAVE_RMDIR 1
#define HAVE_SYSINFO 1
/*#define HAVE_RANDOM 1*/
/*#define HAVE_LRAND48 1*/
#define HAVE_BCOPY 1
#define HAVE_BCMP 1
/*#define HAVE_LOGB 1*/
#define HAVE_FREXP 1
#define HAVE_FMOD 1
/*#define HAVE_RINT 1*/
#define HAVE_CBRT 1
#define HAVE_FTIME 1
/* #undef HAVE_RES_INIT */ /* For -lresolv on Suns.  */
#define HAVE_SETSID 1
#define HAVE_FPATHCONF 1
/*#define HAVE_SELECT 1*/
#define HAVE_MKTIME 1
/* #undef BROKEN_MKTIME */		/* have mktime but it's broken */
/*#define HAVE_EUIDACCESS 1*/
/*#define HAVE_GETPAGESIZE 1*/
#define HAVE_TZSET 1
#define HAVE_SETLOCALE 1
/*#define HAVE_UTIMES 1*/
/*#define HAVE_SETRLIMIT 1*/
/*#define HAVE_SETPGID 1*/
#define HAVE_GETCWD 1
/*#define HAVE_GETWD 1*/
/*#define HAVE_SHUTDOWN 1*/
#define HAVE_STRFTIME 1
#define HAVE_GETADDRINFO 1
#define HAVE___FPENDING 1
#define HAVE_FSEEKO 1
/*#define HAVE_GETLOADAVG 1*/
/* #undef NLIST_STRUCT */
/* #undef NLIST_NAME_UNION */
/*#define HAVE_MBLEN 1*/
/*#define HAVE_MBRLEN 1*/
/*#define HAVE_STRSIGNAL 1*/
#define HAVE_GRANTPT 1
#define HAVE_GETPT 1
#define HAVE_SPEED_T 1		/* speed_t typedef in termios.h */
/* #undef HAVE_STRUCT_TIMEZONE */
#define HAVE_INDEX 1
#define HAVE_RINDEX 1
#define HAVE_MMAP 1
#define HAVE_GAI_STRERROR 1
/*#define HAVE_MKSTEMP 1*/

/* #undef LOCALTIME_CACHE */
#define HAVE_INET_SOCKETS 1

/* #undef HAVE_AIX_SMT_EXP */

/* #undef vfork */
/* #undef size_t */

/* Define if you have the ANSI `strerror' function.
   Otherwise you must have the variable `char *sys_errlist[]'.  */
#define HAVE_STRERROR 1

/* Define if `sys_siglist' is declared by <signal.h>.  */
/*#define SYS_SIGLIST_DECLARED 1*/

/* Define if `struct utimbuf' is declared by <utime.h>.  */
#define HAVE_STRUCT_UTIMBUF 1

/* Define if `struct timeval' is declared by <sys/time.h>.  */
/*#define HAVE_TIMEVAL 1*/

/* If using GNU, then support inline function declarations. */
/* Don't try to switch on inline handling as detected by AC_C_INLINE
   generally, because even if non-gcc compilers accept `inline', they
   may reject `extern inline'.  */
#ifdef __GNUC__
#define INLINE __inline__
#else
#define INLINE
#endif

/* Define this if you don't have struct exception in math.h.  */
#define NO_MATHERR 1

/* Define as `void' if your compiler accepts `void *'; otherwise
   define as `char'.  */
#define POINTER_TYPE void
#define PTR POINTER_TYPE *	/* For strftime.c.  */

/* Number of bits in a file offset, on hosts where this is settable.  */
#define _FILE_OFFSET_BITS 64
/* Define to make ftello visible on some hosts (e.g. HP-UX 10.20).  */
#define _LARGEFILE_SOURCE 1
/* Define for large files, on AIX-style hosts.  */
/* #undef _LARGE_FILES */

#define EMACS_CONFIGURATION "i686-pc-minix"

#define EMACS_CONFIG_OPTIONS " --without-x --without-gcc --prefix=/usr/local"

/* The configuration script defines opsysfile to be the name of the
   s/SYSTEM.h file that describes the system type you are using.  The file
   is chosen based on the configuration name you give.

   See the file ../etc/MACHINES for a list of systems and the
   configuration names to use for them.

   See s/template.h for documentation on writing s/SYSTEM.h files.  */
#define config_opsysfile "s/minix.h" 
#include config_opsysfile

/* The configuration script defines machfile to be the name of the
   m/MACHINE.h file that describes the machine you are using.  The file is
   chosen based on the configuration name you give.

   See the file ../etc/MACHINES for a list of machines and the
   configuration names to use for them.

   See m/template.h for documentation on writing m/MACHINE.h files.  */
#define config_machfile "m/intel386.h"
#include config_machfile

/* Load in the conversion definitions if this system
   needs them and the source file being compiled has not
   said to inhibit this.  There should be no need for you
   to alter these lines.  */

#ifdef SHORTNAMES
#ifndef NO_SHORTNAMES
#include "../shortnames/remap.h"
#endif /* not NO_SHORTNAMES */
#endif /* SHORTNAMES */

/* If no remapping takes place, static variables cannot be dumped as
   pure, so don't worry about the `static' keyword. */
#ifdef NO_REMAP
/* #undef static */
#endif

/* Define `subprocesses' should be defined if you want to
   have code for asynchronous subprocesses
   (as used in M-x compile and M-x shell).
   These do not work for some USG systems yet;
   for the ones where they work, the s/SYSTEM.h file defines this flag.  */

#ifndef VMS
#ifndef USG
/* #define subprocesses */
#endif
#endif

/* Define LD_SWITCH_SITE to contain any special flags your loader may need.  */
/* #undef LD_SWITCH_SITE */

/* Define C_SWITCH_SITE to contain any special flags your compiler needs.  */
/* #undef C_SWITCH_SITE */

/* Define LD_SWITCH_X_SITE to contain any special flags your loader
   may need to deal with X Windows.  For instance, if you've defined
   HAVE_X_WINDOWS above and your X libraries aren't in a place that
   your loader can find on its own, you might want to add "-L/..." or
   something similar.  */
#define LD_SWITCH_X_SITE 

/* Define LD_SWITCH_X_SITE_AUX with an -R option
   in case it's needed (for Solaris, for example).  */
#define LD_SWITCH_X_SITE_AUX 

/* Define C_SWITCH_X_SITE to contain any special flags your compiler
   may need to deal with X Windows.  For instance, if you've defined
   HAVE_X_WINDOWS above and your X include files aren't in a place
   that your compiler can find on its own, you might want to add
   "-I/..." or something similar.  */
#define C_SWITCH_X_SITE 

/* Define STACK_DIRECTION here, but not if m/foo.h did.  */
#ifndef STACK_DIRECTION
/* #undef STACK_DIRECTION */
#endif

/* Define the return type of signal handlers if the s-xxx file
   did not already do so.  */
#define RETSIGTYPE void

/* SIGTYPE is the macro we actually use.  */
#ifndef SIGTYPE
#define SIGTYPE RETSIGTYPE
#endif

#ifdef emacs /* Don't do this for lib-src.  */
/* Tell regex.c to use a type compatible with Emacs.  */
#define RE_TRANSLATE_TYPE Lisp_Object
#define RE_TRANSLATE(TBL, C) CHAR_TABLE_TRANSLATE (TBL, C)
#define RE_TRANSLATE_P(TBL) (XFASTINT (TBL) != 0)
#endif

/* Avoid link-time collision with system mktime if we will use our own.  */
#if ! HAVE_MKTIME || BROKEN_MKTIME
#define mktime emacs_mktime
#endif

/* The rest of the code currently tests the CPP symbol BSTRING.
   Override any claims made by the system-description files.
   Note that on some SCO version it is possible to have bcopy and not bcmp.  */
/* #undef BSTRING */
#if defined (HAVE_BCOPY) && defined (HAVE_BCMP)
#define BSTRING
#endif

/* Define to empty if the keyword `volatile' does not work.  Warning:
   valid code using `volatile' can become incorrect without.  Disable
   with care. */
/* #undef volatile */

/* Some of the files of Emacs which are intended for use with other
   programs assume that if you have a config.h file, you must declare
   the type of getenv.

   This declaration shouldn't appear when alloca.s or Makefile.in
   includes config.h.  */
#ifndef NOT_C_CODE
extern char *getenv ();
#endif

#endif /* EMACS_CONFIG_H */

/* These default definitions are good for almost all machines.
   The exceptions override them in m/MACHINE.h.  */

#ifndef BITS_PER_CHAR
#define BITS_PER_CHAR 8
#endif

#ifndef BITS_PER_SHORT
#define BITS_PER_SHORT 16
#endif

/* Note that lisp.h uses this in a preprocessor conditional, so it
   would not work to use sizeof.  That being so, we do all of them
   without sizeof, for uniformity's sake.  */
#ifndef BITS_PER_INT
#define BITS_PER_INT 32
#endif

#ifndef BITS_PER_LONG
#ifdef _LP64
#define BITS_PER_LONG 64
#else
#define BITS_PER_LONG 32
#endif
#endif

/* Define if the compiler supports function prototypes.  It may do so
   but not define __STDC__ (e.g. DEC C by default) or may define it as
   zero.  */
#define PROTOTYPES 1
/* For mktime.c:  */
#ifndef __P
# if defined PROTOTYPES
#  define __P(args) args
# else
#  define __P(args) ()
# endif  /* GCC.  */
#endif /* __P */


/* Don't include "string.h" or <stdlib.h> in non-C code.  */
#ifndef NOT_C_CODE
#ifdef HAVE_STRING_H
#include "string.h"
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#endif

/* Define HAVE_X_I18N if we have usable i18n support.  */

#ifdef HAVE_X11R6
#define HAVE_X_I18N
#elif defined HAVE_X11R5 && !defined X11R5_INHIBIT_I18N
#define HAVE_X_I18N
#endif

/* Define HAVE_X11R6_XIM if we have usable X11R6-style XIM support.  */

#if defined HAVE_X11R6 && !defined INHIBIT_X11R6_XIM
#define HAVE_X11R6_XIM
#endif

/* Should we enable expensive run-time checking of data types?  */
/* #undef ENABLE_CHECKING */

#if defined __GNUC__ && (__GNUC__ > 2 \
                         || (__GNUC__ == 2 && __GNUC_MINOR__ >= 5))
#define NO_RETURN	__attribute__ ((__noreturn__))
#else
#define NO_RETURN	/* nothing */
#endif








