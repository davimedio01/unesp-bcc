#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max 100

int main()
{
 	int n,m;
 	scanf("%d %d",&n,&m);
 	
 	int vet[max][max];
 	int i,j;
 	
 	for(i=0;i<n;i++)
 		for(j=0;j<m;j++)
 			scanf("%d",&vet[i][j]);
 			
 	int soma=0;
 	//Somar primeira linha e considerar a maior
 	for(i=0;i<m;i++)
 		soma += vet[0][i];
 	
 	//Comparar com outras somas (linha)
 	int soma2=0;
 	for(i=1;i<n;i++)
 	{
 		soma2=0;
 		for(j=0;j<m;j++)
 		{
 			soma2 += vet[i][j];
		}
		if(soma2>soma)
			soma=soma2;
	}
	//Comparar com outras somas (coluna)
 	for(i=0;i<m;i++)
 	{
 		soma2=0;
 		for(j=0;j<n;j++)
 		{
 			soma2 += vet[j][i];
		}
		if(soma2>soma)
			soma=soma2;
	}
	
	printf("%d\n",soma);
	return 0;
}

