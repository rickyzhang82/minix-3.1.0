s:^.*[ 	]ALLOCDEF[ 	].*"\(.*\)"[ 	]*\([0-9][0-9]*\).*$:\
/* allocation definitions of struct \1 */\
char *st_alloc(char **, unsigned int, int); \
extern struct \1 *h_\1;\
#ifdef DEBUG\
extern int cnt_\1;\
extern char *std_alloc();\
#define new_\1() ((struct \1 *) std_alloc((char **)\&h_\1, sizeof(struct \1), \2, \&cnt_\1))\
#else\
#define	new_\1() ((struct \1 *) st_alloc((char **)\&h_\1, sizeof(struct \1), \2))\
#endif\
#define	free_\1(p) st_free(p, \&h_\1, sizeof(struct \1))\
:
s:^.*[ 	]STATICALLOCDEF[ 	].*"\(.*\)"[ 	]*\([0-9][0-9]*\).*$:\
/* allocation definitions of struct \1 */\
char *st_alloc(char **, unsigned int, int); \
struct \1 *h_\1;\
#ifdef DEBUG\
int cnt_\1;\
#define	new_\1() ((struct \1 *) std_alloc((char **)\&h_\1, sizeof(struct \1), \2, \&cnt_\1))\
#else\
#define	new_\1() ((struct \1 *) st_alloc((char **)\&h_\1, sizeof(struct \1), \2))\
#endif\
#define	free_\1(p) st_free(p, \&h_\1, sizeof(struct \1))\
:
