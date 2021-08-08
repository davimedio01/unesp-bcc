#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x;
    scanf("%i",&x);

    if(x>=1 && x<=1000)
    {
        for(int i=0;i<=x;i++)
        {
            if(i%2!=0)
                printf("%i\n",i);
        }
    }

    return 0;
}
