CFLAGS="-wa -wo -D_MINIX -D_POSIX_SOURCE"
CPPFLAGS="-I/usr/include -I."
LDFLAGS="-i -stack 1m"
LIB="-l socket"
export CFLAGS LDFLAGS CPPFLAGS LIB 
CC=cc /bin/bigsh ./configure --with-zlib
