#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,x,y,i,j,soma=0;
    scanf("%i",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%i %i",&x,&y);
        if(x==y)
        {
            soma=0;
            printf("%i\n",soma);
        }
        else if(x>y)
        {
            for(j=y+1,soma=0;j<x;j++)
            {
                if(j%2==1||j%2==-1)
                    soma+=j;
            }
            printf("%i\n",soma);
        }
        else if(x<y)
        {
            for(j=x+1,soma=0;j<y;j++)
            {
                if(j%2==1||j%2==-1)
                    soma+=j;
            }
            printf("%i\n",soma);
        }
    }

    return 0;
}
