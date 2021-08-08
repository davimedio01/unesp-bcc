#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,c;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&c);
        if(c<=8000)
            printf("Inseto!\n");
        else
            printf("Mais de 8000!\n");
    }
    return 0;
}
