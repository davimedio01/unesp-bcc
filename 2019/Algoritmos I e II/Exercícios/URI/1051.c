#include <stdio.h>
#include <stdlib.h>

int main()
{
    float renda,v1;
    scanf("%f",&renda);

    if(renda>=0.00 && renda<=2000.00)
        printf("Isento\n");
    else if(renda<=3000.00)
    {
        v1=((renda-2000.00)*0.08);
        printf("R$ %.2f\n",v1);
    }
    else if(renda<=4500.00)
    {
        v1=(((renda-3000.00)*0.18)+ 80);
        printf("R$ %.2f\n",v1);
    }
    else if(renda>4500.00)
    {
        v1=(((renda-4500.00)*0.28)+ 350);
        printf("R$ %.2f\n",v1);
    }

    return 0;
}
