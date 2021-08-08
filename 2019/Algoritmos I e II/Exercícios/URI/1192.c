#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
	int n;
	scanf("%d",&n);
	
	do
	{
		int d1,d2;
		char l;
		fflush(stdin);
		scanf("%d%c%d",&d1,&l,&d2);
		
		if(d1==d2)
			printf("%d\n",(d1*d2));
		else
		{
			if(islower(l))
				printf("%d\n",(d1+d2));
			else
				printf("%d\n",(d2-d1));
		}
		n--;
	}while(n!=0);
	return 0;
}

