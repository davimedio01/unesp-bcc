#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 91
int main()
{
	int n,b;
	scanf("%d %d", &n, &b);
	int i,j;
	while(n!=0 && b!=0)
	{
		int bolas[MAX], aux[MAX];
		for(i=0;i<MAX;i++)
			aux[i]=0;
		
		for(i=0;i<b;i++)
			scanf("%d",&bolas[i]);
			
		int cont=0;
		for(i=0;i<b;i++)
		{
			for(j=i+1;j<b;j++)
			{
				if((abs(bolas[i]-bolas[j])>=0) && (abs(bolas[i]-bolas[j])<=n))
					aux[abs(bolas[i]-bolas[j])]++;
			}
		}
		
		for(i=0;i<MAX;i++)
			if(aux[i]!=0)
				cont++;
		if(cont==n)
			printf("Y\n");
		else
			printf("N\n");

		scanf("%d %d", &n, &b);
	}

	return 0;
}

