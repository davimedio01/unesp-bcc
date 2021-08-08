#include <stdio.h>
#include <math.h>

int main()
{
    int a,b,c,area,aux,ladoterreno;
    while(1)
    {
        scanf("%i", &a);
        if(a==0)
            break;
        else
        {
            scanf("%i %i", &b,&c);
            if(b==0||c==0)
                break;
            area=a*b;
            aux=(area*100)/c;
            ladoterreno=pow(aux,0.5);
            printf("%i\n",ladoterreno);
        }
    }
    return 0;
}
