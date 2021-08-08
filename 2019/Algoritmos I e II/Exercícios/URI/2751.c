#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a=15,b=a/2;
    float c=15.456,d=c/7;
    printf("Valores de b:\n");
    printf("-------------\n");
    printf("1) b = %i\n",b);
    printf("2) b = %20i\n",b);
    printf("3) b = 0000000000000000000%i\n",b);
    printf("4) b = %-20i\n",b);
    printf("5) b = %i%%\n",b);
    printf("\n");
    printf("Valores de d:\n");
    printf("-------------\n");
    printf("1) d = %f\n",d);
    printf("2) d = %.0f\n",d);
    printf("3) d = %.1f\n",d);
    printf("4) d = %.2f\n",d);
    printf("5) d = %.3f\n",d);
    printf("6) d = %20.3f\n",d);
    printf("7) d = 000000000000000%.3f\n",d);
    printf("8) d = %-20.3f\n",d);
    printf("9) d = %.2f%%\n",d);
    return 0;
}
