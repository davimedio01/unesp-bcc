#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte "Windows 1252"
typedef struct{
    int maior;
    int posicao;
}Maior;
int main()
{
	int n;
    scanf("%d",&n);

    int vet[n],i,j;
    int total=0;
    Maior aux1,aux2;

    for(i=0;i<n;i++)
    {
        scanf("%d",&vet[i]);
        total+=vet[i];
        if(i==0)
        {
            aux1.maior = aux2.maior = vet[i];
            aux1.posicao = aux2.posicao = i;
        }
        else if(vet[i] > aux2.maior)
        {
            aux1.maior = aux2.maior;
            aux1.posicao = aux1.posicao;

            aux2.maior = vet[i];
            aux2.posicao = i;
        }
    }

    float teste1 = (aux2.maior*100.0/total);
    float teste2 = (aux1.maior*100.0/total);

    if(teste1>=45.0)
        printf("1\n");
    else if(teste1>=40.0 && (teste1-teste2)>=10.0)
        printf("1\n");
    else
        printf("2\n");

	return 0;
}
