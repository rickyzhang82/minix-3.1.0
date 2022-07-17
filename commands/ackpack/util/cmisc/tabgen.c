/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
/*
	chtabgen - character table generator 

	Author: Erik Baalbergen (..tjalk!erikb)
	Many mods by Ceriel Jacobs
*/

#include "util.h"
#ifdef __CYGWIN__
# include <fcntl.h>
#endif

#ifndef NORCSID
static const char *RcsId = "$Id: tabgen.c,v 1.3 2005/09/01 12:13:29 beng Exp $";
#endif

#define MAXBUF	256
#define MAXTAB 10000
#define COMCOM	'-'
#define FILECOM	'%'

char *ProgName;		/* callname of this program */

static int InputForm = 'c';
			/* default input format (and, currently, only one) */
static char OutputForm[MAXBUF] = "%s,\n";
				/* format for spitting out a string */
static char *Table[MAXTAB];
static int TabSize = 128;	/* default size of generated table */
static char *InitialValue;	/* initial value of all table entries */

static
void
InitTable(char *ival)
{
	int i;

	for (i = 0; i < TabSize; i++) {
		Table[i] = 0;
	}
	InitialValue = 0;
	if (ival) {
		InitialValue = Salloc(ival);
	}
}

static
void
PrintTable(void)
{
	int i;

	for (i = 0; i < TabSize; i++) {
		if (Table[i]) {
			printf(OutputForm, Table[i]);
		}
		else if (InitialValue) {
			printf(OutputForm, InitialValue);
		}
		else {
			printf(OutputForm, "0");
		}
	}
}

static
int
setval(int ch,char *nm)
{
	char **p = &Table[ch];

	if (ch < 0 || ch >= TabSize) {
		fprintf(stderr, "Illegal index: %d\n", ch);
		return 0;
	}
	if (*p) {
		fprintf(stderr, "Warning: redefinition of index %d\n", ch);
	}
	*p = nm;
	return 1;
}

static
int
quoted(char **pstr)
{
	int ch;
	int i;
	char *str = *pstr;

	if ((*++str >= '0') && (*str <= '9'))	{
		ch = 0;
		for (i = 0; i < 3; i++)	{
			ch = 8 * ch + (*str - '0');
			if (*++str < '0' || *str > '9')
				break;
		}
	}
	else	{
		switch (*str++)	{
		case 'n':
			ch = '\n';
			break;
		case 't':
			ch = '\t';
			break;
		case 'b':
			ch = '\b';
			break;
		case 'r':
			ch = '\r';
			break;
		case 'f':
			ch = '\f';
			break;
		case 'v':
			ch = 013;
			break;
		default :
			ch = *(str - 1);
			break;
		}
	}
	*pstr = str;
	return ch & 0377;
}

static
int
c_proc(char *str,char *Name)
{
	int ch, ch2;
	char *name = Salloc(Name);

	while (*str)	{
		if (*str == '\\')	{
			ch = quoted(&str);
		}
		else	{
			ch = *str++ & 0377;
		}
		if (*str == '-')	{
			if (*++str == '\\')	{
				ch2 = quoted(&str);
			}
			else	{
				ch2 = (*str++ & 0377);
				if( 0 == ch2 ) --str;
			}
			if (ch > ch2) {
				fprintf(stderr, "%s: bad range\n", ProgName);
				return 0;
			}
			while (ch <= ch2) {
				if (! setval(ch, name)) return 0;
				ch++;
			}
		}
		else	{
			if (! setval(ch, name)) return 0;
		}
	}
	return 1;
}

static
int
process(char *str,int format)
{
	char *cstr = str;
	char *Name = cstr;	/* overwrite original string!	*/

	/* strip of the entry name
	*/
	while (*str && *str != ':') {
		if (*str == '\\') {
			++str;
		}
		*cstr++ = *str++;
	}

	if (*str != ':') {
		fprintf(stderr, "%s: bad specification: \"%s\", ignored\n",
			ProgName, Name);
		return 0;
	}
	*cstr = '\0';
	str++;

	switch (format) {

	case 'c':
		return c_proc(str, Name);
	default:
		fprintf(stderr, "%s: bad input format\n", ProgName);
	}
	return 0;
}

static
char *
getline(char *s,int n,FILE *fp)
{
	int c = getc(fp);
	char *str = s;

	while (n--) {
		if (c == EOF) {
			return NULL;
		}
		else
		if (c == '\n') {
			*str = '\0';
			return s;
		}
		*str++ = c;
		c = getc(fp);
	}
	s[n - 1] = '\0';
	return s;
}

static void DoFile(char *);	/* Forward declaration */

static
void
option(char *str)
{
	/*	note that *str indicates the source of the option:
		either COMCOM (from command line) or FILECOM (from a file).
	*/
	switch (*++str) {

	case ' ':	/* command */
	case '\t':
	case '\0':
		break;
	case 'I':	/* for future extension */
		InputForm = *++str;
		break;
	case 'f':	/* input from file ... */
		if (*++str == '\0') {
			fprintf(stderr, "%s: -f: name expected\n", ProgName);
			exit(1);
		}
		DoFile(str);
		break;
	case 'F':	/* new output format string */
		sprintf(OutputForm, "%s\n", ++str);
		break;
	case 'T':	/* insert text literally */
		printf("%s\n", ++str);
		break;
	case 'p':	/* print table */
		PrintTable();
		break;
	case 'C':	/* clear table */
		InitTable((char *)0);
		break;
	case 'i':	/* initialize table with given value */
		if (*++str == '\0') {
			InitTable((char *)0);
		}
		else	InitTable(str);
		break;
	case 'S':
	{
		int i = atoi(++str);

		if (i <= 0 || i > MAXTAB) {
			fprintf(stderr, "%s: size would exceed maximum\n",
				ProgName);
		}
		else {
			TabSize = i;
		}
		break;
	}
	default:
		fprintf(stderr, "%s: bad option -%s\n", ProgName, str);
	}
}

#define BUFSIZE 1024

static
void
DoFile(char *name)
{
	char text[BUFSIZE];
	FILE *fp;

	if ((fp = fopen(name, "r")) == NULL) {
		fprintf(stderr, "%s: cannot read file %s\n", ProgName, name);
		exit(1);
	}
#if defined( __CYGWIN__ )
	setmode( fileno( fp ), O_TEXT );
#endif
	while (getline(text, BUFSIZE, fp) != NULL) {
		if (text[0] == FILECOM) {
			option(text);
		}
		else {
			if (! process(text, InputForm)) {
				exit(1);
			}
		}
	}
}

int
main(int argc,char *argv[])
{
#if defined( __CYGWIN__ )
	setmode( 0, O_TEXT );
	setmode( 1, O_TEXT );
#endif
	ProgName = *argv++;
	argc--;
	while (argc-- > 0) {
		if (**argv == COMCOM) {
			option(*argv++);
		}
		else {
			if (! process(*argv++, InputForm)) {
				exit(1);
			}
		}
	}
	return 0;
}

