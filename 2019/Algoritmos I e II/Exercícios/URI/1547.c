#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

#define max 100

int main()
{
	int n;
	scanf("%d",&n);
	while(n>0)
	{
		int qt,s;
		scanf("%d %d",&qt,&s);
		
		int vet[qt], dif[qt], i, j;
		for(i=0;i<qt;i++)
		{
			scanf("%d",&vet[i]);
			dif[i] = abs(vet[i]-s);
		}
			
		int pos, aux=101; //Auxiliar com valor máximo do número secreto
		for(i=0;i<qt;i++)
		{
			
			if(vet[i]==s)
			{
				pos = i;
				break;
			}
			
			if(dif[i] < aux)
			{
				aux = dif[i];
				pos = i;
			}
		}
			
		printf("%d\n",pos+1);
		
		n--;
	}
	return 0;
}

