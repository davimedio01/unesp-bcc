#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
	system("COLOR 09");
	setlocale(LC_ALL,"Portuguese");

    int n;
    scanf("%d",&n);
    while(n>0)
    {
        int A, B, auxA, auxB;
        long int resto;
        scanf("%d %d", &A, &B);
        auxA = A;
        auxB = B;
        while(auxA % auxB != 0)
        {
            resto = auxA % auxB;
            auxA = auxB;
            auxB = resto;
        }
        A /= auxB;
        B /= auxB;

        printf("%d %d\n", B, A);

        n--;
    }

	return 0;
}
