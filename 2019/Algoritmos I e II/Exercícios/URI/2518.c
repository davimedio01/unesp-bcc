#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int n;
	while(scanf("%d",&n) != EOF)
	{
		int cat1, cat2, largura;
		scanf("%d %d %d",&cat1, &cat2, &largura);
		
		
		double comprimento = (sqrt(cat1*cat1 + cat2*cat2));		
		double area = ((comprimento*largura)*n);
		
		printf("%.4lf\n", area/10000.0);
	}
	return 0;
}


