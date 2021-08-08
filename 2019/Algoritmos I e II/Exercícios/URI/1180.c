#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,x[1000],i,aux1,aux2;
    scanf("%i",&n);
    scanf("%i",&x[0]);
    aux1=x[0];
    aux2=0;
    for(i=1;i<n;i++)
    {
        scanf("%i",&x[i]);
        if(x[i]<aux1)
        {
            aux1 = x[i];
            aux2 = i;
        }

    }
    printf("Menor valor: %i\n",aux1);
    printf("Posicao: %i\n",aux2);
    return 0;
}
