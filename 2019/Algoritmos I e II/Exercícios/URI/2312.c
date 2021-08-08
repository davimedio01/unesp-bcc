#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte "Windows 1252"
typedef struct
{
    char nome[max];
    int ouro, prata, bronze;
}Medalha;
int main()
{
	int n, i, j;
    scanf("%d",&n);

    Medalha medalhinha[n];
    for(i=0;i<n;i++)
    {
        scanf("%s %d %d %d", &medalhinha[i].nome, &medalhinha[i].ouro, &medalhinha[i].prata, &medalhinha[i].bronze);
        fflush(stdin);
    }

    Medalha aux;
    for(i=1;i<n;i++)
    {
        for(j=0;j<n-1;j++)
        {
            if(medalhinha[j].ouro < medalhinha[j+1].ouro)
            {
                aux.ouro = medalhinha[j].ouro;
                medalhinha[j].ouro = medalhinha[j+1].ouro;
                medalhinha[j+1].ouro = aux.ouro;

                aux.prata = medalhinha[j].prata;
                medalhinha[j].prata = medalhinha[j+1].prata;
                medalhinha[j+1].prata = aux.prata;

                aux.bronze = medalhinha[j].bronze;
                medalhinha[j].bronze = medalhinha[j+1].bronze;
                medalhinha[j+1].bronze = aux.bronze;

                strcpy(aux.nome, medalhinha[j].nome);
                strcpy(medalhinha[j].nome, medalhinha[j+1].nome);
                strcpy(medalhinha[j+1].nome, aux.nome);
            }
            else if (medalhinha[j].ouro == medalhinha[j+1].ouro)
            {
                if(medalhinha[j].prata < medalhinha[j+1].prata)
                {
                    aux.ouro = medalhinha[j].ouro;
                    medalhinha[j].ouro = medalhinha[j+1].ouro;
                    medalhinha[j+1].ouro = aux.ouro;

                    aux.prata = medalhinha[j].prata;
                    medalhinha[j].prata = medalhinha[j+1].prata;
                    medalhinha[j+1].prata = aux.prata;

                    aux.bronze = medalhinha[j].bronze;
                    medalhinha[j].bronze = medalhinha[j+1].bronze;
                    medalhinha[j+1].bronze = aux.bronze;

                    strcpy(aux.nome, medalhinha[j].nome);
                    strcpy(medalhinha[j].nome, medalhinha[j+1].nome);
                    strcpy(medalhinha[j+1].nome, aux.nome);
                }
                else if (medalhinha[j].prata == medalhinha[j+1].prata)
                {
                    if(medalhinha[j].bronze < medalhinha[j+1].bronze)
                    {
                        aux.ouro = medalhinha[j].ouro;
                        medalhinha[j].ouro = medalhinha[j+1].ouro;
                        medalhinha[j+1].ouro = aux.ouro;

                        aux.prata = medalhinha[j].prata;
                        medalhinha[j].prata = medalhinha[j+1].prata;
                        medalhinha[j+1].prata = aux.prata;

                        aux.bronze = medalhinha[j].bronze;
                        medalhinha[j].bronze = medalhinha[j+1].bronze;
                        medalhinha[j+1].bronze = aux.bronze;

                        strcpy(aux.nome, medalhinha[j].nome);
                        strcpy(medalhinha[j].nome, medalhinha[j+1].nome);
                        strcpy(medalhinha[j+1].nome, aux.nome);
                    }
                    else if(medalhinha[j].bronze == medalhinha[j+1].bronze)
                    {
                        if(strcmp(medalhinha[j].nome,medalhinha[j+1].nome) > 0)
                        {
                            aux.ouro = medalhinha[j].ouro;
                            medalhinha[j].ouro = medalhinha[j+1].ouro;
                            medalhinha[j+1].ouro = aux.ouro;

                            aux.prata = medalhinha[j].prata;
                            medalhinha[j].prata = medalhinha[j+1].prata;
                            medalhinha[j+1].prata = aux.prata;

                            aux.bronze = medalhinha[j].bronze;
                            medalhinha[j].bronze = medalhinha[j+1].bronze;
                            medalhinha[j+1].bronze = aux.bronze;

                            strcpy(aux.nome, medalhinha[j].nome);
                            strcpy(medalhinha[j].nome, medalhinha[j+1].nome);
                            strcpy(medalhinha[j+1].nome, aux.nome);
                        }
                    }
                }
            }
        }
    }

    //printf("\n");
    for(i=0;i<n;i++)
        printf("%s %d %d %d\n",medalhinha[i].nome, medalhinha[i].ouro, medalhinha[i].prata, medalhinha[i].bronze);

	return 0;
}
