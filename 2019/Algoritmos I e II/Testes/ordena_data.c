#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte "Windows 1252"

int main()
{
	system("COLOR 09");
	setlocale(LC_ALL,"Portuguese");

	int n;
	scanf("%d",&n);
	int i,j;
	int data[max][3];
	for(i=0;i<n;i++)
		scanf("%d/%d/%d",&data[i][0],&data[i][1],&data[i][2]);

    printf("\nData Ordenada (Crescente)\n\n");
	for(i=1;i<n;i++)
	{
		for(j=0;j<n-i;j++)
		{
			if(data[j][2]>data[j+1][2])
			{
				Troca_Data(&data[j][2],&data[j+1][2]);
				Troca_Data(&data[j][1],&data[j+1][1]);
				Troca_Data(&data[j][0],&data[j+1][0]);
			}
			else
				if(data[j][2]==data[j+1][2])
					if(data[j][1]>data[j+1][1])
					{
						Troca_Data(&data[j][1],&data[j+1][1]);
						Troca_Data(&data[j][0],&data[j+1][0]);
					}
			else
			 	if(data[j][1]==data[j+1][1])
					if(data[j][0]>data[j+1][0])
						Troca_Data(&data[j][0],&data[j+1][0]);
		}
	}

	for(i=0;i<n;i++)
		printf("%d/%d/%d\n",data[i][0],data[i][1],data[i][2]);

	return 0;
}

void Troca_Data (int *x, int *y)
{
    int aux;
    aux = (*x);
    (*x) = (*y);
    (*y) = aux;
}
