#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,n,cont=0,x=0,y;
    for(i=1;i<=100;i++)
    {
        scanf("%i",&n);
        cont++;
        if(n>x)
        {
            y=cont;
            x=n;
        }
    }
    printf("%i\n",x);
    printf("%i\n",y);

    return 0;
}
