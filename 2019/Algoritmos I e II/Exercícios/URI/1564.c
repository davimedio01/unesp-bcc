#include <stdio.h>
#include <stdlib.h>

int main()
{
    int copa;
    while(scanf("%i",&copa)!=EOF)
    {
        if(copa==0)
            printf("vai ter copa!\n");
        else if(copa>0)
            printf("vai ter duas!\n");
    }
    return 0;
}
