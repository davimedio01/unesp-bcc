#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,y,i,soma=0;
    scanf("%i\n%i",&x,&y);

    if(x<y)
    {
        for(i=x;i<=y;i++)
        {
            if(i%13==0)
                continue;
            soma+=i;
        }
    }
    else if(x>y)
    {
        for(i=y;i<=x;i++)
        {
            if(i%13==0)
                continue;
            soma+=i;
        }
    }
    printf("%i\n",soma);

    return 0;
}
