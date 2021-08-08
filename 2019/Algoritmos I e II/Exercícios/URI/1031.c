#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte "Windows 1252"

int main()
{
	int n;
	while(1)
	{
		scanf("%d",&n);
		if(n==0)
			break;
		
		int regiao=1;
		while(1)
		{
			if(Recursivo_Josephus(n,regiao) != 11)
				regiao++;
			else
				break;
		}
		printf("%d\n",regiao);
	}

	return 0;
}


/*int Salto_Circulo(int n, int k)
{
	
	int aux=0, i;
	for(i=1;i<n;i++)
		aux = (aux+k)%i;
	return aux;
}*/

int Recursivo_Josephus (int n, int k)
{
	if(n==0)
		return 0;
	return abs((Recursivo_Josephus(n-1,k) + k-1) % n);
}
