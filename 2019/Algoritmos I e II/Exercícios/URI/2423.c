#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int farinha, ovo, leite;
    scanf("%d %d %d", &farinha, &ovo, &leite);

    int cont = 0;
    while((farinha>=2) && (ovo>=3) && (leite>=5))
    {
        farinha -= 2;
        ovo -= 3;
        leite -= 5;
        cont++;
    }
    printf("%d\n", cont);
	return 0;
}
