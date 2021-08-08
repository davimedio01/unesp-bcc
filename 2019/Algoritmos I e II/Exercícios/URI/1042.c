#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b,c;
    scanf("%i %i %i", &a, &b, &c);
    if(a<b)
    {
        if(a<c)
        {
            if(b<c)
                printf("%i\n%i\n%i\n", a,b,c);
            else
                printf("%i\n%i\n%i\n", a,c,b);
        }
        else
        {
                printf("%i\n%i\n%i\n", c,a,b);
        }
    }
    else
    {
        if(b>c)
            printf("%i\n%i\n%i\n", c,b,a);
        else
        {
            if(a<c)
                printf("%i\n%i\n%i\n", b,a,c);
            else
                printf("%i\n%i\n%i\n", b,c,a);
        }
    }
    printf ("\n%i\n%i\n%i\n", a,b,c);

    return 0;
}
