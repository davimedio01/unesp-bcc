#include <stdio.h>
#include <stdlib.h>

int main()
{
    int d;
    scanf("%d",&d);
    if(d<=800) printf("1\n");
    else if(d<=1400) printf("2\n");
    else if(d<=2000) printf("3\n");

    return 0;
}
