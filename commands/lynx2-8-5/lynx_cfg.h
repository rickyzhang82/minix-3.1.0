/* lynx_cfg.h.  Generated automatically by configure.  */
/* The configure script translates "config.hin" into "lynx_cfg.h" */
#ifndef LYNX_CFG_H
#define LYNX_CFG_H 1

/* #undef ALL_CHARSETS */		/* AC_ARG_WITH(charsets) */
/* #undef ALT_CHAR_SET */		/* CF_ALT_CHAR_SET */
#define ANSI_VARARGS 1		/* CF_VARARGS */
/* #undef ARCHIVE_ONLY */		/* CF_ARG_DISABLE(dired-archive) */
#define BZIP2_PATH "/usr/local/bin/bzip2"		/* CF_PATH_PROG(bzip2) */
#define CAN_SET_ERRNO 1		/* CF_SET_ERRNO */
/* #undef CHMOD_PATH */		/* CF_PATH_PROG(chmod) */
/* #undef CJK_EX */			/* CF_ARG_ENABLE(cjk) */
/* #undef COLOR_CURSES */		/* CF_COLOR_CURSES */
#define COMPRESS_PATH "/usr/bin/compress"		/* CF_PATH_PROG(compress) */
/* #undef COPY_PATH */		/* CF_PATH_PROG(cp) */
/* #undef CURS_PERFORMANCE */		/* CF_CURS_PERFORMANCE */
/* #undef DEBUG */			/* configure --enable-debug */
/* #undef DECL_ERRNO */
/* #undef DECL_GETGRGID */
/* #undef DECL_GETGRNAM */
/* #undef DECL_STRSTR */
#define DECL_SYS_ERRLIST 1
#define DIRED_SUPPORT 1		/* AC_ARG_WITH(dired) */
/* #undef DISABLE_BIBP */		/* CF_ARG_DISABLE(bibp-urls) */
/* #undef DISABLE_FINGER */		/* CF_ARG_DISABLE(finger) */
/* #undef DISABLE_FTP */		/* CF_ARG_DISABLE(ftp) */
/* #undef DISABLE_GOPHER */		/* CF_ARG_DISABLE(gopher) */
/* #undef DISABLE_NEWS */		/* CF_ARG_DISABLE(news) */
#define DISP_PARTIAL 1		/* CF_ARG_ENABLE(partial) */
#define DONT_TRACK_INTERNAL_LINKS 1 /* CF_ARG_DISABLE(internal-links) */
/* #undef ENABLE_IPV6 */		/* CF_CHECK_IPV6 */
/* #undef ENABLE_NLS */		/* defined if NLS is requested */
/* #undef ENABLE_OPTS_CHANGE_EXEC */	/* CF_ARG_ENABLE(change-exec) */
/* #undef EXEC_LINKS */		/* CF_ARG_ENABLE(exec-links) */
/* #undef EXEC_SCRIPTS */		/* CF_ARG_ENABLE(exec-scripts) */
/* #undef EXP_ADDRLIST_PAGE */	/* CF_ARG_ENABLE(addrlist-page) */
#define EXP_ALT_BINDINGS 1		/* CF_ARG_ENABLE(alt-bindings) */
/* #undef EXP_CHARSET_CHOICE */	/* CF_ARG_ENABLE(charset-choice) */
/* #undef EXP_CHARTRANS_AUTOSWITCH */	/* CF_ARG_ENABLE(font-switch) */
/* #undef EXP_JUSTIFY_ELTS */		/* CF_ARG_ENABLE(justify-elts) */
/* #undef EXP_KEYBOARD_LAYOUT */	/* CF_ARG_ENABLE(kbd-layout) */
#define EXP_LOCALE_CHARSET 1	/* CF_ARG_ENABLE(locale-charset) */
/* #undef EXP_LIBJS */		/* CF_ARG_ENABLE(libjs) */
/* #undef EXP_NESTED_TABLES */	/* CF_ARG_ENABLE(nested-tables) */
#define FANCY_CURSES 1		/* CF_FANCY_CURSES */
/* #undef GCC_NORETURN */		/* CF_GCC_ATTRIBUTES */
/* #undef GCC_PRINTF */		/* CF_GCC_ATTRIBUTES */
/* #undef GCC_UNUSED */		/* CF_GCC_ATTRIBUTES */
#define GETGROUPS_T gid_t		/* AC_TYPE_GETGROUPS */
#define GZIP_PATH "/usr/local/bin/gzip"		/* CF_PATH_PROG(gzip) */
#define HAVE_ALLOCA 1		/* AM_GNU_GETTEXT/AC_FUNC_ALLOCA */
#define HAVE_ALLOCA_H 1		/* AM_GNU_GETTEXT/AC_FUNC_ALLOCA */
/* #undef HAVE_ARGZ_H */		/* AM_GNU_GETTEXT */
#define HAVE_ARPA_INET_H 1
/* #undef HAVE_ASSUME_DEFAULT_COLORS */ /* ncurses extension */
#define HAVE_BSD_TOUCHLINE 1	/* CF_CURS_TOUCHLINE */
/* #undef HAVE_CATGETS */		/* defined if you want to use non-GNU catgets */
#define HAVE_CBREAK 1
/* #undef HAVE_CURSESX_H */
#define HAVE_CUSERID 1
/* #undef HAVE_DCGETTEXT */		/* AM_GNU_GETTEXT */
/* #undef HAVE_DEFINE_KEY */
/* #undef HAVE_DELSCREEN */		/* CF_CURSES_FUNCS  */
#define HAVE_DIRENT_H 1		/* AC_HEADER_DIRENT */
#define HAVE_FCNTL_H 1		/* have <fcntl.h> */
/* #undef HAVE_FTIME */
/* #undef HAVE_GAI_STRERROR */	/* CF_CHECK_IPV6 */
/* #undef HAVE_GETADDRINFO */		/* CF_CHECK_IPV6 */
/* #undef HAVE_GETATTRS */
/* #undef HAVE_GETBEGX */
/* #undef HAVE_GETBEGY */
/* #undef HAVE_GETBKGD */		/* CF_COLOR_CURSES */
#define HAVE_GETCWD 1
#define HAVE_GETGROUPS 1
/* #undef HAVE_GETTEXT */		/* defined if you want to use non-GNU gettext */
#define HAVE_GETTIMEOFDAY 1
#define HAVE_GETUID 1
#define HAVE_H_ERRNO 1
#define HAVE_INET_ATON 1		/* CF_INET_ADDR */
/* #undef HAVE_JCURSES_H */
#define HAVE_KEYPAD 1
/* #undef HAVE_LANGINFO_CODESET */	/* AM_LANGINFO_CODESET */
/* #undef HAVE_LC_MESSAGES */		/* locale messages */
/* #undef HAVE_LIBDBMALLOC */		/* --with-dbmalloc */
/* #undef HAVE_LIBDMALLOC */		/* --with-dmalloc */
/* #undef HAVE_LIBGETTEXT_H */	/* defined if you want to use bundled gettext */
/* #undef HAVE_LIBINTL_H */		/* AM_GNU_GETTEXT, or cleanup from that */
/* #undef HAVE_LIBUTF8_H */		/* may be needed for libncursesw */
#define HAVE_LIMITS_H 1
#define HAVE_LOCALE_H 1
#define HAVE_LSTAT 1		/* CF_FUNC_LSTAT */
/* #undef HAVE_MALLOC_H */		/* AM_GNU_GETTEXT */
/* #undef HAVE_MBSTATE_T */		/* CF_WIDEC_CURSES */
/* #undef HAVE_MKDTEMP */
#define HAVE_MKTEMP 1
/* #undef HAVE_MMAP */		/* AM_GNU_GETTEXT */
/* #undef HAVE_MUNMAP */		/* AM_GNU_GETTEXT */
/* #undef HAVE_NAPMS */
/* #undef HAVE_NCURSESW_NCURSES_H */	/* defined if we include <ncursesw/ncurses.h> */
/* #undef HAVE_NCURSESW_TERM_H */	/* have <ncursesw/term.h> */
/* #undef HAVE_NCURSES_H */		/* defined if we include <ncurses.h> */
/* #undef HAVE_NCURSES_NCURSES_H */	/* defined if we include <ncurses/ncurses.h> */
/* #undef HAVE_NCURSES_TERM_H */	/* have <ncurses/term.h> */
/* #undef HAVE_NEWPAD */
/* #undef HAVE_NEWTERM */
/* #undef HAVE_NL_TYPES_H */		/* AM_GNU_GETTEXT */
/* #undef HAVE_PNOUTREFRESH */
#define HAVE_POPEN 1
#define HAVE_PUTENV 1
#define HAVE_READDIR 1
/* #undef HAVE_RESIZETERM */
/* #undef HAVE_RESOLV_H */
/* #undef HAVE_SETENV */		/* AM_GNU_GETTEXT */
#define HAVE_SETLOCALE 1
#define HAVE_SETUID 1
#define HAVE_SIGACTION 1		/* CF_FUNC_SIGACTION */
#define HAVE_SIZECHANGE 1		/* CF_SIZECHANGE */
#define HAVE_STDARG_H 1		/* CF_VARARGS */
#define HAVE_STDLIB_H 1
/* #undef HAVE_STPCPY */		/* AM_GNU_GETTEXT */
#define HAVE_STRCASECMP 1		/* AM_GNU_GETTEXT */
#define HAVE_STRCHR 1		/* AM_GNU_GETTEXT */
#define HAVE_STRERROR 1
#define HAVE_STRING_H 1
/* #undef HAVE_SYSLOG_H */
/* #undef HAVE_SYSV_TOUCHLINE */	/* CF_CURS_TOUCHLINE */
/* #undef HAVE_SYS_DIR_H */		/* AC_HEADER_DIRENT */
/* #undef HAVE_SYS_FCNTL_H */		/* have <sys/fcntl.h> */
/* #undef HAVE_SYS_FILIO_H */		/* have <sys/filio.h> */
#define HAVE_SYS_IOCTL_H 1		/* have <sys/ioctl.h> */
/* #undef HAVE_SYS_NDIR_H */		/* AC_HEADER_DIRENT */
#define HAVE_SYS_PARAM_H 1		/* AM_GNU_GETTEXT */
/* #undef HAVE_SYS_TIMEB_H */		/* have <sys/timeb.h> */
#define HAVE_SYS_WAIT_H 1		/* have <sys/wait.h> */
#define HAVE_TERMIOS_H 1		/* have <termios.h> */
/* #undef HAVE_TERMIO_H */		/* have <termio.h> */
/* #undef HAVE_TERM_H */		/* have <term.h> */
/* #undef HAVE_TOUCHLINE */
#define HAVE_TOUCHWIN 1
/* #undef HAVE_TRUNCATE */
#define HAVE_TTYNAME 1
/* #undef HAVE_TTYTYPE */
/* #undef HAVE_TYPE_UNIONWAIT */	/* CF_UNION_WAIT */
#define HAVE_UNISTD_H 1		/* have <unistd.h> */
/* #undef HAVE_UNSETENV */
/* #undef HAVE_USE_DEFAULT_COLORS */	/* ncurses extension */
#define HAVE_UTMP 1		/* CF_UTMP */
#define HAVE_UTMP_UT_HOST 1	/* CF_UTMP_UT_HOST */
/* #undef HAVE_UTMP_UT_SESSION */	/* CF_UTMP_UT_SESSION */
/* #undef HAVE_UTMP_UT_XSTATUS */	/* CF_UTMP_UT_XSTATUS */
/* #undef HAVE_UTMP_UT_XTIME */	/* CF_UTMP_UT_XTIME */
/* #undef HAVE_VALUES_H */		/* AM_GNU_GETTEXT */
/* #undef HAVE_VARARGS_H */		/* CF_VARARGS */
/* #undef HAVE_VASPRINTF */
/* #undef HAVE_VFORK_H */		/* have <vfork.h> */
#define HAVE_WAITPID 1
/* #undef HAVE_WATTR_GET */
/* #undef HAVE_WBORDER */
/* #undef HAVE_WREDRAWLN */
/* #undef HAVE_WRESIZE */
/* #undef HAVE_XCURSES */		/* CF_PDCURSES_X11 */
/* #undef HAVE___ARGZ_COUNT */	/* AM_GNU_GETTEXT */
/* #undef HAVE___ARGZ_NEXT */		/* AM_GNU_GETTEXT */
/* #undef HAVE___ARGZ_STRINGIFY */	/* AM_GNU_GETTEXT */
/* #undef IGNORE_CTRL_C */		/* FIXME: make tests? */
/* #undef INCLUDE_PROTOTYPES */	/* CF_SOCKS5 */
#define INSTALL_ARGS "-c"		/* CF_PATH_PROG(install) */
#define INSTALL_PATH "/bin/install"		/* CF_PATH_PROG(install) */
/* #undef LINUX */			/* FIXME: make tests? */
#define LOCALE 1			/* for locale support */
#define LONG_LIST 1		/* CF_ARG_DISABLE(long-list) */
/* #undef LYNXCGI_LINKS */		/* CF_ARG_ENABLE(cgi-links) */
#define LYNX_CFG_FILE "/usr/local/lib/lynx.cfg"		/* $libdir/lynx.cfg */
/* #undef LYNX_LSS_FILE */		/* $libdir/lynx.lss */
#define LYNX_RAND_MAX INT_MAX		/* CF_SRAND */
/* #undef LY_FIND_LEAKS */		/* CF_ARG_ENABLE(find-leaks) */
/* #undef LY_TRACELINE */		/* CF_ARG_ENABLE(vertrace) */
/* #undef MKDIR_PATH */		/* CF_PATH_PROG(mkdir) */
#define MV_PATH "/bin/mv"			/* CF_PATH_PROG(mv) */
/* #undef NCURSES */			/* defined for ncurses support */
/* #undef NCURSES_BROKEN */		/* defined for ncurses color support */
/* #undef NEED_PTEM_H */		/* CF_SIZECHANGE */
/* #undef NEED_REMOVE */		/* CF_REMOVE_BROKEN */
/* #undef NEED_WCHAR_H */		/* CF_WIDEC_CURSES */
#define NGROUPS NGROUPS_MAX			/* CF_NGROUPS */
/* #undef NO_CHANGE_EXECUTE_PERMS */	/* CF_ARG_DISABLE(dired-xpermit) */
/* #undef NO_CONFIG_INFO */		/* CF_ARG_DISABLE(config-info) */
/* #undef NO_EXTENDED_HTMLDTD */	/* CF_ARG_DISABLE(extended-dtd) */
/* #undef NO_LYNX_TRACE */		/* CF_ARG_DISABLE(trace) */
/* #undef NO_OPTION_FORMS */		/* CF_ARG_DISABLE(forms-options) */
/* #undef NO_OPTION_MENU */		/* CF_ARG_DISABLE(option-menu) */
/* #undef NO_PARENT_DIR_REFERENCE */	/* CF_ARG_DISABLE(parent-dir-refs) */
/* #undef NSL_FORK */			/* CF_ARG_ENABLE(nsl-fork) */
/* #undef OK_INSTALL */
#define OK_OVERRIDE 1		/* CF_ARG_DISABLE(dired-override) */
#define OK_PERMIT 1		/* CF_ARG_DISABLE(dired-permit) */
/* #undef REAL_UNIX_SYSTEM */		/* CF_SLANG_UNIX_DEFS */
#define RLOGIN_PATH "/usr/bin/rlogin"		/* CF_PATH_PROG(rlogin) */
#define RM_PATH "/bin/rm"			/* CF_PATH_PROG(rm) */
/* #undef SOCKS */			/* CF_SOCKS, CF_SOCKS5 */
#define STDC_HEADERS 1
#define SYSTEM_MAIL "unknown"		/* CF_DEFINE_PROG */
#define SYSTEM_MAIL_FLAGS "-t -oi"	/* CF_SYSTEM_MAIL_FLAGS */
#define SYSTEM_NAME "minix"		/* CF_CHECK_CACHE */
#define TAR_DOWN_OPTIONS "-xf"		/* CF_TAR_OPTIONS */
#define TAR_FILE_OPTIONS ""		/* CF_TAR_OPTIONS */
#define TAR_PATH "/usr/bin/tar"			/* CF_PATH_PROG(tar) */
#define TAR_PIPE_OPTIONS "-"		/* CF_TAR_OPTIONS */
#define TAR_UP_OPTIONS "-cf"		/* CF_TAR_OPTIONS */
#define TELNET_PATH "/usr/bin/telnet"		/* CF_PATH_PROG(telnet) */
/* #undef TERMIO_AND_CURSES */	/* CF_TERMIO_AND_CURSES workaround */
/* #undef TERMIO_AND_TERMIOS */	/* CF_TERMIO_AND_TERMIOS workaround */
/* #undef TN3270_PATH */		/* CF_PATH_PROG(tn3270) */
/* #undef TOUCH_PATH */		/* CF_PATH_PROG(touch) */
/* #undef ULTRIX */			/* config.sub */
#define UNCOMPRESS_PATH "/usr/local/bin/gunzip"		/* CF_PATH_PROG(gunzip) */
#define UNDERLINE_LINKS 0		/* CF_ARG_ENABLE(underlines) */
#define UNIX 1
/* #undef UNZIP_PATH */		/* CF_PATH_PROG(unzip) */
/* #undef USE_BZLIB */		/* AC_ARG_WITH(bzlib) */
/* #undef USE_COLOR_STYLE */		/* CF_ARG_ENABLE(color-style) */
/* #undef USE_DEFAULT_COLORS */	/* CF_ARG_ENABLE(default-colors) */
/* #undef USE_EXECVP */		/* CF_ARG_DISABLE(full-paths) */
/* #undef USE_EXTERNALS */		/* CF_ARG_ENABLE(externs) */
#define USE_FCNTL 1		/* CF_FIONBIO */
#define USE_FILE_UPLOAD 1		/* CF_ARG_ENABLE(file-upload) */
/* #undef USE_GNUTLS_INCL */		/* CF_GNUTLS */
/* #undef USE_OPENSSL_INCL */		/* CF_SSL */
#define USE_PERSISTENT_COOKIES 1	/* CF_ARG_ENABLE(persistent-cookies) */
#define USE_PRETTYSRC 1		/* CF_ARG_ENABLE(prettysrc) */
#define USE_READPROGRESS 1		/* CF_ARG_ENABLE(read-eta) */
/* #undef USE_SCROLLBAR */		/* CF_ARG_ENABLE(scrollbar) */
/* #undef USE_SLANG */		/* AC_ARG_WITH(screen=slang) */
/* #undef USE_SOCKS4_PREFIX */	/* CF_SOCKS5 */
/* #undef USE_SOCKS5 */		/* CF_SOCKS5 */
#define USE_SOURCE_CACHE 1		/* CF_ARG_ENABLE(source-cache) */
/* #undef USE_SSL */			/* CF_SSL */
/* #undef USE_SYSV_UTMP */		/* CF_UTMP */
/* #undef USE_X509_SUPPORT */		/* CF_GNUTLS, CF_SSL */
#define USE_ZLIB 1			/* AC_ARG_WITH(zlib) */
/* #undef UTF8 */			/* CF_SLANG_CPPFLAGS */
/* #undef UTMPX_FOR_UTMP */		/* use <utmpx.h> since <utmp.h> not found */
#define UUDECODE_PATH "/usr/bin/uudecode"		/* CF_PATH_PROG(uudecode) */
/* #undef WAITPID_USES_UNION */	/* CF_FUNC_WAIT */
/* #undef WAIT_USES_UNION */		/* CF_FUNC_WAIT */
/* #undef WIDEC_CURSES */		/* CF_WIDEC_CURSES */
/* #undef XCURSES */			/* CF_PDCURSES_X11 */
#define ZCAT_PATH "/usr/bin/zcat"		/* CF_PATH_PROG(zcat) */
/* #undef ZIP_PATH */			/* CF_PATH_PROG(zip) */
/* #undef _ALL_SOURCE */		/* AC_AIX */
#define inline 			/* AC_C_INLINE */
#define lynx_rand random		/* CF_SRAND */
#define lynx_srand srandom		/* CF_SRAND */
/* #undef mode_t */			/* AC_TYPE_MODE_T */
/* #undef off_t */			/* AC_TYPE_OFF_T */
/* #undef pid_t */			/* AC_TYPE_PID_T */
/* #undef uid_t */			/* AC_TYPE_UID_T */
/* #undef ut_name */			/* CF_UTMP */
/* #undef ut_xstatus */		/* CF_UTMP_UT_XSTATUS */
/* #undef ut_xtime */			/* CF_UTMP_UT_XTIME */

#ifdef GZIP_PATH
#define OK_GZIP 1			/* CF_ARG_DISABLE(dired-gzip) */
#endif

#ifdef TAR_PATH
#define OK_TAR 1			/* CF_ARG_DISABLE(dired-tar) */
#endif

#ifdef UUDECODE_PATH
#define OK_UUDECODE 1		/* CF_ARG_DISABLE(dired-uudecode) */
#endif

#ifdef ZIP_PATH
#define OK_ZIP 1			/* CF_ARG_DISABLE(dired-zip) */
#endif

/*
 * U/Win defines vfork() as a macro in vfork.h, which is included from unistd.h.
 */
#ifndef HAVE_VFORK_H
#define vfork fork			/* AC_FUNC_FORK */
#endif

/* 'const' may be defined externally by the compiler-wrapper, as in 'unproto'
 * or by AC_C_CONST
 */
#ifndef const
/* #undef const */
#endif

/*
 * The configure script generates LYHelp.h (handcrafted makefiles may not do
 * this, so we set a definition):
 */
#define HAVE_LYHELP_H 1

/* FIXME:DGUX (done in $host_os case-statement) */
/* FIXME:DGUX_OLD */
/* FIXME:HP_TERMINAL */
/* FIXME:REVERSE_CLEAR_SCREEN_PROBLEM */
/* FIXME:SHORTENED_RBIND */
/* FIXME:SNAKE */
/* FIXME:SVR4_BSDSELECT (done in $host_os case-statement) */

/* Some older socks libraries, especially AIX need special definitions */
#if defined(_AIX) && !defined(USE_SOCKS5)
/* #undef accept */
/* #undef bind */
/* #undef connect */
/* #undef getpeername */
/* #undef getsockname */
/* #undef listen */
/* #undef recvfrom */
/* #undef select */
#endif

#ifdef HAVE_SYSLOG_H
/* #undef SYSLOG_REQUESTED_URLS */	/* CF_ARG_ENABLE(syslog) */
#endif

#ifndef HAVE_LSTAT
#define lstat stat
#endif

#ifdef DECL_GETGRGID
extern struct group * getgrgid ();
#endif

#ifdef DECL_GETGRNAM
extern struct group * getgrnam ();
#endif

#ifdef DECL_STRSTR
extern char * strstr ();
#endif

#endif /* LYNX_CFG_H */
