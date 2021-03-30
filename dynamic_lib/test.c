#include <stdio.h>
#include "myadd.h"
#include "mysub.h"


int main()
{
   int x = 12;
   int y = 13;
   printf("x - y = %d\n",mysub(x,y));
   printf("x + y = %d\n",myadd(x,y));
   return 0;
}
