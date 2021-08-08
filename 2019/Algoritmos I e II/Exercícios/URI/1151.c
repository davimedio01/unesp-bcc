#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,x=0,y=1,z=0;
    scanf("%i",&n);
    for(i=1;i<n;i++)
    {
        if(i%2==1)
        {
            printf("%i ",z);
            z=x+y;
            x=z;
        }
        else if(i==2)
            printf("%i ",z);
        else if(i%2==0)
        {
            printf("%i ",z);
            z=x+y;
            y=z;
        }
    }
    printf("%i\n",z);
    return 0;
}
