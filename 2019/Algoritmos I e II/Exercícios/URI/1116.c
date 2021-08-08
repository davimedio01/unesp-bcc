#include <stdio.h>
#include <math.h>

int main()
{
    int n,i,x,y;
    float div=0;
    scanf("%i",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%i %i",&x,&y);
        if(y==0 ||(x==0&&y==0))
            printf("divisao impossivel\n");
        else
        {
            div=(float)x/y;
            printf("%.1f\n",div);
        }
        div=0;
    }

    return 0;
}
