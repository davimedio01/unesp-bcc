#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

int main()
{
	char bits[34];
	int i, tam, cont;
	while(1)
	{
		scanf("%s", &bits);
		if(bits[0] == '#')
			break;
		cont = 0;
		tam = strlen(bits);
		for(i=0; i<tam; i++)
		{
			if(bits[i] == '1')
				cont++;
		}
		if(bits[tam-1] == 'e')
		{
			if(cont%2 == 0)
				bits[tam-1] = '0';
			else
				bits[tam-1] = '1';
		}
		else if(bits[tam-1] == 'o')
		{
			if(cont%2 == 0)
				bits[tam-1] = '1';
			else
				bits[tam-1] = '0';
		}
		printf("%s\n", bits);
	}
	return 0;
}
