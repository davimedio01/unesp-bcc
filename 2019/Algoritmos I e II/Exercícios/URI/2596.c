#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int c, n, i, j, aux=0, cont;
    scanf("%d", &c);
    while(c>0)
    {
        scanf("%d", &n);
        for(i=1;i<=n;i++)
        {
            cont=0;
            for(j=1;j<=i;j++)
            {
                if(i%j==0)
                    cont++;
            }
            if(cont%2==0)
                aux++;
        }
        printf("%d\n", aux);
        aux=0;
        c--;
    }
	return 0;
}
