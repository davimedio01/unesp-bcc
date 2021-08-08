#include <stdio.h>
#include <math.h>

int main()
{
    int n,a,b,aux,duende;
    scanf("%i",&n);
    scanf("%i %i",&a,&b);
    aux=a+b;
    duende=n-aux;
    if(duende>=0)
        printf("Farei hoje!\n");
    else
        printf("Deixa para amanha!\n");

    return 0;
}
