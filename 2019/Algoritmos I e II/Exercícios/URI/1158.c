#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,x,y,aux1,aux2;
    scanf("%i",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%i %i",&x,&y);
        if(x%2==1)
        {
            aux1=0;
            for(aux2=1;aux2<=y;aux2++)
            {
                aux1+=x;
                x+=2;
            }
            printf("%i\n",aux1);
        }
        else
        {
            x++;
            aux1=0;
            for(aux2=1;aux2<=y;aux2++)
            {
                aux1+=x;
                x+=2;
            }
            printf("%i\n",aux1);
        }

    }

    return 0;
}
