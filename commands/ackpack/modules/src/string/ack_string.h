/*
 * (c) copyright 1993 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/* RCS: $Id: */

#ifndef __ACK_STRING_INCLUDED__
#define __ACK_STRING_INCLUDED__

#include <string.h>

char *strindex(char *s, int c);
char *strrindex(char *s, int c);
char *strzero(char *s);
char *str2bts(char *s, char *b, int *n);
char *long2str(long l, int b);
long str2long(char *s, int b);
char *btscpy(char *s1, const char *s2, int n);
char *btscat(char *s1, int n1, const char *s2, int n2);
int btscmp(const char *s1, int n1, const char *s2, int n2);
char *btszero(char *b, int n);
char *bts2str(const char *b, int n, char *s);

#endif /* __ACK_STRING_INCLUDED__ */
