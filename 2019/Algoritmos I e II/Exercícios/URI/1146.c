#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,i;
    while(1)
    {
        scanf("%i",&x);
        if(x==0)
            break;
        for(i=1;i<x;i++)
            printf("%i ",i);
        printf("%i\n",x);
    }
    return 0;
}
