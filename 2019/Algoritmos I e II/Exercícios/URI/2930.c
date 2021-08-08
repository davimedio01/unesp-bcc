#include <stdio.h>
#include <stdlib.h>

int main()
{
    int e,d,aux1,aux2;
    scanf("%d %d",&e,&d);
    aux1=d-e;

    if(aux1>=3)
        printf("Muito bem! Apresenta antes do Natal!\n");
    else if(aux1>0)
    {
        printf("Parece o trabalho do meu filho!\n");
        if((d+2)<=24)
            printf("TCC Apresentado!\n");
        else
            printf("Fail! Entao eh nataaaaal!\n");
    }
    else
        printf("Eu odeio a professora!\n");
    return 0;
}
