#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,n,i,soma=0;
    scanf("%i %i",&a,&n);
    while(n<=0)
    {
        scanf("%i",&n);
    }
    for(i=1;i<=n;i++)
    {
        soma+=a;
        a++;
    }
    printf("%i\n",soma);
    return 0;
}
