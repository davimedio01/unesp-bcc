#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,par,impar;
    scanf("%i",&x);

    if(x%2==0)
    {
        for(par=x+1;par<=x+11;par=par+2)
            printf("%i\n",par);
    }
    else
    {
        for(impar=x;impar<=x+10;impar=impar+2)
            printf("%i\n",impar);
    }

}
