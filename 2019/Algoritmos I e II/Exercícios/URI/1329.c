#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int n, mary, john, i, aux;
    while(1)
    {
        mary = 0;
        john = 0;
        scanf("%d", &n);
        if(n==0)
            break;

        for(i=0; i<n; i++)
        {
            scanf("%d", &aux);
            if(aux==0)
                mary++;
            else if(aux==1)
                john++;
        }
        printf("Mary won %d times and John won %d times\n", mary, john);
    }
	return 0;
}
