#include <stdio.h>
#include "newGame.h"

#include <ncurses.h>
#include <sys/select.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#define MAXWIDTH 79
#define MAXHEIGHT 23
int snakeArray[100][2];
siginfo_t t;
/* client in shm */
void *ptr;

typedef enum
{
  STATE_IDDLE = 1,
  STATE_PLAY = 2,
  STATE_STOP = 3,
  STATE_SAVE_QUIT = 4
} STATE_T;

typedef enum
{
  EVENT_UP = 65,
  EVENT_DOWN = 66,
  EVENT_LEFT = 68,
  EVENT_RIGHT = 67
} EVENT_T;

int readFile(char *name, int SIZE)
{
  int shm_fd = -1;
  void *ptr;
  shm_fd = shm_open(name, O_RDWR, 0600);
  ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  char *res = (char *)ptr;
  printf("%c \n", res[0]);

  if (res[0] == 'A')
  {
    return 0;
  }
  return -1;
}

static void my_sig_handler2(int signum, siginfo_t *info)
{
  t = *(info);
  // printf ("\n Signal %d received : %d\n", signum, info->si_value.sival_int);
}

int kbhit2(void)
{
  /* checks if key has been hit or not */
  struct timeval tv;
  fd_set read_fd;

  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&read_fd);
  FD_SET(0, &read_fd);

  if (select(1, &read_fd, NULL, NULL, &tv) == -1)
    return 0;

  if (FD_ISSET(0, &read_fd))
    return 1;

  return 0;
}

int colliding2(int *snakeArray)
{
  /* checks if snake is colliding with walls */
  int x = *snakeArray;
  int y = *(snakeArray + 1);
  if (x < 0 || x > MAXWIDTH)
  {
    return 1;
  }
  else if (y < 0 || y > MAXHEIGHT)
  {
    return 1;
  }
  return 0;
}

void moveSnake2(int *snakeArray, int dirX, int dirY, int speed, int snakeLength)
{
  /* moves snake one position to the direction provided also controls the speed
     of the game using usleep function */
  int oldX = 0;
  int oldY = 0;
  int curX = *snakeArray;
  int curY = *(snakeArray + 1);
  int newX = curX + dirX;
  int newY = curY + dirY;

  *(snakeArray) = newX;
  *(snakeArray + 1) = newY;
  mvprintw(newY, newX, "T");

  for (size_t i = 2; i < snakeLength * 2; i += 2)
  {
    oldX = curX;
    oldY = curY;
    curX = *(snakeArray + i);
    curY = *(snakeArray + i + 1);
    newX = oldX;
    newY = oldY;
    *(snakeArray + i) = newX;
    *(snakeArray + i + 1) = newY;
    mvprintw(newY, newX, "S");
  }

  if (dirY != 0)
  {
    usleep(1000000 / speed);
  }

  usleep(1000000 / speed);
}

void letThereBeApple2(int *appleX, int *appleY, int *appleEaten)
{
  /* new random apple location if apple is eaten, if not then prints apple at
     previous location */
  if (*appleEaten)
  {
    srand(time(0)); //use current time as seed for random generator
    *appleX = (rand() % MAXWIDTH) + 1;
    *appleY = (rand() % MAXHEIGHT) + 1;
    *appleEaten = 0;
  }

  mvprintw(*appleY, *appleX, "*");
}

void eatApple2(int *snakeArray, int appleX, int appleY,
              int *appleEaten, int *snakeLength)
{
  /* if snake find apple get one point, also sets appleEaten to true and
  prints snakeLength and debug info */
  int x = *snakeArray;
  int y = *(snakeArray + 1);
  if (x == appleX && y == appleY)
  {
    *appleEaten = 1;
    *snakeLength += 1;
    int snakeLen = *snakeLength;
    int lastX = *(snakeArray + snakeLen * 2 - 2);
    int lastY = *(snakeArray + snakeLen * 2 - 2 + 1);
    *(snakeArray + snakeLen * 2) = lastX;
    *(snakeArray + snakeLen * 2 + 1) = lastY;
  }

  mvprintw(0, 0, "snakeLength: %d", *snakeLength);
}

int GamePlay2(STATE_T S)
{
  EVENT_T E;
  snakeArray[0][0] = 3;
  snakeArray[0][1] = 3;
  int keyPressed = 0; /* which key user pressed */
  int dirX = 1;       /* direction xy */
  int dirY = 0;
  int speed = 20; /* controls speed of the snake */
  int appleX = 0; /* current apple xy position */
  int appleY = 0;
  int appleEaten = 1;  /* is apple eaten? */
  int snakeLength = 3; /* player snakeLength */
  initscr();           /* Start curses mode */
  curs_set(false);
  noecho();

  while (!colliding2(&snakeArray[0][0]))
  {
    signal(SIGINT, my_sig_handler2);
    erase();
    letThereBeApple2(&appleX, &appleY, &appleEaten);
    moveSnake2(&snakeArray[0][0], dirX, dirY, speed, snakeLength);
    eatApple2(&snakeArray[0][0], appleX, appleY, &appleEaten, &snakeLength);
    refresh();
    // change direction with wasd
    if (kbhit2())
    {
      // keyPressed = getch();
      E = getch();
      switch (E)
      {
      case EVENT_UP:
        dirY = -1;
        dirX = 0;
        break;

      case EVENT_DOWN:
        dirY = 1;
        dirX = 0;
        break;

      case EVENT_LEFT:
        dirX = -1;
        dirY = 0;
        break;

      case EVENT_RIGHT:
        dirX = 1;
        dirY = 0;
        break;

      default:
        break;
      }
    }
  }
  erase();
  mvprintw(MAXHEIGHT / 2, MAXWIDTH / 4, "Game Over! - Your score was: %d", snakeLength);
  refresh();
  getch();  // Wait for user input
  endwin(); // End curses mode
  return 0;
}

int EndMenu2()
{
  char start[2];
  
  printf(" \n enter r for another player \n");
  printf(" \n Enter q to save and quit \n");
  scanf("%s", start);
  int resr = strcmp(start, "s");
  int res2 = strcmp(start, "r");
  int resq = strcmp(start, "q");

  if (resr == 0)
  {
    return 0;
  }

  if (res2 == 0)
  {
    return 1;
  }

  if (resq == 0)
  {
    return 2;
  }
  return -1;
}


int  startPlayGame()
{
  printf("start after having the permission \n");
  STATE_T S = STATE_IDDLE;
  int n = 1;
  int pidValue;

  char playerName[256];
  union sigval sig_val; // Extra value to be sent with signal
  /* the size (in bytes) of shared memory object */
  int SIZE = 4096;
  /* name of the shared memory object */
  char *name = "OS";
  /* remove the shared memory object */
  if (readFile(name, SIZE) == 0)
  {
    while (1)
    {
      switch (S)
      {
      case STATE_IDDLE:
          S = STATE_PLAY;
        break;

      case STATE_PLAY:
        if (GamePlay2(S) == 0)
        {
          S = STATE_STOP;
        }
        break;

      case STATE_STOP:

        if (EndMenu2() == 0)
        {
          S = STATE_PLAY;
        }

        if (EndMenu2() == 2)
        {
          S = STATE_SAVE_QUIT;
        }
        break;

      case STATE_SAVE_QUIT:
        printf("Enter signal value: ");
        scanf("%d", &sig_val.sival_int);
        shm_unlink(name);
        return 0;
        break;

      default:
        break;
      }
    }
  }

  return -1;
}