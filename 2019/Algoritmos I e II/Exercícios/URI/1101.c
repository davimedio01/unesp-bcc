#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m,n,i,soma=0;
    while(1)
    {
        scanf("%i %i",&m,&n);
        if((m<=0)||(n<=0))
            break;
        if(m<n)
        {
            for(i=m;i<=n;i++)
            {
                soma+=i;
                printf("%i ",i);
            }
            printf("Sum=%i\n",soma);
            soma=0;
        }
        else if(m>n)
        {
            for(i=n;i<=m;i++)
            {
                soma+=i;
                printf("%i ",i);
            }
            printf("Sum=%i\n",soma);
            soma=0;
        }
    }
    return 0;
}
