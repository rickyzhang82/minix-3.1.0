# template-makefile for Lynx src directory

SHELL		= /bin/sh
CDPATH		= .


prefix		= /usr/local
exec_prefix	= ${prefix}
top_srcdir	= ..
srcdir		= .

top_builddir	= ..

# see po/makefile
localedir	= /usr/local/share/locale

# Symbols which the configure script can set in each makefile:
CC		= cc
CPP		= cc -E
CFLAGS		= -wa -wo -D_MINIX -D_POSIX_SOURCE 
DEFS		= -DHAVE_CONFIG_H
CHARSET_DEFS	= 
CPPFLAGS	=  -I/usr/local/include -I/usr/include -I. -D_XOPEN_SOURCE=500 -D_POSIX_C_SOURCE

x		= 
o		= .o

LIBS		= -L/usr/local/lib -lz -lcurses   $(RESOLVLIB) $(WAISLIB) $(SITE_LIBS)
LDFLAGS		= -i -stack 1m

# Symbols inherited from the top-level makefile
RESOLVLIB	= # FIXME: set in parent makefile
SITE_DEFS	= # FIXME: set in parent makefile
SITE_LIBS	= # FIXME: set in parent makefile
WAISLIB		= # FIXME: set in parent makefile

WWWINC		= WWW/Library/Implementation
WWWLIB		= $(top_builddir)/WWW/Library/Implementation/libwww.a

INTLLIB		= 
INTLDIR_CPPFLAGS= #-I$(top_srcdir)/intl

CPP_OPTS	= $(CPPFLAGS) $(DEFS) $(CHARSET_DEFS) \
		-DLOCALEDIR=\"$(localedir)\" \
		-I. \
		-I$(top_builddir) \
		-Ichrtrans \
		-I$(srcdir)/chrtrans \
		-I$(top_srcdir) \
		-I$(top_srcdir)/src \
		-I$(top_srcdir)/$(WWWINC) \
		$(INTLDIR_CPPFLAGS) $(SITE_DEFS)
CC_OPTS		= $(CPP_OPTS) $(CFLAGS)

LINT		= 
LINTOPTS	=

COMPRESS_PROG	=
COMPRESS_EXT	=

CHARTRANS_OBJS	= UCdomap$o UCAux$o UCAuto$o
OBJS	= \
	LYClean$o LYShowInfo$o LYEdit$o LYStrings$o LYMail$o \
	HTAlert$o GridText$o LYGetFile$o LYMain$o LYMainLoop$o \
	LYCurses$o LYBookmark$o LYUtils$o LYOptions$o \
	LYReadCFG$o LYSearch$o LYHistory$o LYForms$o LYPrint$o \
	LYrcFile$o LYDownload$o LYNews$o LYKeymap$o HTML$o \
	HTFWriter$o HTInit$o DefaultStyle$o LYUpload$o \
	LYLeaks$o LYexit$o LYJump$o LYList$o LYCgi$o \
	LYTraversal$o LYEditmap$o LYCharSets$o LYCharUtils$o \
	LYMap$o LYCookie$o LYStyle$o LYHash$o LYPrettySrc$o \
	TRSTable$o $(CHARTRANS_OBJS)  LYLocal$o

C_SRC	= $(OBJS:$o=.c)

all: lynx$x

.SUFFIXES : $o .i

.c$o:
# compiling
	$(CC) $(CC_OPTS) -c $(srcdir)/$*.c

.c.i:
# compiling
	$(CPP) -C $(CPP_OPTS) $(srcdir)/$*.c >$@

lynx$x:   message do_chartrans_stuff $(top_builddir)/LYHelp.h $(OBJS) $(WWWLIB)
	@echo "Linking and creating Lynx executable"
	$(CC) $(CC_OPTS) $(LDFLAGS) -o $@  $(OBJS) $(WWWLIB) $(INTLLIB) $(LIBS)
	@echo "Copying Lynx executable into top-level directory"
	rm -f $(top_builddir)/$@
	cp $@ $(top_builddir)/
	@echo "Welcome to Lynx!"

message:
	@echo "Compiling Lynx sources"

do_chartrans_stuff:
	-cd chrtrans && $(MAKE) \
		SITE_DEFS="$(SITE_DEFS)" \
		CFLAGS="$(CFLAGS)" \
		CPPFLAGS="$(CPPFLAGS)" \
		CC="$(CC)" tables

lint:
	$(LINT) $(LINTOPTS) $(CPP_OPTS) *.c  > $(top_builddir)/lint.lynx

clean:
	rm -f lynx$x core *.core *.leaks *.i *$o *.bak tags TAGS
	cd chrtrans && $(MAKE) clean

distclean: clean

CMN=$(top_srcdir)/WWW/Library/Implementation/

HTFWriter$o :		$(top_srcdir)/userdefs.h
HTInit$o :		$(top_srcdir)/userdefs.h
LYCharSets$o :		$(top_srcdir)/userdefs.h
LYGetFile$o :		$(top_srcdir)/userdefs.h
LYKeymap$o :		$(top_srcdir)/userdefs.h
LYMail$o :		$(top_srcdir)/userdefs.h
LYMain$o :		$(top_srcdir)/userdefs.h $(top_builddir)/lynx_cfg.h
LYMainLoop$o :		$(top_srcdir)/userdefs.h
LYOptions$o :		$(top_srcdir)/userdefs.h
LYReadCFG$o :		$(top_srcdir)/userdefs.h
LYShowInfo$o :		$(top_builddir)/cfg_defs.h
LYTraversal$o :		$(top_srcdir)/userdefs.h
LYUtils$o :		$(top_srcdir)/userdefs.h
LYrcFile$o :		$(top_srcdir)/userdefs.h
LYLeaks$o :		$(CMN)LYLeaks.h $(CMN)HTString.h

CHRTR= chrtrans/

TABLES= \
 $(CHRTR)cp1250_uni.h \
 $(CHRTR)cp1251_uni.h \
 $(CHRTR)cp1252_uni.h \
 $(CHRTR)cp1253_uni.h \
 $(CHRTR)cp1255_uni.h \
 $(CHRTR)cp1256_uni.h \
 $(CHRTR)cp1257_uni.h \
 $(CHRTR)cp437_uni.h \
 $(CHRTR)cp737_uni.h \
 $(CHRTR)cp775_uni.h \
 $(CHRTR)cp850_uni.h \
 $(CHRTR)cp852_uni.h \
 $(CHRTR)cp862_uni.h \
 $(CHRTR)cp864_uni.h \
 $(CHRTR)cp866_uni.h \
 $(CHRTR)cp869_uni.h \
 $(CHRTR)def7_uni.h \
 $(CHRTR)dmcs_uni.h \
 $(CHRTR)hp_uni.h \
 $(CHRTR)iso01_uni.h \
 $(CHRTR)iso02_uni.h \
 $(CHRTR)iso03_uni.h \
 $(CHRTR)iso04_uni.h \
 $(CHRTR)iso05_uni.h \
 $(CHRTR)iso06_uni.h \
 $(CHRTR)iso07_uni.h \
 $(CHRTR)iso08_uni.h \
 $(CHRTR)iso09_uni.h \
 $(CHRTR)iso10_uni.h \
 $(CHRTR)iso15_uni.h \
 $(CHRTR)koi8r_uni.h \
 $(CHRTR)mac_uni.h \
 $(CHRTR)mnem_suni.h \
 $(CHRTR)mnem2_suni.h \
 $(CHRTR)next_uni.h \
 $(CHRTR)rfc_suni.h \
 $(CHRTR)utf8_uni.h \
 $(CHRTR)viscii_uni.h

$(TABLES):
	-cd chrtrans && $(MAKE) tables

UCdomap$o : UCdomap.c chrtrans/UCkd.h chrtrans/makeuctb$x chrtrans/makeuctb.c \
	UCdomap.h $(CMN)UCMap.h $(TABLES) $(top_srcdir)/userdefs.h

chrtrans/makeuctb$x:
	cd chrtrans; make makeuctb$x

UCAux$o : UCAux.c $(CMN)UCAux.h $(CMN)UCDefs.h
LYCookie$o : $(top_srcdir)/userdefs.h

depend : $(TABLES)
	makedepend -fmakefile -- $(CC_OPTS) -- $(C_SRC)

# DO NOT DELETE THIS LINE -- make depend depends on it.
