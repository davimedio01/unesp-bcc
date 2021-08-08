#include <stdio.h>
#include <stdlib.h>

int main()
{
    float n,soma=0,media;
    int i,positivo=0;
    for(i=1;i<=6;i++)
    {
        scanf("%f", &n);
        if(n>=0)
        {
            positivo++;
            soma+=n;
        }
    }
    media=soma/positivo;
    printf ("%i valores positivos\n",positivo);
    printf("%.1f\n", media);

    return 0;
}
