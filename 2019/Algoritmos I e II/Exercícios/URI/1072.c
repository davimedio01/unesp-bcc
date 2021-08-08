#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,x;
    int in=0;
    int out=0;
    scanf("%i",&n);

    for(int i=0;i<n;i++)
    {
        scanf("%i",&x);
        if((x>=10) && (x<=20))
            in++;
        else
            out++;
    }

    printf("%i in\n",in);
    printf("%i out\n",out);

    return 0;
}
