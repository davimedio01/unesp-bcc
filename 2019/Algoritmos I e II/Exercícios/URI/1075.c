#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i;
    scanf("%i",&n);
    for(i=1;i<=10000;i++)
    {
        if(i%n==2)
            printf("%i\n",i);
    }

    return 0;
}
