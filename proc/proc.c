#include"proc.h"

void proc()
{
  char bar[NUM];
  memset(bar,'\0',sizeof(bar));
  const char* lab = "|/-\\";
  int i = 0;
  while(i < 100)
  {
    fflush(stdout);
    bar[i++]='#';
    usleep(100000);
    printf("[%-100s][%3d%%][%c]\r",bar,i,lab[i%4]);
  }
  printf("\n");
}
