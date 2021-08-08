#include <stdio.h>
#include <stdlib.h>

int main()
{
    int s,t,f,aux1;
    scanf("%i %i %i",&s,&t,&f);
    aux1=s+t+f;
    if(aux1<0)
        aux1+=24;
    printf("%i\n",aux1%24);
    return 0;
}
