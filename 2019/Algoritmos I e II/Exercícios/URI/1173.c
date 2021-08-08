#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n[10],i,vlr_ini,x;
    scanf("%i",&vlr_ini);
    n[0]=vlr_ini;
    x=n[0];
    for(i=0;i<10;i++)
    {
        printf("N[%i] = %i\n",i,x);
        x*=2;
    }

    return 0;
}
