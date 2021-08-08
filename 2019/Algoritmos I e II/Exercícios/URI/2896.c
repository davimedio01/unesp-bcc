#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,x,y,aux=0;
    scanf("%i",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%i %i",&x,&y);
        aux=((x%y)+(x/y));
        printf("%i\n",aux);
    }
    return 0;
}
