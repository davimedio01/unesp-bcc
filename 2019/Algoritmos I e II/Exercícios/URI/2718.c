#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i;
    long long int x;
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        scanf("%lld",&x);
        long long int max=0,aux1=0,temp;
        while(x>0)
        {
            temp=x%2;
            x/=2;
            if(temp==1)
                aux1++;
            else
            {
                if(aux1>max)
                {
                    max=aux1;
                    aux1=0;
                }
                aux1=0;
            }
        }
        if(aux1>max)
        {
            max=aux1;
            aux1=0;
        }
        printf("%lld\n",max);
    }
    return 0;
}
