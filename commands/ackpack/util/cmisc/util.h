/* util.h */
/* Assorted declarations and utility functions */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <process.h>
#endif

/**/

#define HASHSIZE	257

extern char *ProgName;
extern size_t maxlen;	/* EnHash() */

char * Malloc(size_t n);
char * Salloc(const char *);
int EnHash(const char *);


void CheckId(char *, size_t);
void DoOption(char *);
void BeginOfProgram(void);
int EndOfProgram(void);

