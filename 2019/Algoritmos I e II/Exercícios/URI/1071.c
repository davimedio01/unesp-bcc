#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,y,soma=0;
    scanf("%i\n%i",&x,&y);

    if(x==y)
        printf("%i\n",soma);
    else if(x<y)
    {
        for(x=x+1;x<y;x++)
        {
            if(x%2==1||x%2==-1)
                soma+=x;
        }
        printf("%i\n",soma);
    }
    else if(x>y)
    {
        for(y=y+1;x>y;y++)
        {
            if(y%2==1||y%2==-1)
                soma+=y;
        }
        printf("%i\n",soma);
    }

    return 0;
}
