#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned long long int Fib[61]; //64 bits sem sinal (unsigned long long)
    int t,i,n; //32 bits com sinal

    Fib[0]=0;
    Fib[1]=1;
    for(i=2;i<=60;i++)
        Fib[i] = Fib[i-2]+Fib[i-1];

    scanf("%i",&t);
    for(i=0;i<t;i++)
    {
        scanf("%i",&n);
        printf("Fib(%i) = %llu\n",n,Fib[n]);
    }
    return 0;
}
