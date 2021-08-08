#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 1000

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"
void Ordena_Vetor (int vetor[], int n)
{
	int i, j, aux;
	for (i=1; i<n; i++)
	{
		for (j=0; j<n-i; j++)
		{
			if (vetor[j] > vetor[j+1])
			{
				aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;
			}
		}
	}

}

int Busca_Bin(int esq, int dir, int vet[], int num)
{
    int meio = (esq+dir)/2;
    if(esq>dir)
        return -1;
    if(vet[meio] == num)
        return meio+1;
    if(vet[meio]<num)
        return Busca_Bin(meio+1, dir, vet, num);
    return Busca_Bin(esq, meio-1, vet, num);
}


int main()
{
    int t;
    scanf("%d",&t);
    while(t>0)
    {
        int  k, n, i, j, aux;
        int songs[max];
        scanf("%d", &n);
        for(i=0; i<n; i++)
            scanf("%d", &songs[i]);
        scanf("%d", &k);
        aux = songs[k-1];
        Ordena_Vetor(songs, n);

        printf("%d\n", Busca_Bin(0, n-1, songs, aux));
        t--;
    }

	return 0;
}
