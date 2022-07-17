#define _SYSTEM	1
#define _MINIX	1

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <minix/config.h>
#include <minix/type.h>
#include <minix/const.h>
#include <minix/com.h>
#include <minix/syslib.h>
#include <timers.h>
#include <../src/kernel/const.h>
#include <../src/kernel/type.h>
#include <../src/kernel/proc.h>
#include <assert.h>

int get_data_end (void)
{
/* sys_getproc doesn't seem to be allowed	
	struct proc my_proc;
	int s;
	s = sys_getproc (&my_proc, SELF);

	printf ("get_data_end: %d %X %X %X\n", s,
		my_proc.p_memmap[D].mem_vir,
		my_proc.p_memmap[D].mem_len,
		my_proc.p_memmap[D].mem_vir + my_proc.p_memmap[D].mem_len
	);
*/
	return (int) sbrk (0);
}

void croak (const char *msg)
{
	fprintf (stderr, "croak: %s\n", msg);
	exit (1);
}

int lstat (const char *fn, struct stat *buf)
{
	return stat (fn, buf);
}

int vfork (void)
{
	return fork ();
}

int sigblock (int s)
{
	sigset_t old;
/* A cast on s would suffice, but this will also work if 
 * sigset_t (long) is larger than int.
 */
	sigset_t s_tmp = s;
	sigprocmask (SIG_BLOCK, &s_tmp, &old);
	return old;
}

int sigsetmask (int s)
{
	sigset_t old;
/* A cast on s would suffice, but this will also work if 
 * sigset_t (long) is larger than int.
 */
	sigset_t s_tmp = s;
	sigprocmask (SIG_SETMASK, &s_tmp, &old);
	return old;
}

pid_t wait3 (int *status, int options, void *rusage)
{
	if (rusage)
	{
		croak ("rusage not implemented for wait3");
	}

	return waitpid (-1, status, options);
}
/*
pid_t tcgetpgrp (int fd)
{
	croak ("tcgetpgrp not implemented");
}

int tcsetpgrp (int fd, pid_t pgrp)
{
	croak ("tcsetpgrp not implemented");
}
*/
int setpgrp(void)
{
	setpgid (0,0);
}

int setpgid (pid_t pid, pid_t pgid)
{
/*	croak ("setpgid not implemented");*/
}

void request_sigio (void)
{
}

void unrequest_sigio (void)
{
}
