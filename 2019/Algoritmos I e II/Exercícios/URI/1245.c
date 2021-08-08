#include <stdio.h>
#include <math.h>
#include <string.h>
#define MAX 61

typedef struct{
	int direita;
	int esquerda;
}Pe;
int main()
{
	int n;
	while(scanf("%d",&n) != EOF)
	{
		Pe m[MAX];
		int i;
		//Atribuir cada lado com um contador
		for(i=30;i<MAX;i++)
		{
			m[i].direita=0;
			m[i].esquerda=0;
		}
		int num_pe;
		char lado[10];
		for(i=0;i<n;i++)
		{
			scanf("%d %s",&num_pe,&lado);
			fflush(stdin);
			if(strcmp(lado,"E")==0)
				m[num_pe].esquerda++;
			else if(strcmp(lado,"D")==0)
				m[num_pe].direita++;
		}
		int par=0;
		//Compara a posição x com a posição x+1. Se iguais, ele pula e continua a verificação. Caso combine os sapatos, adiciona no contador
		for(i=30;i<MAX;i++)
		{
			if(!m[i].direita || !m[i].esquerda)
				continue;
				
			if(m[i].direita == m[i].esquerda)
				par += m[i].direita;
			else if(m[i].direita < m[i].esquerda)
				par += m[i].direita;
			else //if(m[i].esquerda < m[i].direita)
				par += m[i].esquerda;
		}
		printf("%d\n",par);
	}
	return 0;
}

