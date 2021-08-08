#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,num,i;
    scanf("%i",&n);

    for(i=1;i<=n;i++)
    {
        scanf("%i",&num);
        if(num==0)
            printf("NULL\n");
        else if(num>0&&num%2==0)
            printf("EVEN POSITIVE\n");
        else if(num>0&&num%2==1)
            printf("ODD POSITIVE\n");
        else if(num<0&&num%2==0)
            printf("EVEN NEGATIVE\n");
        else if(num<0&&num%2==-1)
            printf("ODD NEGATIVE\n");
    }

    return 0;
}
