#include <stdio.h>
int main()
{
	int n;
	while(1)
	{
		scanf("%d",&n);
		if(n==0)
			break;
		long long int i,aux;
		for(i=1;i<=n;i++)
		{
			if((i*i)<=n)
			{
				if((i*i)==1)
					printf("%lld",i*i);
				else
					printf(" %lld",i*i);
			}
		}
		printf("\n");
	}
	return 0;
}

