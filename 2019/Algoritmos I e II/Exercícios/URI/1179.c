#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,par[5],impar[5],i,j,qp=0,qi=0;
    for(i=0;i<15;i++)
    {
        scanf("%i",&n);
        if(n%2==0)
        {
            par[qp]=n;
            qp++;
            if(qp==5)
            {
                for(j=0;j<5;j++)
                    printf("par[%i] = %i\n",j,par[j]);
                qp=0;
            }

        }
        else
        {
            impar[qi]=n;
            qi++;
            if(qi==5)
            {
                for(j=0;j<5;j++)
                    printf("impar[%i] = %i\n",j,impar[j]);
                qi=0;
            }
        }
    }
    for(j=0;j<qi;j++)
        printf("impar[%i] = %i\n",j,impar[j]);
    for(j=0;j<qp;j++)
        printf("par[%i] = %i\n",j,par[j]);

    return 0;
}
