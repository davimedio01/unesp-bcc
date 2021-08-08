#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 4

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int n, i, num, aux=0, cont=0;
    int vet[max];

    for(i=0; i<max; i++)
        vet[i] = 0;

    while(scanf("%d", &n) != EOF)
    {
        aux = 0;
        cont = 0;
        for(i=0; i<n; i++)
        {
            scanf("%d", &num);
            if(!Busca_Seq(vet, max, &num))
            {
                vet[aux++] = num;
                cont++;
            }
            if(aux==4)
                aux=0;
        }

        printf("%d\n", cont);
    }

	return 0;
}

int Busca_Seq(int vet[], int n, int *valor)
{
    int i;
    for(i=0; i<n; i++)
        if(vet[i] == *valor)
            return 1;                                                     ;
    return 0;
}
