#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    long long int guerreiros, total = 0;
    int n;
    scanf("%d", &n);

    while(n>0)
    {
        scanf("%lld", &guerreiros);
        total = (sqrt(8*guerreiros+1)-1)/2;
        printf("%lld\n", total);
        n--;
    }
	return 0;
}
