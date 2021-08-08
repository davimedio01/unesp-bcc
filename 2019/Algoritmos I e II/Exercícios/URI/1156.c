#include <stdio.h>
#include <stdlib.h>

int main()
{
    float S=1,i=2,n;
    for(n=3;n<=39;n+=2)
    {
        S+=(n/i);
        i*=2;
    }
    printf("%.2f\n",S);

    return 0;
}
