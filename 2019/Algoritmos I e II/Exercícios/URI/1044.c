#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b;
    scanf("%i %i",&a,&b);
    if((a%b==0)||(b%a==0))
        printf("Sao Multiplos\n");
    else
        printf("Nao sao Multiplos\n");

    return 0;
}
