#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n[1000],t,x,i=0,j;
    scanf("%i",&t);
    while(1)
    {
        for(j=0;j<t;j++)
        {
            printf("N[%i] = %i\n",i,j);
            i++;
            if(i>=1000)
            break;
        }
        if(i>=1000)
            break;
    }

    return 0;
}
