#include <ncurses.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXWIDTH 79
#define MAXHEIGHT 23

// int snakeArray[100][2];
// snakeArray[0][0] = 3;
// snakeArray[0][1] = 3;
// int keyPressed = 0; /* which key user pressed */
// int dirX = 1;       /* direction xy */
// int dirY = 0;
// int speed = 20; /* controls speed of the snake */
// int appleX = 0; /* current apple xy position */
// int appleY = 0;
// int appleEaten = 1;  /* is apple eaten? */


typedef enum
{
  STATE_IDDLE = 1,
  STATE_PLAY = 2,
  STATE_STOP = 3,

} STATE_T;

typedef enum
{
  EVENT_UP = 65,
  EVENT_DOWN = 66,
  EVENT_LEFT = 68,
  EVENT_RIGHT = 67
} EVENT_T;

int kbhit(void)
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

int colliding(int *snakeArray)
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

void moveSnake(int *snakeArray, int dirX, int dirY, int speed, int snakeLength)
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

void letThereBeApple(int *appleX, int *appleY, int *appleEaten)
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

void eatApple(int *snakeArray, int appleX, int appleY,
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

int main()
{

  STATE_T S = STATE_IDDLE;
  EVENT_T E;
  int n = 1;
  char playerName[256];
  char start[2];

  int snakeArray[100][2];

  while(1){
    switch (S)
    {
    case STATE_IDDLE:
      printf("am in the iddle state \n");
      printf("enter your name \n");
      scanf("%s", playerName);
      printf("player name is %s \n", playerName);
      printf("enter s to start the game \n");
      scanf("%s", start);
      int res = strcmp(start, "s");
      if (res == 0)
      {
        S = STATE_PLAY;
      }
      break;

    case STATE_PLAY:
      snakeArray[0][0] = 3;
      snakeArray[0][1] = 3;
      int keyPressed = 0;   /* which key user pressed */
      int dirX = 1;        /* direction xy */
      int dirY = 0;
      int speed = 20;       /* controls speed of the snake */
      int appleX = 0;       /* current apple xy position */
      int appleY = 0;
      int appleEaten = 1;   /* is apple eaten? */
      int snakeLength = 3;  /* player snakeLength */

      initscr();			/* Start curses mode */
      curs_set(false);
      noecho();

      while (!colliding(&snakeArray[0][0])) {
        erase();
        letThereBeApple(&appleX, &appleY, &appleEaten);
        moveSnake(&snakeArray[0][0], dirX, dirY, speed, snakeLength);
        eatApple(&snakeArray[0][0], appleX, appleY, &appleEaten, &snakeLength);
        refresh();
        // change direction with wasd 
        if (kbhit()) {
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
      mvprintw(MAXHEIGHT/2,MAXWIDTH/4,"Game Over! - Your score was: %d", snakeLength);
      refresh();
      getch();			// Wait for user input 
      endwin();			// End curses mode
      S = STATE_STOP;
      break;

    case STATE_STOP:
      printf(" \n \n enter s to start the game again \n");
      printf("enter r for another player \n");
      scanf("%s", start);
      int resr = strcmp(start, "s");
      int res2 = strcmp(start, "r");
      if (resr == 0)
      {
        S = STATE_PLAY;
      }

      if (res2 == 0)
      {
        S = STATE_IDDLE;
      }
      break;

    default:
      break;
    }
  }
  return 0;
}