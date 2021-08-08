#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,par=0,impar=0,positivo=0,negativo=0;
    for(i=1;i<=5;i++)
    {
        scanf("%i",&n);
        if(n%2==0)
            par++;
        else
            impar++;
        if(n>0)
            positivo++;
        else if(n<0)
            negativo++;
    }
    printf("%i valor(es) par(es)\n",par);
    printf("%i valor(es) impar(es)\n",impar);
    printf("%i valor(es) positivo(s)\n",positivo);
    printf("%i valor(es) negativo(s)\n",negativo);

    return 0;
}
