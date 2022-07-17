%{
/* $Id: lex.l,v 1.1 2005/09/01 12:13:22 beng Exp $ */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#ifndef _WIN32
# include <unistd.h>
#endif
# include "oem.h"
# include "Lpars.h"

# define TAB	8	/* Size of a acsii tab (\t) in spaces */
# if (TAB&(TAB-1))!=0
# define TABSTOP(ind)	((ind)+TAB-(ind)%TAB)
# else
# define TABSTOP(ind)	(((ind)+TAB)&(~(TAB-1)))
# endif

struct token token;
int ind=0;		/* Indentation level of current line */
static int tab=0;	/* First indentation found */

int included=0;		/* Is current file included? */
int lineno = 1;

static char * string(char *s);
static long number(char *s);
static long hex_number(char *s);
static int hextoint(int c);
static int character(char **S);
static int char_constant(char *s);
static int indentation(char *s);
static void set_line_file(char *l);
%}

%%
'((\*[^\n])|([^'\n*]))*'	{
	if ((token.t_lval=char_constant(yytext+1))== -1L) 
		report("%s not a character constant", yytext);

	return CHAR_CONST;
}
'[^'\n]*'?			{
	report("missing '.");
	token.t_lval= -1L;

	return CHAR_CONST;
}
\"((\*[^\n])|([^"\n*]))*\"	{
	token.t_sval=string(yytext);

	return STRING;
}
\"[^"\n]*\"?			{
	report("missing \".");
	token.t_sval="";

	return STRING;
}
#[ \t]*"line"?[ \t]*[0-9]+[ \t]*\"[^"\n]*\"	{
	set_line_file(yytext);
	tab=0;
}
#[A-Fa-f0-9]+			{
	token.t_lval=hex_number(yytext+1);

	return NUMBER;
}
[0-9]+				{
	token.t_lval=number(yytext);

	return NUMBER;
}
[A-Za-z][A-Za-z0-9.]*		{
	register key;

	if ((key=keyword(yytext))==IDENTIFIER)
		token.t_sval=strcpy(Malloc(yyleng+1), yytext);
	
	return key;
}
\n[ \f\t]*/"--"			{/* Line with only a comment, don't set tab */
				 lineno++;
				}

\n[ \f\t]*			{

	lineno++;
	ind=indentation(yytext+1);
	if (tab==0)
		tab=ind;
	else
	if (ind%tab!=0)
		warning("indentation not on a %d space boundary", tab);
}
[ \f\t]				{ /* Nothing */ }
[-=<>:,;+*/\[\]()?!&]		return yytext[0];

"\\"				return BS;
":="				return AS;
"<="				return LE;
">="				return GE;
"<>"				return NE;
"<<"				return LS;
">>"				return RS;
"/\\"				return BA;
"\\/"				return BO;
"><"				return BX;

"--"[^\n]*			{ /* Comment is skipped */ }
.				{
	warning((' '<=yytext[0] && yytext[0]<0177) ? "%s'%c')" : "%soctal: %o)",
		"bad character seen (", yytext[0]&0377);
}
%%
static
char *
string(char *s)
{
	register int c;
	register char *p= s;
	char *str= s;
	
	str++; p++;
	while (*str != '"') {
		if ((c=character(&str)) != -1)
			*p++= c;
		else
			return "";
	}

	*p=0;
	*s=p-(s+1);
	return s;
}

static
long
number(char *s)
{
	static char max_str[]="2147483647";
	int maxlen=sizeof max_str-1;
	long num;

	while (*s=='0') { /* skip leading nulls */
		*s++;
		yyleng--;
	}

	if (*s==0)
		num=0L;
	else {
		if ((yyleng>maxlen) || (yyleng==maxlen && strcmp(s, max_str)>0))
			warning("integer constant overflow.");

		num=atol(s);
	}

	return num;
}

static
long
hex_number(char *s)
{
	long number=0L;

	while (*s)
		number=(number<<4)+hextoint(*s++);

	return number;
}

static
int
hextoint(int c)
{
	register int val;
	
	if (islower(c))
		val=(c-'a')+10;
	else
	if (isupper(c))
		val=(c-'A')+10;
	else
		val=c-'0';
	
	return val;
}

static
int
character(char **S)
{
	register char *s= *S;
	register int c, cc;

	if ((c= *s++)=='*') {
		switch (c= *s++) {
		case 'c':
			cc='\r';
			break;
		case 'n':
			cc='\n';
			break;
		case 't':
			cc='\t';
			break;
		case 's':
			cc=' ';
			break;
		case '#':
			if (isxdigit(c= *s++) && isxdigit(*s)) {
				cc= (hextoint(c)<<4)+hextoint(*s++);
				break;
			} else {
				report("two digit hexadecimal const expected.");
				return -1;
			}
		default:
			cc=c;
			break;
		}
	} else
		cc=c;
	
	*S=s;
	return cc;
}

static
int
char_constant(char *s)
{
	register int cc;

	cc=character(&s);

	return (*s=='\'' && cc!= -1) ? cc : -1;
}

static
int
indentation(char *s)
{
	register int in=0, c;

	while (c= *s++) {
		if (c=='\t')
			in=TABSTOP(in);
		else
		if (c=='\f')
			in=0;
		else
			in++;
	}
	
	return in;
}

int
tabulated(int oind,int ind)
{
	if (tab>0 && ind>oind+tab)
		warning("process' indentation too large (changed to %d tab%s)",
			oind/tab+1, oind>=tab ? "s" : "");
	return ind>oind;
}

int rep_tk=0;
struct token rep_token;

void
repeat_token(int tk)
{
	rep_tk=tk;
	rep_token=token;
}

int
scanner(void)
{
	register int tk;

	if (rep_tk>0) {
		tk=rep_tk;;
		rep_tk=0;
		token=rep_token;
		return tk;
	} else
		return yylex();
}

char *
tokenname(int tk,int inst)
{
	if (tk<0400) {
		static char c[7];

		if (' '<tk && tk<='~')
			sprintf(c, "'%c'", tk);
		else
			sprintf(c, "'*#%02x'", tk);
		return c;
	} else {
		switch (tk) {
			char fake_id[1+sizeof(int)*3+1];
			static fake_cnt=0;
		default:
			return keyname(tk);
		case IDENTIFIER:
			if (inst) {
				sprintf(fake_id, "_%d", ++fake_cnt);
				token.t_sval=strcpy(Malloc(strlen(fake_id)+1),
					fake_id);
				return "IDENTIFIER";
			} else
				return token.t_sval;
		case NUMBER:
		case CHAR_CONST:
			token.t_lval=0L;
			return "NUMBER";
		case STRING:
			if (inst) {
				token.t_sval=Malloc(1);
				token.t_sval[0]=0;
			} else
				free(token.t_sval);
			return "STRING";
		case AS:	case LE:	case GE:	case NE:
		case LS:	case RS:	case BA:	case BO:
		case BX:	case BS:	{
			static int op[]= {
				AS, LE, GE, NE, LS, RS, BA, BO, BX, BS
			};
			static char *opc[]= {
				":=", "<=", ">=", "<>", "<<", ">>", "/\\",
				"\\/", "><", "\\"
			};
			register i;
			static char qopc[5];

			for (i=0; op[i]!=tk; i++) ;
			sprintf(qopc, "'%s'", opc[i]);
			return qopc;
			}
		}
	}
}

static
void
set_line_file(char *l)
{
	register char *file;

	while (*l<'0' || *l>'9') l++;

	lineno=0;
	while ('0'<=*l && *l<='9')
		lineno=lineno*10+(*l++ - '0');

	lineno--;

	while (*l++!='"');

	file=l;
	while (*l++!='"');
	*--l=0;

	included=set_file(file);
}

#ifdef yywrap
#undef yywrap
#endif

/* Flex-2.5.4 needs yywrap() */
int
yywrap( void )
{
    return 1;
}

