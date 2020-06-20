#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <time.h>











static pid_t  	pid;								// Process ID of current process
static bool     to_quit = false;		// Indicate quit
static char			blocked_sigs[32];		// Array of blocked signals

static volatile sig_atomic_t done_waiting = 0;
siginfo_t  t;

static void my_sig_handler (int signum, siginfo_t *info)
{
  t = *(info);
	printf ("\n(%d) Signal %d received : %d\n", pid, signum, info->si_value.sival_int);
}

static void install_sigaction (int signo)
{
    struct sigaction 	new_action;
    struct sigaction	old_action;

    printf ("(%d) Install signal handler for signal %d\n", pid, signo);

    sigemptyset (&new_action.sa_mask);
    new_action.sa_handler = my_sig_handler;
    new_action.sa_flags   = SA_SIGINFO;

    if (sigaction (signo, &new_action, NULL) == -1)
    {
        perror ("sigaction(set-my-sig)");
    }
}

// static void add_to_blocked_signals(int sig)
// {
// 	int i;
// 	for ( i = 0; i < 32; i++){
// 		if (blocked_sigs[i] == 0){
// 			blocked_sigs[i] = sig;
// 			break;}}
// }
// static void remove_from_blocked_signals(int sig)
// {
// 	// remove sig from array
// 	int i;
// 	for (i = 0; i < 32; i++){
// 		if (blocked_sigs[i] == sig){
// 			blocked_sigs[i] = 0;}
// 		else{
// 			break;}}
// 	// tidy up the array (make sure all indexes are filled, no empty indexes between values)
// 	int j;
// 	for (j = 0; j< 32; j++){
// 		if (blocked_sigs[j] == 0 && blocked_sigs[j+1] != 0){
// 			blocked_sigs[j] = blocked_sigs[j+1];
// 			blocked_sigs[j+1] = 0;
// 		}}
// }

static void get_blocked_signals()
{
	// print all blocked signals
	if (blocked_sigs[0] != 0){
		int i;
		for (i = 0; i < 32; i++){
			if (blocked_sigs[i] != 0)
				printf("%d ", blocked_sigs[i]);
			}
	}
	else{
		printf(" there are no signals blocked.");
	}
}


void Help()
{
                printf ("Options:\n"
                "=================================\n"
                "    i  :   install new signal\n"
                "    k  :   send signal with kill\n"
                "    q  :   signal queue\n"
                "    b  :   block a signal\n"
       					"		 u  :   unblock a signal\n"
                "    n  :   signal pending\n"
                "    p  :   wait for signal\n"
								"    t  :   start a timer to send signal\n"
								"    s  :   stop timer\n"
                "    l  :   list all blocked signals\n"
                "    H  :   help\n"
                "    Q  :   quit\n");
}



static void  handler()
{
  printf("Signal caught\n");
  done_waiting = 1;
}

void my_pause()
{
  signal(SIGINT, handler);
  done_waiting = 0;
  while (!done_waiting)
    ;
}


void SetTImerCreate(int sig)
{
    timer_t		timer;
    struct sigevent 	sevp;
    struct itimerspec ts;

    // set timer configurations
    ts.it_value.tv_sec = 2;
	ts.it_value.tv_nsec = 0;

    sevp.sigev_notify = SIGEV_SIGNAL;
	sevp.sigev_signo = sig;
	sevp.sigev_value.sival_ptr= &timer;

	if (timer_create(CLOCK_REALTIME, &sevp, &timer) != 0)
		perror("timer_create()");
				
	if (timer_settime(timer, 0, &ts, NULL) != 0)
					perror("timer_settime()");
}

int main(int argc, char * argv[])
{
  int     		    	sig;					// Signal numbeer
  pid_t    					target_pid;		// PID of target
  char     					choice = 0;		// User input
  
  sigset_t 					sig_set;			// Set of blocked signals
  sigset_t 					temp_set;			// Set buffer for to be blocked signals
  
  union sigval 	    sig_val;			// Extra value to be sent with signal
  timer_t		timer;
  

   pid_t   processID;      /* Process ID from fork() */

  // get process ID
  pid = getpid();

  processID = fork();

  if(processID == 0)
  {
    //  raise(SIGSTOP);
    //  while(1)
    //  {
    //     printf("am child \n");
    //     sleep(2);
    //  }
      
  }
  else
  {
  while(to_quit == false)
  {
    printf ("\n\nChoices: i, k, q, b, u, n, p, t, s, l, Q, H, a");
    printf ("\n in A Please enter your choice: ");
    scanf("%s", &choice);

    switch(choice)
    {
      case 'i':
        // SIGNAL ACTION
        printf("Enter signal number: ");
        scanf("%d", &sig);
		printf("\n");
        install_sigaction(sig);
        printf("(%d) Signal handler %d is created", pid, sig);
        printf("\n \n");
        break;

      case 'a':
        printf("signal code %d \n ", t.si_code);
        printf("signal error %d \n ", t.si_errno);
        break;
    
      case 'k':
        printf("\n kill the child in fork \n \n ");
        printf("Enter signal number: ");
        
        scanf("%d", &sig);
        if (kill(0, sig) != 0){
			perror ("kill()");
		}
		printf("(%d) Signal %d sent to process %d\n", pid, sig, target_pid);		
        break;

      case 'q':
        // SIGNAL QUEUE
        printf("Enter signal number: ");
        scanf("%d", &sig);

        printf("Enter Process ID: ");
        scanf("%d", &target_pid);

        printf("Enter signal value: ");
        scanf("%d", &sig_val.sival_int);

        if (sigqueue(target_pid, sig, sig_val) != 0)
			    perror("sigqueue()");
				
		    printf("(%d) Signal %d sent to process %d \n", pid, sig, target_pid);
        break;


      case 'b':
        break;


      case 'u':
        break;


      case 'n':
        // EXAMINE PENDING SIGNALS
		printf("Enter signal number to check: ");
		scanf("%d", &sig);

		// Get all pending signals and store them in a buffer
        sigset_t waiting;
        sigemptyset (&waiting);
        if(sigpending(&waiting) != 0){
          perror("sigpending()");
        }
		else{
			if (sigismember (&waiting, sig)){
			printf("(%d) Signal %d is pending", pid, sig);
			}
			printf("(%d) No signal %d detected", pid, sig);		
		}
        break;


      case 'p':
        // PAUSE SIGNAL
		printf("Enter ctr c to continue ");
		my_pause();
        printf("Enter ctr c to close");
        my_pause();
        break;
	
       case 't':
				// PERIODICALLY SEND A SIGNAL TO SELF
				printf("Enter signal number: ");
				scanf("%d", &sig);

				

				// install signal handler for timer signal
				install_sigaction(sig);
				// set signal event for timer
				
				SetTImerCreate(sig);

				printf("(%d) Timer with ID %d set.", pid, timer);
				
				break;
	   case 's':
				// set timer configurations to stop
				
				break;
	   case 'l':
				// LIST ALL BLOCKED SIGNALS
				break;
      case 'Q':
        // QUIT
			to_quit = true;
        break;
      case 'H':
			Help();
        break;
    }
   }
  }
}



