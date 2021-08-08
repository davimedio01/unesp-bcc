#include <stdio.h>
#include <math.h>

int main()
{
    int n,quad,i;
    scanf("%i",&n);

    for(i=2;i<=n;i=i+2)
    {
        quad=i*i;
        printf("%i^2 = %i\n",i,quad);
        quad=0;
    }

    return 0;
}
