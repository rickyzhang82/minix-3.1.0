#include <stdio.h>
#include "object.h"

void arch(void);
void notelib(long);
void arch2(void);
void stop(void);
void fatal(char *,...);
void warning(char *,...);
void error(char *,...);
int do_verbose(char *,...);
void extract(void);
void finish(void);
void beginoutput(void);
void endoutput(void);
void savemagic(void);
int getfile(char *);
void closefile(char *);
void get_modul(void);
void seek(long);
char * getblk(long,long *,int);
void endemit(char *);
void init_symboltable(void);
int hash(char *);
void begin_write(void);
void end_write(void);
void wrt_emit(char *, int, long);
void wrt_nulls(int, long);

/* const.h */
bool setbit(int, char[]);

/* memory.h -- contains prototypes */

ind_t savechar(int,ind_t);

/* out.h */
struct outname * searchname(char *,int);
void namerelocate(struct outname *);
void do_crs(struct outname *, unsigned);
void addbase(struct outname *);
void namecpy(struct outname *, unsigned, long);
void relocate(struct outhead *, char *, struct outname [], struct outrelo *, long);
void savelocal(struct outname *);
void skip_modul(struct outhead *);
void startrelo(struct outhead *);
struct outrelo * nextrelo(void);
char * getemit(struct outhead *, struct outsect *, int);
void entername(struct outname *, int);
unsigned indexof(struct outname *);
void wrt_name(struct outname *, int);

/* ranlib.h */
void savehdr(struct ar_hdr *);
void get_archive_header(struct ar_hdr *);
