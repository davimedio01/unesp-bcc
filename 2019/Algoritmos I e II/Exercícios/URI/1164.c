#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,j,num,aux1=0,aux2;;
    scanf("%i",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%i",&num);
        aux2=num/2;
        aux1=0;
        for(j=1;j<=aux2;j++)
        {
            if(num%j==0)
            {
                aux1+=j;
            }
        }
        if(aux1==num)
            printf("%i eh perfeito\n",num);
        else
            printf("%i nao eh perfeito\n",num);
    }
    return 0;
}
