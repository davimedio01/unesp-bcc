#include <stdio.h>
#define MAX 2000
void Ordena_Vetor (int vet[], int n)
{
	int aux,i,j;
	for (i=1;i<n;i++) {
   		for (j=0;j<n-1; j++) {
     		if (vet[j]>vet[j+1]) {
       		aux=vet[j];
       		vet[j]=vet[j+1];
       		vet[j+1]=aux;
     		}
   		}
 	}
}

int main()
{
	int n,i;
	scanf("%d",&n);
	int a,cont[MAX];
	//Iniciar contador de cada posição ser um numero digitado (limite do n°2000)
	for(i=0;i<MAX;i++)
		cont[i]=0;
	for(i=0;i<n;i++)
	{
		scanf("%d",&a);
		cont[a-1]++;
	}
	//Vai mostrar na ordem os que tiverem contador>0 (ou seja, os que o usuario digitou)
	for(i=0;i<MAX;i++)
		if(cont[i]!=0)
			printf("%d aparece %d vez(es)\n",i+1,cont[i]);
	return 0;
}

