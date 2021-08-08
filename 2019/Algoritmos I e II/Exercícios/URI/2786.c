#include <stdio.h>
#include <math.h>

int main()
{
    int c,l,laj_1,laj_2;
    scanf("%d",&l);
    scanf("%d",&c);

    laj_1=(c*l)+(c-1)*(l-1);
    laj_2=(c-1)*2+(l-1)*2;

    printf("%d\n",laj_1);
    printf("%d\n",laj_2);

    return 0;
}
