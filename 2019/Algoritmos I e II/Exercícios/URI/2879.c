#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,porta,aux=0;
    scanf("%d",&n);

    srand(time(NULL));

    for(i=0;i<n;i++)
    {
        scanf("%d",&porta);
        if(porta==2||porta==3)
            aux++;
    }
    printf("%d\n",aux);

    return 0;
}
