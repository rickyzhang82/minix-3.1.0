/* $Id: em_ego.c,v 1.3 2005/09/01 12:13:30 beng Exp $ */

/* Driver program for the global optimizer. It might even become the global
   optimizer itself one day ...
*/

#ifndef _WIN32
# include <sys/wait.h>
# include <unistd.h>
#else
# include <io.h>
#endif
#include <stdlib.h>
#include <signal.h>
#include <system.h>
#include <stdio.h>
#include <stdarg.h>
#include <ack_string.h>

#define	IC	1
#define CF	2
#define IL	3
#define CS	4
#define SR	5
#define UD	6
#define LV	7
#define RA	8
#define SP	9
#define BO	10
#define CJ	11
#define CA	12

static char *phnames[] = {
  0,
  "ic",
  "cf",
  "il",
  "cs",
  "sr",
  "ud",
  "lv",
  "ra",
  "sp",
  "bo",
  "cj",
  "ca",
  0
};

#define MAXUPHASES	64		/* max # of phases to be run */
#define MAXARGS		1024		/* mar # of args */
#define NTEMPS		4		/* # of temporary files; not tunable */

#ifdef __dos
extern int	dosexec();
#endif

static char	ddump[128]; /*TMP_DIR*/	/* data label dump file */
static char	pdump[128]; /*TMP_DIR*/	/* procedure name dump file */
static char	tmpbufs[NTEMPS*2][128]; /* = { TMP_DIR }; */

static int O2phases[] = {		/* Passes for -O2 */
  CJ, BO, SP, 0
};

static int O3phases[] = {		/* Passes for -O3 */
  CS, SR, CJ, BO, SP, UD, LV, RA, 0
};

static int O4phases[] = {		/* Passes for -O4 */
  IL, CF, CS, SR, CJ, BO, SP, UD, LV, RA, 0
};

static int	*Ophase = &O2phases[0];	/* default : -O2 */

static int	nuphases;		/* # of phases specified by user */
static int	uphases[MAXUPHASES+1];	/* phases to be run */

static int	nfiles = NTEMPS*2+1;	/* leave space for tempfilenames */
static char * phargs[MAXARGS+1];

static int	keeptemps = 0;

static char	**phase_args;
static int	nphase_args;

static char	*opt_dir;
static char	*prog_name;

static int	v_flag;

#ifndef HAVE_FORK
static char cmd[ 256 ];         /* command buffer */
#endif

static
void
cleanup(void)
{
  /*	Cleanup temporaries */

  if (! keeptemps) {
	register int i;

	for (i = NTEMPS*2; i > 0; i--) {
		char	*f = phargs[i];
		if (f != 0 && *f != '\0' && *f != '-') unlink(f);
	}
	if (ddump[0] != '\0') unlink(ddump);
	if (pdump[0] != '\0') unlink(pdump);
  }
}

/*VARARGS1*/
static
void
fatal(char *fmt,...)
{
  /*	A fatal error occurred; exit gracefully */
  va_list va;

  fprintf(stderr, "%s: ", prog_name);
  va_start(va,fmt);
  vfprintf(stderr, fmt, va);
  va_end(va);
  fprintf(stderr, "\n");
  cleanup();
  exit( 1 );
  /*NOTREACHED*/
}

static
void
add_file(char *s)
{
  /*	Add an input file to the list */

  if (nfiles >= MAXARGS) fatal("too many files");
  phargs[nfiles++] = s;
}

static
void
add_uphase(int p)
{
  /*	Add an optimizer phase to the list of phases to run */

  if (nuphases >= MAXUPHASES) fatal("too many phases");
  uphases[nuphases++] = p;
}

static
void
catch(int ignored)
{
  /*	Catch interrupts and exit gracefully */

  cleanup();
  exit( 1 );
}

static
void
old_infiles(void)
{
  /*	Remove old input files unless we have to keep them around. */

  register int i;

  if (phargs[1] == pdump || keeptemps) return;

  for (i = 1; i <= NTEMPS; i++) unlink(phargs[i]);
}

static
void
get_infiles(void)
{
  /*	Make output temps from previous phase input temps of next phase. */

  register int	i;
  register char	**dst = &phargs[1];
  register char	**src = &phargs[NTEMPS+1];

  for (i = 1; i <= NTEMPS; i++) {
	*dst++ = *src++;
  }
}

static
void
new_outfiles(void)
{
  static int	tmpindex = 0;
  static int	Bindex = 0;
  static char	dig1 = '1';
  static char	dig2 = '0';

  int	i;
  char	**dst = &phargs[NTEMPS+1];

  if (! Bindex) {
	Bindex = strrindex(tmpbufs[0], 'B') - tmpbufs[0];
  }
  for (i = 1; i <= NTEMPS; i++) {
	*dst = tmpbufs[tmpindex];
	(*dst)[Bindex-1] = dig2;
	(*dst)[Bindex] = dig1;
	tmpindex++;
	dst++;
  }
  if (tmpindex >= 2*NTEMPS) tmpindex = 0;
  if (++dig1 > '9') {
	++dig2;
	dig1 = '0';
  }
}

static
void
run_phase(int phase)
{
  /*	Run one phase of the global optimizer; special cases are
	IC and CA.
  */
  static int flags_added;
  register int	argc;
  register int	i;
  char	buf[256];
#ifdef HAVE_FORK
  int	pid, status;
#endif

  phargs[0] = buf;
  (void) strcpy(buf, opt_dir);
  (void) strcat(buf, "/");
  (void) strcat(buf, phnames[phase]);

  switch(phase) {
  case IC:
	phargs[1] = pdump;
	phargs[2] = ddump;
	for (i = 3; i <= NTEMPS; i++) phargs[i] = "-";
	new_outfiles();
	argc = nfiles;
  	phargs[argc] = 0;
	break;

  case CA:
	old_infiles();
	get_infiles();
	phargs[NTEMPS+1] = pdump;
	phargs[NTEMPS+2] = ddump;
	for (i = NTEMPS+3; i <= 2*NTEMPS; i++) phargs[i] = "-";
	argc = 2*NTEMPS+1;
  	phargs[argc] = 0;
	break;

  default:
	old_infiles();
	get_infiles();
	new_outfiles();
	if (! flags_added) {
		flags_added = 1;
		argc = 2*NTEMPS+1;
		while (--nphase_args >= 0) {
			phargs[argc++] = *phase_args++;
		}
  		phargs[argc] = 0;
	}
	break;
  }
#ifdef HAVE_FORK
  if ((pid = fork()) < 0) {
	fatal("Could not fork");
  }
  else if (pid == 0) {
	if (v_flag) {
		register int i = 0;

		while (phargs[i]) {
			fprintf(stderr, "%s ", phargs[i]);
			i++;
		}
		fprintf(stderr, "\n");
	}
	(void) execv(phargs[0], (char**)phargs);
	fatal("Could not exec %s", phargs[0]);
	exit( 1 );
  }
  else {
	while (wait(&status) != pid) /* nothing */ ;
	if ((status & 0177) != 0) {
		fatal("%s got a unix signal", phargs[0]);
	}
	if (((status >> 8) & 0377) != 0) {
		cleanup();
		exit( 1 );
	}
  }
#else
  /* Build command string, and execute */
  {
    const char ** arg = phargs;

    cmd[ 0 ] = '\0';
    for( ; *arg ; ++arg )
        strcat( cmd, *arg );
    system( cmd );
  }
#endif
}

int
main(int argc,char *argv[])
{
  register int	i = 0;
  char * tmp;

  tmp = getenv( "TMP" );
  if( 0 == tmp )
    tmp = getenv( "TEMP" );
  if( 0 == tmp )
    tmp = "/tmp";

  strcpy( ddump, tmp );
  strcpy( pdump, tmp );
  strcpy( tmpbufs[ 0 ], tmp );

#ifdef SIGHUP
  if (signal(SIGHUP, catch) == SIG_IGN) (void) signal(SIGHUP, SIG_IGN);
#endif
#ifdef SIGQUIT
  if (signal(SIGQUIT, catch) == SIG_IGN) (void) signal(SIGQUIT, SIG_IGN);
#endif
  if (signal(SIGINT, catch) == SIG_IGN) (void) signal(SIGINT, SIG_IGN);
  prog_name = argv[0];
  phase_args = &argv[1];
  while (--argc > 0) {
	argv++;
	if (argv[0][0] == '-') {
		switch(argv[0][1]) {
		case 'P':
			if (argv[0][2] == '\0') {
				opt_dir = argv[1];
				argc--;
				argv++;
				continue;
			}
			break;
		case 't':
			if (argv[0][2] == '\0') {
				keeptemps = 1;
				/* no continue; IL also needs this */
			}
			break;
		case 'v':
			v_flag = 1;
			break;
		case 'O':
			if (argv[0][2] == '2' || argv[0][2] == '\0') continue;
			if (argv[0][2] == '3') {
				Ophase = &O3phases[0];
				continue;
			}
			Ophase = &O4phases[0];
			continue;
		case 'I':
			if (! strcmp(&argv[0][1], "IL")) {
				add_uphase(IL);
				add_uphase(CF);
				continue;
			}
			break;
		case 'B':
			if (! strcmp(&argv[0][1], "BO")) {
				add_uphase(BO);
				continue;
			}
			break;
		case 'R':
			if (! strcmp(&argv[0][1], "RA")) {
				add_uphase(RA);
				continue;
			}
			break;
		case 'U':
			if (! strcmp(&argv[0][1], "UD")) {
				add_uphase(UD);
				continue;
			}
			break;
		case 'L':
			if (! strcmp(&argv[0][1], "LV")) {
				add_uphase(LV);
				continue;
			}
			break;
		case 'C':
			if (! strcmp(&argv[0][1], "CS")) {
				add_uphase(CS);
				continue;
			}
			if (! strcmp(&argv[0][1], "CJ")) {
				add_uphase(CJ);
				continue;
			}
			break;
		case 'S':
			if (! strcmp(&argv[0][1], "SR")) {
				add_uphase(SR);
				continue;
			}
			if (! strcmp(&argv[0][1], "SP")) {
				add_uphase(SP);
				continue;
			}
			break;
		}
		phase_args[i++] = argv[0];
	}
	else {
		add_file(argv[0]);
	}
  }
  phase_args[i] = 0;
  nphase_args = i;
  if (nuphases) Ophase = uphases;

  if (nfiles == 2*NTEMPS+1) {
	/* 2*NTEMPS+1 was the starting value; nothing to do */
	exit( 0 );
  }

  if (! opt_dir) {
	fatal("no correct -P flag given");
  }

  if (keeptemps) {
	(void) strcpy(ddump, ".");
	(void) strcpy(pdump, ".");
	(void) strcpy(tmpbufs[0], ".");
  }
  (void) strcat(ddump, "/ego.dd.XXXXXX");
  (void) mktemp(ddump);
  (void) strcat(pdump, "/ego.pd.XXXXXX");
  (void) mktemp(pdump);

  (void) strcat(tmpbufs[0], "/ego.A.BB.XXXXXX");
  (void) mktemp(tmpbufs[0]);
  for (i = 2*NTEMPS-1; i >= 1; i--) {
	(void) strcpy(tmpbufs[i], tmpbufs[0]);
  }
  i = strrindex(tmpbufs[0], 'A') - tmpbufs[0];
  tmpbufs[0][i] = 'p'; tmpbufs[NTEMPS+0][i] = 'p';
  tmpbufs[1][i] = 'd'; tmpbufs[NTEMPS+1][i] = 'd';
  tmpbufs[2][i] = 'l'; tmpbufs[NTEMPS+2][i] = 'l';
  tmpbufs[3][i] = 'b'; tmpbufs[NTEMPS+3][i] = 'b';
  run_phase(IC);
  run_phase(CF);
  while (*Ophase) {
	run_phase(*Ophase++);
  }
  run_phase(CA);
  cleanup();
  exit( 0 );
  /*NOTREACHED*/
}
