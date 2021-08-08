#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,y,i,aux=0;
    scanf("%i %i",&x,&y);
    for(i=1;i<=y;i++)
    {
        aux++;
        if(aux==x)
        {
            printf("%i",i);
            aux=0;
            printf("\n");
        }
        else
            printf("%i ",i);
    }
    return 0;
}
