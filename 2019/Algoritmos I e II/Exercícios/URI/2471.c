#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100
#define ordem 50

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    long int vet[ordem][ordem], soma1=0, soma2=0, soma_final;
    int n, i, j, aux_errado, aux1=0, aux2=0;
    scanf("%d", &n);

    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            scanf("%ld", &vet[i][j]);

    //Somando a primeira linha para comparar com as outras
    for(j=0; j<n; j++)
        soma1 += vet[0][j];

    //Comparando as linhas
    for(i=1; i<n; i++)
    {
        soma2 = 0;
        for(j=0; j<n; j++)
            soma2 += vet[i][j];

        if(soma1!=soma2)
        {
            aux1 = i;
            break;
        }
    }

    //Comparando as colunas
    for(i=0; i<n; i++)
    {
        soma2 = 0;
        for(j=0; j<n; j++)
            soma2 += vet[j][i];

        if(soma1!=soma2)
        {
            aux2 = i;
            break;
        }
    }

    //Como soma2 traz a soma errada
    soma_final = soma1 - soma2;
    aux_errado = vet[aux1][aux2];
    vet[aux1][aux2] += (soma_final);

    printf("%d %d\n", vet[aux1][aux2], aux_errado);

	return 0;
}
