mkdir minix
cd minix || exit 1
CFLAGS="-D_MINIX=1 -D_POSIX_SOURCE=1" CC=cc /bin/sh ../Build/configure.minix --prefix=/usr/local --host=minix
make all
