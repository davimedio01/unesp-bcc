#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int angulo;
    while(scanf("%d",&angulo) != EOF)
    {
        if(angulo%6==0)
            printf("Y\n");
        else
            printf("N\n");
    }
	return 0;
}
