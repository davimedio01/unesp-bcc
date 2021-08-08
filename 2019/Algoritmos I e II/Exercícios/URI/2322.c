#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 1000

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int n, i, aux;
    int vet[max];

    scanf("%d", &n);
    for(i=1; i<n; i++)
    {
        scanf("%d", &aux);
        vet[aux] = 1;
    }

    for(i=1; i<=n; i++)
    {
        if(vet[i] != 1)
        {
            printf("%d\n", i);
            break;
        }
    }
	return 0;
}
