#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte "Windows 1252"

int main()
{
    int x1,x2;
    scanf("%d %d", &x1, &x2);

    if(x2<=2)
    {
        if(x1>x2)
            printf("nova\n");
    }
    else if(x2<=96)
    {
        if(x1>x2)
            printf("minguante\n");
        else if((x1>=0)&&(x1<x2)&&(x2>2))
            printf("crescente\n");
    }
    else if(x2<=100)
    {
        if((x1>x2)&&(x2<97))
            printf("minguante\n");
        else
            printf("cheia\n");
    }

	return 0;
}
