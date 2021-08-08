#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max 1005
#define MAX_FLORESTA 205
int main()
{
 	int n;
 	scanf("%d",&n);
 	
 	int tam_floresta[MAX_FLORESTA][MAX_FLORESTA], i, j, k;
 	for(i=0;i<n;i++)
 		for(j=0;j<n;j++)
 			scanf("%d",&tam_floresta[i][j]);
 		
	int aux[max], cont=0;
	for(i=0;i<max;i++)
		aux[i]=0;
	int	x,y;
 	for(k=0;k<2*n;k++)
 	{
 		scanf("%d %d",&x,&y);
 		x--;
 		y--;
 		
		aux[tam_floresta[x][y]]=1;
	}
	
	for(i=0;i<max;i++)
	{
		if(aux[i]==1)
			cont++;
	}
	
	printf("%d\n", cont);
	
	return 0;
}

