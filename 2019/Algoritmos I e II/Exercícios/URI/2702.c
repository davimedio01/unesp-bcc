#include <stdio.h>
#include <math.h>


int main()
{
    int ca,ba,pa,cr,br,pr,soma=0,i;

    scanf("%d %d %d",&ca,&ba,&pa); //N° refeições disponíveis (frango, bife e massa)
    scanf("%d %d %d",&cr,&br,&pr); //N° refeições adquiridas respectivamente

    if((ca-cr)<0)
        soma+=(ca-cr);
    if((ba-br)<0)
        soma+=(ba-br);
    if((pa-pr)<0)
        soma+=(pa-pr);

    soma=abs(soma);
    printf("%d\n",soma);

    return 0;
}
