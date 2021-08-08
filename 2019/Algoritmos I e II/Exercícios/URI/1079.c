#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i;
    float n1,n2,n3,media=0;
    scanf("%i",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%f %f %f",&n1,&n2,&n3);
        media=(n1*2+n2*3+n3*5)/10;
        printf("%.1f\n",media);
        media=0;
    }

    return 0;
}
