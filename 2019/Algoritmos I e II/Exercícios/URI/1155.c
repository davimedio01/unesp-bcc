#include <stdio.h>
#include <stdlib.h>

int main()
{
    float i,s1,sf=0;
    for(i=1;i<=100;i++)
    {
        s1=1/i;
        sf+=s1;
    }
    printf("%.2f\n",sf);
    return 0;
}
