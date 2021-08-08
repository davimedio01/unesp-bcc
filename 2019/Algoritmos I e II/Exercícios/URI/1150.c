#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,z=0,i,j,soma=0;
    scanf("%i",&x);
    do
    {
        scanf("%i",&z);
    }while(x>=z);

    for(i=x,j=0;j<z;i++)
    {
        j+=i;
        soma++;
    }
    printf("%i\n",soma);
    return 0;
}
