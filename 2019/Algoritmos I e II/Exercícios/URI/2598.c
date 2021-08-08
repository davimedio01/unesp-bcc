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

    int c;
    scanf("%d",&c);
    while(c>0)
    {
        int n, m;
        scanf("%d %d", &n, &m);
        int cont;
        if(n%m > 0)
            cont = (n/m) + 1;
        else if (n%m == 0)
            cont = (n/m);
        printf("%d\n",cont);
        
        c--;
    }

	return 0;
}
