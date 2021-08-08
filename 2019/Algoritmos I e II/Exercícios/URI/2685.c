#include <stdio.h>
#include <stdlib.h>

int main()
{
    int grau;
    while(scanf("%d",&grau)!=EOF)
    {
        if(grau<90||grau==360)
            printf("Bom Dia!!\n");
        else if(grau<180)
            printf("Boa Tarde!!\n");
        else if(grau<270)
            printf("Boa Noite!!\n");
        else if(grau<360)
            printf("De Madrugada!!\n");
    }
    return 0;
}
