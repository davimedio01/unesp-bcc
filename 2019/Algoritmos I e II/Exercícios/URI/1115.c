#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,y,i=0;
    while(i==0)
    {
        scanf("%i %i",&x,&y);
        if(x>0&&y>0)
            printf("primeiro\n");
        else if(x<0&&y>0)
            printf("segundo\n");
        else if(x<0&&y<0)
            printf("terceiro\n");
        else if(x>0&&y<0)
            printf("quarto\n");
        else if(x==0||y==0)
            break;
    }

    return 0;
}
