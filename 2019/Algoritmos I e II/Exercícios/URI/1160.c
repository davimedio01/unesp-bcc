#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,pa,pb,aux;
    float g1,g2;
    scanf("%i",&n);

    for(i=1;i<=n;i++)
    {
        aux=0;
        scanf("%i %i %f %f",&pa,&pb,&g1,&g2);
        while(pa<=pb)
        {
            pa*=((g1/100.00)+1.0);
            pb*=((g2/100.00)+1.0);
            aux++;
            if(aux>100)
            {
                printf("Mais de 1 seculo.\n");
                break;
            }
        }
        if(aux<=100)
            printf("%i anos.\n",aux);
    }

    return 0;
}
