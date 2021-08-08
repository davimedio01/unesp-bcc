#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,aux1,i;
    while(1)
    {
        scanf("%i",&x);
        if(x==0)
            break;
        else
        {
            if(x%2==0)
            {
                aux1=0;
                for(i=1;i<=5;i++)
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
                for(i=1;i<=5;i++)
                {
                    aux1+=x;
                    x+=2;
                }
                printf("%i\n",aux1);
            }
        }
    }
    return 0;
}
