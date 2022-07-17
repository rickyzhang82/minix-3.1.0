#!/usr/bin/make
#
# Makefile for 'i386' assembler
# (C) 2005 Michael Kennett

h = h
m = modules/h
s = modules/src
u = util

# Build directories
l = image
o = obj

# Assume current cpp is working
$o/as/i386/as.y : as/share/comm2.y
	$(CC) -P -E -Ias/i386 -Ias -I$h as/share/comm2.y > $@

$o/as/i386/y.tab.c : $o/as/i386/as.y
	yacc -d -l $o/as/i386/as.y
	if test -f $@ && diff y.tab.c $@ > /dev/null 2>&1 ; then rm y.tab.c ; else mv y.tab.c $@ ; fi
	touch $@
	mv y.tab.h $o/as/i386/y.tab.h

CAS = -I$h -I$m -I$s/object -I$s/system -I$o/as/i386 -Ias/i386 -Ias

$o/as/i386/comm3.o : as/share/comm3.c
	$(CC) -c -DNDEBUG -o $@ $(CAS) as/share/comm3.c
$o/as/i386/comm4.o : as/share/comm4.c
	$(CC) -c -DNDEBUG -D_MINIX -o $@ $(CAS) as/share/comm4.c
$o/as/i386/comm5.o : as/share/comm5.c
	$(CC) -c -DNDEBUG -o $@ $(CAS) as/share/comm5.c
$o/as/i386/comm6.o : as/share/comm6.c
	$(CC) -c -DNDEBUG -o $@ $(CAS) as/share/comm6.c
$o/as/i386/comm7.o : as/share/comm7.c
	$(CC) -c -DNDEBUG -D_MINIX -o $@ $(CAS) as/share/comm7.c
$o/as/i386/comm8.o : as/share/comm8.c
	$(CC) -c -DNDEBUG -o $@ $(CAS) as/share/comm8.c
$o/as/i386/y.tab.o : $o/as/i386/y.tab.c
	$(CC) -c -DNDEBUG -o $@ $(CAS) $o/as/i386/y.tab.c

AS_OBJS = $o/as/i386/comm3.o $o/as/i386/comm4.o $o/as/i386/comm5.o \
	$o/as/i386/comm6.o $o/as/i386/comm7.o $o/as/i386/comm8.o \
	$o/as/i386/y.tab.o

$l/i386/as : $o/as/i386/y.tab.c $(AS_OBJS) $o/libmodule.a
	$(CC) -o $@ $(AS_OBJS) -L$o -lmodule


