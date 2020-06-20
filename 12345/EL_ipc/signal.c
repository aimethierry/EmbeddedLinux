#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

static char * 	progname;
static bool		to_quit = false;
static int		delaySeconds = 3;

static void my_sig_handler (int signum)
{
	printf ("\n%s: signal %d received\n", progname, signum);
}

static void install_sigaction (int signo)
{
    struct sigaction 	new_action;
    struct sigaction	old_action;
    printf ("install signal handler for signal %d\n", signo);
    sigemptyset (&new_action.sa_mask);
    new_action.sa_handler = my_sig_handler;
    new_action.sa_flags   = SA_RESTART;
    if (sigaction (signo, &new_action, NULL) == -1)
    {
        perror ("sigaction(set-my-sig)");
    }
}


int main(int argc, char * argv[])
{
    int     sig;
    int     target_pid;
	int		i = 0;
    progname = argv[0];

	if (strcmp (argv[1], "-r") == 0)
	{
		sig = atoi (argv[2]);
		install_sigaction (sig);
	}
	if (strcmp (argv[1], "-s") == 0)
	{
		sig = atoi (argv[2]);
		target_pid = atoi (argv[3]);
		printf ("calling kill(%d,%d)\n", target_pid, sig);
		if (kill (target_pid, sig) != 0)
		{
			perror ("kill()");
		}
		to_quit = true;
	}
	
    while (to_quit == false)
    {
		sleep (delaySeconds);
		printf ("%s:iteration %d\n", progname, i);
		i++;
    }
    printf ("%s:ending in a proper way\n\n", progname);
    return (0);
}

