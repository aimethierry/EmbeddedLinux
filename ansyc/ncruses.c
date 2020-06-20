#include <stdint.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

static uint64_t
GetMilli (void)
{
	struct timespec  ts;
	uint64_t		milli;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	milli = (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
	return (milli);
}

static void
DrawBox(void)
{
	// this is only to demonstrate the characters to build a box
	// this code should be modified to draw a box of arbitrary size
	mvaddch (2, 32, ACS_ULCORNER);
	addch (ACS_HLINE);
	addch (ACS_HLINE);
	addch (ACS_HLINE);
	addch (ACS_HLINE);
	addch (ACS_HLINE);
	addch (ACS_URCORNER);
	mvaddch (3, 32, ACS_VLINE);
	mvaddch (3, 38, ACS_VLINE);
	mvaddch (4, 32, ACS_VLINE);
	mvaddch (4, 38, ACS_VLINE);
	mvaddch (5, 32, ACS_VLINE);
	mvaddch (5, 38, ACS_VLINE);
	mvaddch (6, 32, ACS_LLCORNER);
	addch (ACS_HLINE);
	addch (ACS_HLINE);
	addch (ACS_HLINE);
	addch (ACS_HLINE);
	addch (ACS_HLINE);
	addch (ACS_LRCORNER);
}
		
static void
GetSetTime(void)
{
    time_t		myRawTime;
    time_t		myRawTime2;
    struct tm	myTime;
    struct tm	myTime2;
    int			result = 73;

	// get current system time:
	time(&myRawTime);
	gmtime_r(&myRawTime, &myTime);
	mvprintw(10,5,"%d-%d-%d %02d:%02d:%02d",
		myTime.tm_year+1900,
		myTime.tm_mon+1,
		myTime.tm_mday,
		myTime.tm_hour,
		myTime.tm_min,
		myTime.tm_sec);
	
	// modify the system time:
	/*
	myTime.tm_year++;
	myTime.tm_hour += 2;
	myRawTime = mktime(&myTime);	
	result = stime(&myRawTime);
	*/
	
	// check new system time:
	time(&myRawTime2);
	gmtime_r(&myRawTime2, &myTime2);
	mvprintw(11,5,"%d-%d-%d %02d:%02d:%02d [status:%d]",
		myTime2.tm_year+1900,
		myTime2.tm_mon+1,
		myTime2.tm_mday,
		myTime2.tm_hour,
		myTime2.tm_min,
		myTime2.tm_sec,
		result);
}

int 
main(void)
{
    int     ch;
    unsigned int     i = 0;
    char    x[] = "|/-\\";

    initscr();              /* Start curses mode        */
    raw();                  /* Line buffering disabled  */
    nodelay(stdscr, TRUE);  /* getch() returns immediately      */
    noecho();               /* no cursor */
    curs_set(0);			/* no cursor */

	DrawBox();
	GetSetTime();
    mvprintw(3,5,"press a key ('q' to quit)");
    
    ch = getch();           /* If raw() hadn't been called
                             * we have to press 'enter' before it
                             * gets to the program      
                             */
	
    while (ch != 'q')
    {
		usleep(90000);	// wait a while
        ch = getch();
        if (ch == ERR)
        {
            // no key pressed: show that the while-loop is busy
            i++;
            if (i > strlen (x))
            {
                i = 0;
            }
            mvprintw(7,11,"%c %12lld", x[i], GetMilli());
        }
        else
        {
            // show pressed key
            mvprintw(5,13,"%c (%02x)     ", ch, ch);
        }
    }
    
    endwin();           /* End curses mode        */

    return (0);
}
