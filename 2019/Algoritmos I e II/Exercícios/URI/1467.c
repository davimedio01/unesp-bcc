#include <stdio.h>

int main()
{
	int jogo[3];
	//Todas condições com if
	while(scanf("%d %d %d",&jogo[0],&jogo[1],&jogo[2]) != EOF)
	{
		if((jogo[0]==1 && jogo[1]==0 && jogo[2]==0) || (jogo[0]==0 && jogo[1]==1 && jogo[2]==1))
			printf("A\n");
		else if((jogo[0]==0 && jogo[1]==1 && jogo[2]==0) || (jogo[0]==1 && jogo[1]==0 && jogo[2]==1))
			printf("B\n");
		else if((jogo[0]==0 && jogo[1]==0 && jogo[2]==1) || (jogo[0]==1 && jogo[1]==1 && jogo[2]==0))
			printf("C\n");
		else if((jogo[0]==0 && jogo[1]==0 && jogo[2]==0) || (jogo[0]==1 && jogo[1]==1 && jogo[2]==1))
			printf("*\n");
	}
	return 0;
}

