#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max 10000

int main()
{
 	int n;
 	scanf("%d",&n);
 	while(n>0)
 	{
 		int x,y;
 		scanf("%d %d",&x,&y);
 		
 		int zonas;
 		while(x%3!=0)
 			x--;
 		while(y%3!=0)
 			y--;
 		zonas = (x*y)/9;
 		printf("%d\n",zonas);
 		
 		n--;
	}

	return 0;
}

