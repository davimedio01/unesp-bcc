#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 51
int main()
{
 	int n;
 	scanf("%d",&n);
 	do
 	{
 		fflush(stdin);
 		char caracter[MAX];
 		scanf("%s",&caracter);
 		
 		int i, desloc;
 		scanf("%d",&desloc);
 		for(i=0;i<strlen(caracter);i++)
 		{
 			if((caracter[i]-desloc)<'A')
 				caracter[i] = ((caracter[i] - desloc) + 26);
 			/*else if((caracter[i]-desloc)>'Z')
 				caracter[i] = ((caracter[i] - desloc) - 26);*/
 			else
 				caracter[i] -= desloc;
 			printf("%c",caracter[i]);
		}
		printf("\n");
		for(i=0;i<strlen(caracter);i++)
		{
			if((caracter[i]+desloc)>'Z')
 				caracter[i] = ((caracter[i] + desloc) - 26);
 		//	else if((caracter[i]+desloc)<'A')
 		//		caracter[i] = ((caracter[i] + desloc) + 26);
 			else
 				caracter[i] += desloc;
 			//printf("%c",caracter[i]);
		}
		//printf("\n");
 		n--;
	}while(n!=0);
	return 0;
}

