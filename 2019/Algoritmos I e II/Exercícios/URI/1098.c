#include <stdio.h>
#include <stdlib.h>

int main()
{
    float i,j,aux;
    int x;
    for(i=0; i<=1.9; i=i+0.2)
    {
        for(j=1.0; j<=3.0;j++)
        {
            aux=j+i;
            if(i==0.0||i==1.0)
                printf("I=%.0lf J=%.0lf",i,aux);
            else if(aux==3.0||aux==4.0||aux==5.0)
                printf("I=%.0lf J=%.0lf",i,aux);
            else
                printf("I=%.1lf J=%.1lf",i,aux);
            printf("\n");
        }
    }
    for(x=3; x<=5; x++)
        printf("I=2 J=%.0f\n",x);

    return 0;
}
