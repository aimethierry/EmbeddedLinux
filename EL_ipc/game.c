#include <ncurses.h>                    /* ncurses.h includes stdio.h */
#include <string.h>

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
    addch (ACS_HLINE);
	addch (ACS_HLINE);
	addch (ACS_HLINE);
	addch (ACS_HLINE);
	addch (ACS_HLINE);
	addch (ACS_URCORNER);
	mvaddch (3, 50, ACS_VLINE);
	mvaddch (3, 38, ACS_VLINE);
	
	mvaddch (4, 38, ACS_VLINE);
	mvaddch (5, 32, ACS_VLINE);
	mvaddch (5, 38, ACS_VLINE);
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



static void Player()
{
    printw("&");
    // printw(" \n*\n*\n*");
}

static void SimpleBoolet()
{
    printw("**");
}

static void MediumBoolet()
{
    printw("****");
}


int main()
{
        initscr();   

        // WINDOW * win = newwin(15, 50 , 15, 50);
        // box(win, 0, 0);
        // refresh();
        // wrefresh(win);
        // wgetch(win);

        char ch;  
        int row,col;                            /* to store the number of rows and *
                                                 * the number of colums of the screen */
        initscr();                              /* start the curses mode */
        getmaxyx(stdscr,row,col);               /* get the number of rows and columns */
        keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
        printw("press t to see any change \n \n \n");
        noecho();
        ch = getch();
        
        int a = 10;
        int b = 30;
        int c ;
        int i = 0;

        // mvprintw(a,b,"%d-%d-%d %02d:%02d:%02d [status:%d]");

        if (ch == (char)'a')
        {

            while(i == 0)
            {
                c = getch();
                if(c == 261) //move right
                {  
                   
                    b++;
                    mvinch(a,b);
                    Player();
                }

                if(c == 260) //move to the left
                {
                     
                    b--;
                    mvinch(a,b);
                    Player();
                }

                if(c == 258) //down
                {
                    a++;
                    mvinch(a,b);
                    Player();
                }

                if(c == 259) //up
                {
                    a--;
                    mvinch(a,b);
                    Player();
                }
                
            }
            refresh();
            getch();
        }
        endwin();                                                                               
        return 0;
}