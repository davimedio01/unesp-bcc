#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte "Windows 1252"

int main()
{
	
    int n;
    scanf("%d",&n);
    while(n>0)
    {
        int f1, f2;
        scanf("%d %d", &f1, &f2);
		int div_n,div_s,aux;
		if(f1<f2)
		{
			div_n = f2;
			div_s = f1;
		}
		else
		{
			div_n = f1;
			div_s = f2;
		}
		
		while(div_n%div_s != 0)
		{
			aux = div_n%div_s;
			div_n = div_s;
			div_s = aux;	
		}
        
        printf("%d\n", div_s);
        
        n--;
    }

	return 0;
}
