#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x[10],n,i,aux;
    for(i=0;i<10;i++)
    {
        scanf("%i",&x[i]);
        aux=x[i];
        if(aux<=0)
            printf("X[%i] = 1\n",i);
        else
            printf("X[%i] = %i\n",i,aux);
    }
    return 0;
}
