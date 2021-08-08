#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int n, auxR = 0, i, cont = 0;
    char ciclos[max];
    while(scanf("%s %d", &ciclos, &n) != EOF)
    {
        cont = 0;
        auxR = 0;

        for(i=0; i<strlen(ciclos); i++)
        {
            if(ciclos[i] == 'R')
                auxR++;
            else if (ciclos[i] == 'W')
            {
                cont++;
                if(auxR%n == 0)
                    cont += (auxR/n);
                else if (auxR%n != 0)
                    cont += (auxR/n)+1;
                auxR=0;
            }
        }
        if(auxR%n == 0)
            cont += (auxR/n);
        else if (auxR%n != 0)
            cont += (auxR/n)+1;

        printf("%d\n", cont);
    }
	return 0;
}
