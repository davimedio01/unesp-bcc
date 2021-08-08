#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,bino,aux1=0,aux2=0,aux3=0,aux4=0;
    scanf("%i",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%i",&bino);
        if(bino%2==0)
            aux1++;
        if(bino%3==0)
            aux2++;
        if(bino%4==0)
            aux3++;
        if(bino%5==0)
            aux4++;
    }
    printf("%i Multiplo(s) de 2\n",aux1);
    printf("%i Multiplo(S) de 3\n",aux2);
    printf("%i Multiplo(s) de 4\n",aux3);
    printf("%i Multiplo(s) de 5\n",aux4);

    return 0;
}
