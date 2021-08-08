#include <stdio.h>
#include <math.h>

int main()
{
	int s,va,vb,i;
	while(scanf("%d %d %d", &s, &va, &vb) != EOF)
	{
		float segundos;	
		if(va>vb)
		{
			segundos = (float)s/(va-vb);
			printf("%.2f\n",segundos);
		}
		else
			printf("impossivel\n");
	}
	
	return 0;	
}
