#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte "Windows 1252"

int main()
{
	int c,p,f;
    scanf("%d %d %d", &c, &p, &f);

    int verifica;
    verifica = (c*f);
    if(verifica<=p)
        printf("S\n");
    else
        printf("N\n");

	return 0;
}
