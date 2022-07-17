#/usr/bin/make
#
# Makefile for runtime debugging support (grind).
#
# Note:
#  - only 32-bit (i386) Minix is currently supported;
#  - there is a dependence on libc;
#  - two libraries are built, supporting common and separate text/data
#    segments

# XXX dependence on grind that needs cleaning up...
CC1 = $(CC) -I../../util/grind $(CFLAGS) -c
CC=exec cc
INSTALL = install -o bin -g operator -m644

LIB_COM = ./libgrindc.a
LIB_SEP = ./libgrinds.a

# The construction of the two libraries is almost identical; all that
# differs is a preprocessor flag (COMMON_TEXTDATA).
all : $(LIB_COM) $(LIB_SEP)

SOURCES = atlin.c lib.e par_misc.e i386/machdep.s

$(LIB_COM): $(SOURCES)
	LIBRARY=$(LIB_COM) CFLAGS="$(CFLAGS) -DCOMMON_TEXTDATA" $(MAKE) _lib
$(LIB_SEP): $(SOURCES)
	LIBRARY=$(LIB_SEP) $(MAKE) _lib

install: $(LIB_COM) $(LIB_SEP)
	$(INSTALL) $(LIB_COM) /usr/lib/i386/$(LIB_COM)
	$(INSTALL) $(LIB_SEP) /usr/lib/i386/$(LIB_SEP)

clean:
	rm -f *.o core $(LIB_COM) $(LIB_SEP)

OBJECTS = \
	$(LIBRARY)(atlin.o) \
	$(LIBRARY)(lib.o) \
	$(LIBRARY)(par_misc.o) \
	$(LIBRARY)(machdep.o)

# _lib should not be directly invoked by the user, as it assumes
# $(LIBRARY) has been defined in the process environment.
_lib: $(OBJECTS)
	if [ x$(LIBRARY) != x ] ; then aal cr $(LIBRARY) *.o ; rm *.o ; else \
	echo "Error: LIBRARY not defined" ; false ; fi

$(LIBRARY)(atlin.o):	atlin.c
	$(CC1) atlin.c

$(LIBRARY)(lib.o):	lib.e
	$(CC1) lib.e

$(LIBRARY)(par_misc.o):	par_misc.e
	$(CC1) par_misc.e

$(LIBRARY)(machdep.o):	i386/machdep.s
	$(CC1) i386/machdep.s

