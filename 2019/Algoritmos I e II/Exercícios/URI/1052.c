#include <stdio.h>
#include <stdlib.h>

int main()
{
    int mes;
    scanf("%i",&mes);
    if (mes<=12 && mes>0) {
        if(mes==1) printf ("January\n");
        if(mes==2) printf("February\n");
        if(mes==3) printf("March\n");
        if(mes==4) printf("April\n");
        if(mes==5) printf("May\n");
        if(mes==6) printf("June\n");
        if(mes==7) printf("July\n");
        if(mes==8) printf("August\n");
        if(mes==9) printf("September\n");
        if(mes==10) printf("October\n");
        if(mes==11) printf("November\n");
        if(mes==12) printf("December\n");
}
    return 0;
}
