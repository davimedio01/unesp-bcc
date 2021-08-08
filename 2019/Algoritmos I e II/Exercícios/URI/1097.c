#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,x=7,y;
    for(i=1;i<=9;i=i+2)
    {
        for(j=x,y=1;y<=3;j--,y++)
            printf("I=%i J=%i\n",i,j);
        x=x+2;
    }

    return 0;
}
