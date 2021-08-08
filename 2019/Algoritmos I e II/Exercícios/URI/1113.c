#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,y;
    while(x!=y)
    {
        scanf("%i %i",&x,&y);
        if(x>y)
            printf("Decrescente\n");
        else if(x<y)
            printf("Crescente\n");
    }

    return 0;
}
