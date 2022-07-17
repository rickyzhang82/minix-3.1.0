/* Prototypes for library functions used by other library functions */
void error( int );
int _sgn(double);
void _str(double f,char *buffer);
double _log(double);
double _exp(double);
void _asschn(void);
void _out(char *);
void _outnl(void);
void _setchan(int);
void _readint(int *addr);
void _setline(void);
char * salloc(unsigned int length);
void sfree(char *c);
void _trap(void);
