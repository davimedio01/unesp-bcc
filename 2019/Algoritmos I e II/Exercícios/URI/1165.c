#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,x,aux1,aux2=0;
    scanf("%i",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%i",&x);
        for(aux1=2;aux1<=x/2;aux1++)
        {
            if(x%aux1==0)
            {
                aux2++;
                break;
            }
        }
        if(aux2==0)
            printf("%i eh primo\n",x);
        else
            printf("%i nao eh primo\n",x);
        aux2=0;
    }
    return 0;
}
