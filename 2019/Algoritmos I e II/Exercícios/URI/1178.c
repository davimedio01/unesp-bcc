#include <stdio.h>
#include <stdlib.h>

int main()
{
    float n,x[100];
    int i;
    scanf("%f",&n);
    x[0]=n;
    for(i=1;i<=99;i++)
        x[i]=x[i-1]/2.0000;
    for(i=0;i<=99;i++)
        printf("N[%i] = %.4f\n",i,x[i]);

    return 0;
}
