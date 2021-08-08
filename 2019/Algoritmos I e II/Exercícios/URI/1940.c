#include <stdio.h>
#include <math.h>

int main()
{
	int j,r,i,k,x;
	do
	{
		scanf("%d %d",&j,&r);
	}while(j==0);	
	
	int pontos[r][j];
	int vet[j];
	
	for(i=0;i<r;i++)
		for(k=0;k<j;k++)
			scanf("%d", &pontos[i][k]);
			
	for(k=0;k<j;k++)
	{
		vet[k] = 0;
		for(i=0;i<r;i++)
			vet[k] += pontos[i][k];
	}
	
	int aux1 = vet[0], aux2=1;
	for(k=1;k<j;k++)
	{
		if(vet[k]>=aux1)
		{
			aux2=k+1;
			aux1=vet[k];
		}
	}
	printf("%d\n",aux2);
	
	return 0;	
}
