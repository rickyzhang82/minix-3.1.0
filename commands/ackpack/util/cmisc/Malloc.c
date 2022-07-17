/* Malloc.c */

#include "util.h"

char *
Malloc(size_t n)
{
	void *mem;

	if ((mem = malloc(n)) == 0) {
		fprintf(stderr, "%s: out of memory\n", ProgName);
		exit(1);
	}
	return (char *)mem;
}

