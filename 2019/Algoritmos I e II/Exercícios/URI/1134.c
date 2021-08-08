#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,a=0,g=0,d=0;
    while(1)
    {
        scanf("%i",&n);
        if(n==4)
            break;
        else
        {
            if(n==1)
                a++;
            else if(n==2)
                g++;
            else if(n==3)
                d++;
            else
                continue;
        }
    }
    printf("MUITO OBRIGADO\n");
    printf("Alcool: %i\n",a);
    printf("Gasolina: %i\n",g);
    printf("Diesel: %i\n",d);

    return 0;
}
