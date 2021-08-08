#include <stdio.h>
#include <stdlib.h>

int main()
{
    int p,j1,j2,r,a,soma=0,aux1=0;
    scanf("%d %d %d %d %d",&p,&j1,&j2,&r,&a);
    soma=j1+j2;

    if((soma%2==0&&p==1)||(soma%2==1&&p==0))
        aux1=1;
    else
        aux1=2;
    if((r==1&&a==0)||(r==0&&a==1))
        aux1=1;
    else if(r==1&&a==1)
        aux1=2;

    printf("Jogador %d ganha!\n",aux1);

    return 0;
}
