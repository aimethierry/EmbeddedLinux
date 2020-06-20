#include <stdio.h>
#include "newGame.h"

int main()
{
    printf("call function to play game \n");
    if(startPlayGame() == 0)
    {
        printf("i have to close everything \n");
    }
    return 0;
}