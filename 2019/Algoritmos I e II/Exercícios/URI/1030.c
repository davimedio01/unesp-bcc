#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte "Windows 1252"

int main()
{
	int i,nc;
	scanf("%d",&nc);
	for(i=1;i<=nc;i++)
	{
		int n, k;
		scanf("%d %d", &n, &k);
		//printf("Case %d: %d\n", i, Salto_Circulo(n,k));
		printf("Case %d: %d\n", i, Recursivo_Josephus(n,k));
	}
	
	return 0;
}

/*int Salto_Circulo(int n, int k)
{
	if(n==1)
		return 1;
	int aux=0, i;
	for(i=2;i<=n;i++)
		aux = (aux+k)%i;
	return aux+1;
}
/*
Quando alguém é morto ele não é mais considerado na conta do salto.

Para n=5 e k=2:
1¹ (2)² 3 4 5 //Quem está entre parentese morreu 
1 3¹ (4)² 5 //O próximo salto é avaliado a partir do próximo individuo 
(1)² 3 5¹ //Reinicia o circulo 
3¹ (5)² //Resta agora só o 3
*/


int Recursivo_Josephus (int n, int k)
{
	if(n==0)
		return 0;
	return abs((Recursivo_Josephus(n-1,k) + k-1) % n) + 1;
}



