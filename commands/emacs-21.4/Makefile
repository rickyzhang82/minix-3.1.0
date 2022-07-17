SRCDIR         = /usr/src/commands/emacs-21.4
CHMEM_EMACS    = 16000000
INSTALL_INFO   = echo
PREFIX         = /usr/local
EPREFIX        = /usr/local
BINDIR         = /usr/local/bin
DATADIR        = /usr/local/share
LIBEXECDIR     = /usr/local/libexec
MANDIR         = /usr/local/man
INFODIR        = /usr/local/info
MAKEFILE       = Makefile.minix

MAKEARG = \
	prefix=$(PREFIX) \
	exec_prefix=$(EPREFIX) \
	srcdir=$(SRCDIR) \
	VPATH=$(srcdir) \
	bindir=$(BINDIR) \
	datadir=$(DATADIR) \
	libexecdir=$(LIBEXECDIR) \
	mandir=$(MANDIR) \
	infodir=$(INFODIR) \
	CHMEM_EMACS=$(CHMEM_EMACS) \
	INSTALL_INFO=$(INSTALL_INFO)

all: touchfiles
	make -f $(MAKEFILE) $(MAKEARG)

touchfiles:
	touch src/configure
	touch config.status
	touch src/config.in
	touch src/config.stamp
	touch src/Makefile
	touch lib-src/Makefile
	touch man/Makefile
	touch oldXMenu/Makefile
	touch lwlib/Makefile
	touch leim/Makefile

install: all
	make -f $(MAKEFILE) $(MAKEARG) install

clean:
	make -f $(MAKEFILE) $(MAKEARG) clean
