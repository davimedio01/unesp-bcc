#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,qtd=0,c=0,r=0,s=0,total=0;
    float cp=0,rp=0,sp=0;
    char tipo[2];

    scanf("%i",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%i %s",&qtd,&tipo);
        if(qtd>=1&&qtd<=15)
        {
            if(tipo[0]=='C')
            c+=qtd;
        else if(tipo[0]=='R')
            r+=qtd;
        else if(tipo[0]=='S')
            s+=qtd;
        }
    }
    total=(c+r+s);
    cp=c/(float)total*100.00;
    rp=r/(float)total*100.00;
    sp=s/(float)total*100.00;

    printf("Total: %i cobaias\n",total);
    printf("Total de coelhos: %i\n",c);
    printf("Total de ratos: %i\n",r);
    printf("Total de sapos: %i\n",s);
    printf("Percentual de coelhos: %.2f %%\n",cp);
    printf("Percentual de ratos: %.2f %%\n",rp);
    printf("Percentual de sapos: %.2f %%\n",sp);

    return 0;
}
