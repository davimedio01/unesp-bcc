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

    long long int n, m;
    while(1)
    {
        scanf("%lld %lld", &n, &m);
        if((n==-1)&&(m==-1))
            break;

        unsigned long long int cont = 0, aux = 0;
        int i, c, j;
        for(i=0;i<n;i++)
        {
            scanf("%d", &c);
            aux += c;
            cont += (aux*m);
        }
        printf("%llu\n",cont);
    }
	return 0;
}
