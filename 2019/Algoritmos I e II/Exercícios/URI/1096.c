#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j;
    for(i=1;i<=9;i=i+2)
    {
        for(j=7;j>=5;j--)
            printf("I=%i J=%i\n",i,j);
    }

    return 0;
}
