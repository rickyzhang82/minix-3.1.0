/* $Id: misc.h,v 1.1 2005/09/01 12:13:33 beng Exp $ */

#include "file.h"
#include "position.h"
#include "tokenname.h"
#include "tree.h"
#include "type.h"

void fatal(char *, ...);
void error(char *, ...);
void warning(char *, ...);

void init_types( void );

void init_run( void );
void signal_child( int );
void start_child( p_tree );
int get_bytes( long, t_addr, char * );
int get_string( long, t_addr, char * );
void set_bytes( long, char *, t_addr );
t_addr get_dump( char **, char ** );
int put_dump( char *, char * );
t_addr * get_EM_regs( int );
int set_pc( t_addr );
int send_cont( int );
int singlestep( int, int );
int set_or_clear_breakpoint( t_addr, int );
int set_or_clear_trace( t_addr, t_addr, int );

void DbParser( void );
int DbRead( char * );

void reserve( struct tokenname * );
void prompt( void );
void Commands( void );   /* LLgen-generated */

void lines( p_file, int, int );

void print_params( p_type, t_addr, int );
void print_val( p_type, long, char *, int, int, char * );

int item_addr_actions( t_addr, int, int );
void handle_displays( void );
void add_to_item_list( p_tree );
void remove_from_item_list( int );
p_tree get_from_item_list( int );
void able_item( int, int );
void print_items( p_tree );
void perform_items( void );

int LLlex( void );
int get_name( int );
void LLmessage( int );
void init_del( void );

void enterlog( p_tree );
int setstop( p_tree, int );
int settrace( p_tree, int );
void free_dump( p_tree );

char * symbol2str( int );
