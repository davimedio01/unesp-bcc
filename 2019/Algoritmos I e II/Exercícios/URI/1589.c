#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,r1,r2,rc;
    scanf("%i",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%i %i",&r1,&r2);
        rc=0;
        rc=(r1+r2);
        printf("%i\n",rc);
    }
    return 0;
}
