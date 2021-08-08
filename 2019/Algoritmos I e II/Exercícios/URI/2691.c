#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int i, j, x, y, n;
    scanf("%d", &n);
    while(n>0)
    {
        scanf("%dx%d", &x, &y);
        for(i=5; i<=10; i++)
        {
            if(x!=y)
                printf("%d x %d = %d && %d x %d = %d\n", x, i, x*i, y, i, y*i);
            else
                printf("%d x %d = %d\n", x, i, x*i);
        }

        n--;
    }
	return 0;
}
