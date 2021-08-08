#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 102
int main()
{
	int leds[10] = {2,5,5,4,5,6,3,7,6,6};
	int n;
	char num[MAX];
	scanf("%d",&n);
	do
	{
		int cont=0, i;
		scanf("%s",&num);
		
		for(i=0;i<strlen(num);i++)
		{
			switch(num[i])
			{
				case '1':
					cont += leds[0];
					break;
				case '2':
					cont += leds[1];
					break;
				case '3':
					cont += leds[2];
					break;
				case '4':
					cont += leds[3];
					break;
				case '5':
					cont += leds[4];
					break;
				case '6':
					cont += leds[5];
					break;
				case '7':
					cont += leds[6];
					break;
				case '8':
					cont += leds[7];
					break;
				case '9':
					cont += leds[8];
					break;
				case '0':
					cont += leds[9];
					break;
			}
		}
		printf("%d leds\n",cont);
		n--;
	}while(n!=0);
	return 0;
}

