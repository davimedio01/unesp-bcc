#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int n, i;
    long long int fimo[18];
    fimo[0] = 0;
    fimo[1] = 1;
    fimo[2] = 1;
    for(i=3;i<18;i++)
    {
        if(i%2!=0)
            fimo[i] = fimo[i-1] * fimo[i-2];
        else
            fimo[i] = fimo[i-1] + fimo[i-2];
    }
    while(scanf("%d", &n)!=EOF)
    {
        printf("%lld\n", fimo[n-1]);
    }
	return 0;
}
