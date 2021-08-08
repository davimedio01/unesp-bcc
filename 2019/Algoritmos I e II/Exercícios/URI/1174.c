#include <stdio.h>
#include <stdlib.h>

int main()
{
    float a[100],n;
    int i;
    for(i=0;i<100;i++)
    {
        scanf("%f",&a[i]);
        n=a[i];
        if(n<=10)
            printf("A[%i] = %.1f\n",i,n);
    }
    return 0;
}
