/* localtime example */
#include <stdio.h>
#include <time.h>
#include <string.h>

int main ()
{
  time_t current_time;
  struct tm * time_info;
  char timeString[9];  // space for "HH:MM:SS\0"

  time(&current_time);
  time_info = localtime(&current_time);

  strftime(timeString, sizeof(timeString), "%H:%M", time_info);
  puts(timeString);
  int res = strcmp(timeString, "12:00");
  if(res == 0)
  {
    printf("time is  time to open %s \n", timeString);
    return 0;
  }
  return -1;
}