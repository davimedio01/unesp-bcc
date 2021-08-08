#include <stdio.h>
#include <stdlib.h>

int main()
{
    float n1,n2,media,opcao,h=1,aux1=1,aux2=1;

    for(h=1;;h=1,aux1=1,aux2=1)
    {
        scanf("%f",&n1);
        if(n1<0 || n1>10)
        {
            printf("nota invalida\n");
            continue;
        }
        while(aux1==1)
        {
            scanf("%f",&n2);
            if(n2<0 || n2>10)
            {
                printf("nota invalida\n");
                continue;
            }
            aux1+=2;
        }
        media=(n1+n2)/2.0;
        printf("media = %.2f\n",media);
        printf("novo calculo (1-sim 2-nao)\n");
        while(aux2==1)
        {
            scanf("%f", &opcao);
            if(opcao<1 || opcao>2)
            {
                printf("novo calculo (1-sim 2-nao)\n");
                continue;
            }
            aux2+=2;
        }
        if(opcao==2)
            break;
    }

    return 0;
}
