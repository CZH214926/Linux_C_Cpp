#include <stdio.h>
#include "myadd.h"
#include "mysub.h"
int main()
{
    int x = 23;
    int y = 24;
    printf("x - y = %d\n",MySub(x,y));
    printf("x + y = %d\n",MyAdd(x,y));
    return 0;
}


