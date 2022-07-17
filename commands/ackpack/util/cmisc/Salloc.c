/* Salloc.c */

#include "util.h"

char *
Salloc(str)
	const char *str;
{
	if (str == 0)
		str = "";

	return strcpy(Malloc((unsigned)strlen(str) + 1), str);
}

