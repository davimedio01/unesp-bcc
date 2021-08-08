#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 1000

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"
void Gnome_Sort(int vetor[], int n)
{
    int pos = 0;
    while (pos < n)
    {
        if (pos == 0)
            pos++;
        if (vetor[pos] >= vetor[pos-1])
            pos++;
        else
        {
            troca(&vetor[pos], &vetor[pos-1]);
            pos--;
        }
    }
    return;
}

void troca(int *x, int *y)
{
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

int main()
{
    int m, n, i;
    int vet[max];
    int soma;
    while(scanf("%d %d", &m, &n) != EOF)
    {
        for(i=0; i<m; i++)
            scanf("%d", &vet[i]);

        Gnome_Sort(vet, m);
        soma = 0;
        for(i=m-1; i>m-n-1; i--)
            soma += vet[i];

        printf("%d\n", soma);

    }
	return 0;
}
