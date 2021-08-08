#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int c, n, i, aux=0;
    scanf("%d",&c);
    while(c>0)
    {
        scanf("%d",&n);
        for(i=1;i<=n;i++)
            aux+=i;
        printf("%d\n",aux+1);
        aux=0;
        c--;
    }
	return 0;
}
