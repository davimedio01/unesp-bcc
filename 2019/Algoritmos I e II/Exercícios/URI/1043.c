#include <stdio.h>
#include <math.h>

int main()
{
    float a,b,c,perimetro,area_tra;
    scanf("%f %f %f", &a,&b,&c);

    if ((fabs(b-c)<a && a<(b+c))|| (fabs(a-c)<b && b<a+c) || (fabs(a-b)<c && c<a+b))
    {
        perimetro=(a+b+c);
        printf("Perimetro = %.1f\n",perimetro);
    }
    else
    {
        area_tra=((a+b)*c/2);
        printf("Area = %.1f\n", area_tra);
    }
    return 0;
}
