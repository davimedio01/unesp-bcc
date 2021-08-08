#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 1000005

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int cont=0, i, n, aux;
    char vet[max]; //char por conta do tamanho
    memset(vet, 0, max); //inicia o "vetor de char" com 0 (evitar o for)

    scanf("%d", &n);
    for(i=0; i<n; i++)
    {
        scanf("%d", &aux);
        if(vet[aux] == 0)
        {
            cont++;
            vet[aux] = 1;
        }
    }
    printf("%d\n", cont);

	return 0;
}
