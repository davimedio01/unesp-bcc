#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,par=0;
    for(i=1;i<=5;i++)
    {
        scanf("%i",&n);
        if(n%2==0)
        {
            par++;
        }
    }
    printf("%i valores pares\n",par);

    return 0;
}
