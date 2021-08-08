#include <stdio.h>
#include <stdlib.h>

int main()
{
    float n,soma,media=0, notas=0;
    while (1)
    {
        if(notas==2)
            break;
        scanf("%f",&n);
        if(n>=0&&n<=10)
        {
            notas++;
            soma+=n;
        }
        else
            printf("nota invalida\n");
    }
    media=(soma/2.00);
    printf("media = %.2f\n",media);

    return 0;
}
