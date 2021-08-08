#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max 100

int main()
{
	int m,k;
	while(scanf("%d %d",&m,&k) != EOF)
	{
		int mi[m], ki[k], aux[max];
		int i,j;
		
		for(i=0;i<max;i++)
			aux[i]=0;
		for(i=0;i<m;i++)
			scanf("%d",&mi[i]);
		for(i=0;i<k;i++)
			scanf("%d",&ki[i]);
			
		int dura=0, repete;
		for(i=0;i<k;i++)	
		{
			repete=0;
			for(j=0;j<m;j++)
			{
				if(aux[j]!=0)
					repete++;
				
				if(repete==m)
					break;
			}
			if(repete==m)
				break;
			dura += mi[ki[i]-1];
			aux[ki[i]-1]++;
		}
		if(repete==m)
			printf("%d\n",dura);
		else
			printf("-1\n");
	}

	return 0;
}

