/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#include "tokentab.h"

/* Mod van gertjan */
extern int LLsymb;
extern int toknum;

extern int listing,errorcnt;
extern int basicline;

static
void
error_char(char * format,char ch)
{
	if ( !listing ) fprintf(stderr, "LINE %d:",basicline);
	fprintf(stderr, format,ch);
	errorcnt++;
}

static
void
error_string(char * format,char * str)
{
	if ( !listing ) fprintf(stderr, "LINE %d:",basicline);
	fprintf(stderr, format,str);
	errorcnt++;
}


void
LLmessage(int insertedtok)
{
    if ( insertedtok < 0 ) {
	error("Fatal stack overflow\n");
	C_close();
	exit( 1 );
    }

    if ( insertedtok == 0 ) 
	if ( LLsymb < 256 )
	    error_char("%c deleted\n", (char)LLsymb);
	else
	    error_string("%s deleted\n", tokentab[ LLsymb-256 ]);
    else {
	if ( insertedtok < 256 )
	    error_char("%c inserted\n", (char)insertedtok);
	else
	    error_string("%s inserted\n", tokentab[ insertedtok-256 ]);
	toknum = insertedtok;
    }
}
