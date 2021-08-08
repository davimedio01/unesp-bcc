#include <stdio.h>
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
	int a,d;
	while(1)
	{
		scanf("%d %d",&a,&d);
		if((a==0) && (d==0))
			break;
		int jog[a], def[d];
		int i,j,k;
		for(i=0;i<a;i++)
			scanf("%d",&jog[i]);
		for(i=0;i<d;i++)
			scanf("%d",&def[i]);
		int cont;
		Ordena_Vetor(jog,a);
		Ordena_Vetor(def,d);
		if(jog[0] == def[0] && jog[0] == def[1])
			printf("N\n");
		else if(jog[0] == def[1])
			printf("N\n");
		else if (jog[0]>def[0] && jog[0]>def[1])
			printf("N\n");
		else
			printf("Y\n");
	}
	return 0;
}

