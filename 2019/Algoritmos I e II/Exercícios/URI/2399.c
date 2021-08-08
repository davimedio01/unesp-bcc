#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 50

//Utilizar o Atom para compilar com a fonte "Windows 1252"

int main()
{
	int n,i;
    scanf("%d",&n);

    int vet[max];
    for(i=0;i<n;i++)
        scanf("%d",&vet[i]);

    for(i=0;i<n;i++)
    {
        if(i==0)
            printf("%d\n", vet[i]+vet[i+1]);
        else if(i==n-1)
            printf("%d\n", vet[i-1]+vet[i]);
        else
            printf("%d\n", vet[i-1]+vet[i]+vet[i+1]);
    }

	return 0;
}
