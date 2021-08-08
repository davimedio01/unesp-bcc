#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int n, i=1;
    while(1)
    {
        scanf("%d", &n);
        if(n==-1)
            break;
        printf("Experiment %d: %d full cycle(s)\n", i, n/2);
        i++;
    }
	return 0;
}
