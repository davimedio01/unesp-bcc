/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define MAX 5

//Verificar se a Pilha está vazia
int verificaVazia(float pilha[], int topo)
{
    if (topo == -1)
        return 1;
    return 0;
}

//Função para visualizar as pilhas antes e após a operação
void Visualizar(float pilha[], int topo, int opc)
{
    if (verificaVazia(pilha, topo))
    {
        printf("\nPilha %d vazia\n\n", opc);
    }
    else
    {
        printf("\nPilha %d\n\n", opc);
        int i;
        for (i = topo; i >= 0; i--)
        {
            printf("%.1f\n", pilha[i]);
        }
        printf("\n");
    }
}

//Função Principal da Concatenação de Pilhas
void ConcatenaPilhas(float *pilha1, float *pilha2, int *topo1, int *topo2){

    //Auxiliar (Não ferir conceito de pilha)
    float pilha_aux[MAX];
    int topoaux = -1;

    //Colocando os elementos da pilha 2 na pilha auxiliar
    while((*topo2) != -1){
        pilha_aux[++(topoaux)] = pilha2[(*topo2)--];
    }

    //Realizando a concatenação (de fato)
    while(topoaux != -1){
        pilha1[++(*topo1)] = pilha_aux[(topoaux)--];
    }
}


int main(){

    //Definição das Pilhas e seus Topos
    //Pilha 1
    float pilha1[MAX] = {2.5, 7.8, 5.9};
    int topo1 = 2;
    //Pilha 2
    float pilha2[] = {6.8, 4.7};
    int topo2 = 1;

    printf("\nPilhas: Antes da Concatenacao\n\n");
    Visualizar(pilha1, topo1, 1);
    Visualizar(pilha2, topo2, 2);
    system("pause");
    system("cls");

    printf("\nRealizando a Concatenacao das Pilhas...\n");
    Sleep(3000);
    ConcatenaPilhas(pilha1, pilha2, &topo1, &topo2);
    printf("\n\nConcatenacao realizada com sucesso!\n\n");
    system("pause");
    system("cls");

    printf("\nPilhas: Apos a Concatenacao\n\n");
    Visualizar(pilha1, topo1, 1);
    Visualizar(pilha2, topo2, 2);

    return 0;

}