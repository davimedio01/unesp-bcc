#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n[20],i,j=0,aux1;
    for(i=0;i<20;i++)
    {
        scanf("%i",&n[i]);
    }
    for(i=19;i>=0;i--)
    {
        aux1=n[i];
        printf("N[%i] = %i\n",j,aux1);
        j++;
    }

    return 0;
}
