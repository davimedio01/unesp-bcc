#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte "Windows 1252"

int main()
{
	int num,den,apostas[max],cont=-1,i;
	while(scanf("%d %d", &num, &den) != EOF)
	{
		apostas[++cont] = Gnomo_Simp(num,den);
		if(apostas[cont]>5)
			printf("Noel\n");
		else
			printf("Gnomos\n");
	}
	for(i=cont; i>=0; i--)
		printf("%d ",apostas[i]);
	printf("\n");

	return 0;
}

int Gnomo_Simp (int num, int den) 
{
	//cout << num << den;
	if(den==0)
		return num;
	return Gnomo_Simp (den, num%den);
}
