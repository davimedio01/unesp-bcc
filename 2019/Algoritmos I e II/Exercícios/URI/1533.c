#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max 100

int main()
{

	while(1)
	{
		int n, i, j;
		scanf("%d",&n);
		if(n==0)
			break;
		
		int num[n], maximo=0, pos=0;
		for(i=0;i<n;i++)
		{
			scanf("%d",&num[i]);
			if(maximo<num[i])
				maximo = num[i];
		}
			
		while(maximo>0)
		{
			maximo--;
			for(i=0;i<n;i++)
			{
				if(num[i] == maximo)
				{
					pos = i+1;
					break;
				}
			}
			if(pos!=0)
				break;
		}
		
		printf("%d\n",pos);
	}
	return 0;
}
