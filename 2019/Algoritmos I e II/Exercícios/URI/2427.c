#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int l;
    int soma = 1;
    scanf("%d", &l);

    while(l != 1)
    {
        soma *= 4;
        l /= 2;
    }
    printf("%d\n", soma);
    
	return 0;
}
