#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"
typedef struct
{
    char nome[max];
    char cor[10];
    char tamanho;
}Camisa;

void Ordena_Nome(Camisa vet[], int n)
{
    int i, j;
    Camisa aux;

    for (i = 1; i <= n-1; i++)
    {
        aux = vet[i];
        j = i-1;
        while (j >= 0 && (strcmp(vet[j].nome, aux.nome) > 0))
        {
            vet[j+1] = vet[j];
            j--;
        }

        vet[j+1] = aux;
    }
}

void Ordena_Tamanho(Camisa vet[], int n)
{
    int i, j;
    Camisa aux;

    for (i=1; i<=n-1; i++)
    {
        aux = vet[i];
        j = i-1;
        while (j >= 0 && (vet[j].tamanho < aux.tamanho))
        {
            vet[j+1] = vet[j];
            j--;
        }

        vet[j+1] = aux;
    }
}

void Ordena_Cor(Camisa vet[], int n)
{
    int i, j;
    Camisa aux;

    for (i=1; i<=n-1; i++)
    {
        aux = vet[i];
        j = i-1;
        while (j >= 0 && (strcmp(vet[j].cor, aux.cor) > 0))
        {
            vet[j+1] = vet[j];
            j--;
        }

        vet[j+1] = aux;
    }
}


int main()
{
    int n, i;
    Camisa vet[60];
    scanf("%d", &n);
    do
    {
        if(n==0)
            break;

        for(i=0; i<n; i++)
        {
            scanf(" %[^\n]s", &vet[i].nome);
            //gets(vet[i].nome);
            scanf(" %s %c", &vet[i].cor, &vet[i].tamanho);
        }

        Ordena_Nome(vet, n);
        Ordena_Tamanho(vet, n);
        Ordena_Cor(vet, n);

        for(i=0; i<n; i++)
            printf("%s %c %s\n", vet[i].cor, vet[i].tamanho, vet[i].nome);

        scanf("%d", &n);
        if(n!=0)
            printf("\n");
    }while(n!=0);
	return 0;
}
