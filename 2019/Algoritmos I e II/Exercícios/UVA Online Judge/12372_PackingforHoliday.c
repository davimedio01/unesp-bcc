#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int n, i;
    scanf("%d", &n);
    for(i=1;i<=n;i++)
    {
        int larg, comp, altura;
        scanf("%d %d %d",&larg, &comp, &altura);

        if((larg<=20)&&(comp<=20)&&(altura<=20))
            printf("Case %d: good\n", i);
        else
            printf("Case %d: bad\n", i);
    }
	return 0;
}
