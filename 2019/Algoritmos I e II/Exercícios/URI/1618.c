#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max 100

int main()
{
 	int n;
	scanf("%d",&n);
	while(n>0)
	{
		int Ax,Ay,Bx,By,Cx,Cy,Dx,Dy;
		int Rx,Ry;
		scanf("%d %d %d %d %d %d %d %d %d %d", &Ax,&Ay,&Bx,&By,&Cx,&Cy,&Dx,&Dy,&Rx,&Ry);
		
		int aux;
		if((Rx>=Ax)&&(Rx<=Bx)&&(Ry>=Ay)&&(Ry<=Cy)) //Área do Retangulo
			aux=1;
		else
			aux=0;
		
		printf("%d\n",aux);

		n--;
	}
	return 0;
}

