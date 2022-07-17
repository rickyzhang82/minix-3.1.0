/* A dummy implementation of some symbolic link library routines for Minix. 
   Minix does not support symbolic links.
*/

#include "symlink.h"

#ifdef _MINIX

int lstat(const char *path, struct stat *buf) {
	return stat(path,buf);
}

/* Impl available now (also one in readlink.c)
int readlink(const char *path, char *buf, size_t bufsiz) {
	errno = ENOSYS;
	return -1;
}
*/

int symlink(const char *name1, char *name2) {
	errno = ENOSYS;
	return -1;
}
	
#endif /* _MINIX */
