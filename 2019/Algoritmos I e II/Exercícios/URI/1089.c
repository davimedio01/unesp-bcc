#include <stdio.h>

int main()
{
	int n;
	while(1)
	{
		scanf("%d",&n);
		if(n==0)
			break;
		int H[n],i;
		for(i=0;i<n;i++)
			scanf("%d",&H[i]);
		int cont=0;
		
		//Dois elementos = dois picos
		if(n==2)
			cont=2;
			
		//Analisar as repetições
		else
		{
			if((H[n-1]>H[0] && H[1]>H[0]) || (H[0]>H[n-1] && H[0]>H[1]))
				cont++;
			
			for(i=1;i<n-1;i++)
				if((H[i-1]>H[i] && H[i+1]>H[i]) || (H[i]>H[i-1] && H[i]>H[i+1]))
					cont++;
					
			if((H[n-2]>H[n-1] && H[0]>H[n-1]) || (H[n-1]>H[n-2] && H[n-1]>H[0]))
				cont++;
		}
		
		printf("%d\n",cont);
	}
	return 0;
}

