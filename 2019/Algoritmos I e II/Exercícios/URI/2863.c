#include <stdio.h>
#include <stdlib.h>

int main()
{
    int t=0,i;
    float t1;

    while(scanf("%d",&t)!=EOF)
    {
        float maior=12.00;

        while(t--)
        {
            scanf("%f",&t1);
            if(t1<maior)
            {
                maior=t1;
            }
        }
        printf("%.2f\n",maior);
    }
    return 0;
}
