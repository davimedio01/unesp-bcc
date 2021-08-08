#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"
long int MDC(long int x, long int y);
int main()
{
	long int x, y, total;
    while(scanf("%ld %ld",&x,&y) != EOF)
    {

        total = MDC(x,y);
        printf("%ld\n", ((2*x/total) + (2*y/total)));


    }
	return 0;
}

long int MDC(long int x, long int y)
{
    long int aux;
    while(x%y!=0)
    {
        aux = x%y;
        x = y;
        y = aux;
    }
    return y;
}
