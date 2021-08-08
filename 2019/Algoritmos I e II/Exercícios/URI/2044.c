#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int n, divida_total = 0, preco, i, cont;
    while(1)
    {
        cont = 0;
        divida_total = 0;
        scanf("%d", &n);
        if(n==-1)
            break;
        for(i=0; i<n; i++)
        {
            scanf("%d", &preco);
            divida_total += preco;
            if(divida_total % 100 == 0)
                cont++;
        }
        printf("%d\n", cont);
    }
	return 0;
}
