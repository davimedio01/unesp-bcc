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

    char matring[4][max];
    int i, j, k;
    for(i=0;i<4;i++)
        scanf("%s",&matring[i]);

    int F = 0, L = 0;
    k = strlen(matring[0])-1;
    F += (matring[0][0]-'0')*1000;
    F += (matring[1][0]-'0')*100;
    F += (matring[2][0]-'0')*10;
    F += (matring[3][0]-'0');
    L += (matring[0][k]-'0')*1000;
    L += (matring[1][k]-'0')*100;
    L += (matring[2][k]-'0')*10;
    L += (matring[3][k]-'0');

    int c, resul;
    for(i=1;i<k;i++)
    {
        c = 0;

        c += (matring[0][i]-'0')*1000;
        c += (matring[1][i]-'0')*100;
        c += (matring[2][i]-'0')*10;
        c += (matring[3][i]-'0');


        printf("%c",((F*c + L)%257));
    }

    printf("\n");

	return 0;
}
