#include <stdio.h>
#include <math.h>


int main()
{
	int t,i,j,n,k;
	scanf("%d",&t);
	
	for(i=0;i<t;i++)
	{
		scanf("%d", &n);
		int soma=0;
		
		for(j=0;j<n;j++)
			soma += pow(2,j);
		printf("%d\n",soma);
	}
	
	return 0;	
}
