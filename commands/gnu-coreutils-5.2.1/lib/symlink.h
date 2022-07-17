/* Header for users of the faked implementation of some sym link 
library routines for Minix. Minix 2.0 does not support symbolic links.
*/

#ifndef _SYMLINK_H_
#define _SYMLINK_H_

#include "../config.h"

#ifdef _MINIX

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

int lstat(const char *path, struct stat *buf);
/* readlink proto for impl in readlink.c; unnecessary; impl now available. */
/*int readlink(const char *path, char *buf, size_t bufsiz);*/
int symlink(const char *name1,char *name2);
	
#endif /* _MINIX */
#endif /* _SYMLINK_H_ */
