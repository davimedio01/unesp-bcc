#include <stdio.h>
#include <stdlib.h>

int main()
{
    int cod,qtd;
    scanf("%d %d",&cod,&qtd);
    if(cod==1) printf("Total: R$ %.2f\n",(qtd*4.00));
    else if(cod==2) printf("Total: R$ %.2f\n",(qtd*4.50));
    else if(cod==3) printf("Total: R$ %.2f\n",(qtd*5.00));
    else if(cod==4) printf("Total: R$ %.2f\n",(qtd*2.00));
    else if(cod==5) printf("Total: R$ %.2f\n",(qtd*1.50));

    return 0;
}
