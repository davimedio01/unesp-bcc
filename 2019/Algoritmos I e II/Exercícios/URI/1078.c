#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,tabuada=0;
    scanf("%i",&n);

    for(i=1;i<=10;i++)
    {
        if(n>2&&n<1000)
        {
            tabuada=i*n;
            printf("%i x %i = %i\n",i,n,tabuada);
        }
        tabuada=0;
    }
    return 0;
}
