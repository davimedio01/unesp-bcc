#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte "Windows 1252"

int main()
{
	system("COLOR 09");
	setlocale(LC_ALL,"Portuguese");

	int n,i,j;
    scanf("%d",&n);
    int fibo[max];

    fibo[0] = 0;
    fibo[1] = 1;
    for(i=2;i<=n;i++)
        fibo[i] = fibo[i-1] + fibo[i-2];

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=i;j++)
            printf("%d ",fibo[j]);
        printf("\n");
    }
    for(i=n;i>=1;i--)
    {
        for(j=1;j<=i-1;j++)
            printf("%d ",fibo[j]);
        printf("\n");
    }
	return 0;
}
