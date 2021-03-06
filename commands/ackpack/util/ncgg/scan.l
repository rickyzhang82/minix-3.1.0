%{
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */
#ifndef NORCSID
static char rcsid2[]= "$Id: scan.l,v 1.3 2005/09/01 12:13:34 beng Exp $";
#endif

#include <stdio.h>
#ifndef _WIN32
#include <unistd.h>
#endif

char *mystrcpy(char *);
int   myatoi(char *);

int lineno=1;
extern char *filename;
#undef yywrap
static int yywrap(void); /* forward prototype */
%}

%%
"/*"                    { char c;
                          c = input(); if (c=='\n') lineno++;
                          do {
                                while (c!='*') {
                                        c = input();
					if (c=='\n') lineno++;
				}
                                c = input();
				if (c=='\n') lineno++;
                          } while (c!='/');
                        }
^\#(line)?[ \t]*[0-9]+[ \t]+\".*\".*$	{
			  int ind,ind2;
			  for (ind=0; yytext[ind] < '0' || yytext[ind]>'9'; ind++)
				;
			  lineno=atoi(&yytext[ind])-1;
			  for(;yytext[ind]!='"';ind++)
				;
			  for(ind2=ind+1;yytext[ind2]!='"';ind2++)
				;
			  yytext[ind2]=0;
			  if (strcmp(yytext+ind+1,filename)!=0)
				filename=mystrcpy(yytext+ind+1);
			}
"=="			return(CMPEQ);
"!="			return(CMPNE);
"<"			return(CMPLT);
"<="			return(CMPLE);
">"			return(CMPGT);
">="			return(CMPGE);
"||"			return(OR2);
"&&"			return(AND2);
"<<"			return(LSHIFT);
">>"			return(RSHIFT);
"!"			return(NOT);
"~"			return(COMP); 
":ro"			{ yylval.yy_int = AD_RO; return(ADORNACCESS);  }
":wo"			{ yylval.yy_int = AD_WO; return(ADORNACCESS);  }
":rw"			{ yylval.yy_int = AD_RW; return(ADORNACCESS);  }
":cc"			{ yylval.yy_int = AD_CC; return(ADORNCC);  }
\$[0-9]+		{ yylval.yy_int = atoi(yytext+1); return(DOLLAR); }
\%[0-9]+		{ yylval.yy_int = atoi(yytext+1); return(PERCENT); }
\%[a-z]			{ yylval.yy_int = yytext[1]-'a'; return(ALLREG); }
[0-9]+|0x[0-9A-Fa-f]+	{ yylval.yy_int = myatoi(yytext); return(NUMBER); }
[_A-Za-z][_A-Za-z0-9]*	{ register symbol *sy_p;
			  if (yyleng==3 &&
			      emhere &&
			      (yylval.yy_int=mlookup(yytext))!=0) {
				return(EMMNEM);
			  }
    			  if ((sy_p=lookup(yytext,symkeyw,justlooking))!=0)
				 return(sy_p->sy_value.syv_keywno); 
			  yylval.yy_str = mystrcpy(yytext); return(IDENT);
			}
\%[_A-Za-z][_A-Za-z0-9]* { yylval.yy_str = mystrcpy(yytext+1);
			   return(PERC_IDENT);
			 }
\"[^"\n]*\"		{ yytext[yyleng-1]=0;
			  yylval.yy_str = mystrcpy(yytext+1);
			  return(STRING);
			}
[0-9][bf]		{ yytext[2]=0;
			  yylval.yy_str = mystrcpy(yytext);
			  return(STRING);
			}
\n			{ lineno++; }
[ \t]*			;
.			return(yytext[0]);
%%
int skipping=0;

static
int
yywrap(void) {

	if (skipping)
		fatal("EOF reached during error recovery");
	return(1);
}

void
skipupto(int tok,char *str)
{
	int i; 

	skipping=1; 
	while (yylex()!=tok)
		;
	for(i=strlen(str); i>0; i--)
		unput(str[i-1]);
	skipping=0; 
}

