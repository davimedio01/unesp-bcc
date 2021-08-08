#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte "Windows 1252"

int cont1, cont2;

int main()
{
	int n;
	scanf("%d",&n);
	while(n>0)
	{
		int fibo;
		scanf("%d",&fibo);
		cont1=cont2=0;
		
		cont1 = Fibo_Rec(fibo);
		printf("fib(%d) = %d calls = %d\n", fibo, cont2-1, cont1);
		
		n--;
	}

	return 0;
}

int Fibo_Rec (int n)
{
	cont2++;
	if (n<=1)
		return n;
  	return Fibo_Rec(n-1) + Fibo_Rec(n-2);
}
