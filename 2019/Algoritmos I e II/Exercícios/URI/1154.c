#include <stdio.h>
#include <stdlib.h>

int main()
{
    int idade,soma=0;
    float media,aux=0;

    while(1)
    {
        scanf("%i",&idade);
        if(idade<0)
            break;
        else
        {
           aux++;
           soma+=idade;
        }
    }
    media=(float)soma/aux;
    printf("%.2f\n",media);
    return 0;
}
