#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,fatorial=1;
    scanf("%i",&n);
    for(i=n;i>=1;i--)
    {
        fatorial*=i;
    }
    printf("%i\n",fatorial);

    return 0;
}
