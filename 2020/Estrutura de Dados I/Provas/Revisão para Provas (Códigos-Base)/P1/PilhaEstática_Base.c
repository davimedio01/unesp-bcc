/**/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define ESC 27
#define MAX 5

//Estrutura da Pilha
typedef struct
{
     int info[MAX]; //Informação
     int topo;      //Marcação do Topo da Pilha
} def_pilha;

//Funções Básicas
int verificaCheia(int topo)
{
     return (topo == MAX - 1);
}
int verificaVazia(int topo)
{
     return (topo == -1);
}

int empilhar(def_pilha *pilha, int info)
{
     //Necessário verificar se está cheia
     if (verificaCheia(pilha->topo))
     {
          return 0;
     }

     //Aumentar o topo e inserir
     (*pilha).info[++(*pilha).topo] = info;

     return 1;
}
int desempilhar(def_pilha *pilha, int *info)
{
     //Necessário verificar se está vazia
     if (verificaVazia(pilha->topo))
     {
          return 0;
     }

     //Remover e decrementar o topo
     (*info) = (*pilha).info[(*pilha).topo];
     (*pilha).info[(*pilha).topo] = -1; //Marcação de elemento nulo
     (*pilha).topo--;

     return 1;
}

void mostrar(def_pilha pilha)
{
     if (verificaVazia(pilha.topo))
     {
          printf("\nPilha vazia.\n\n");
          return;
     }

     printf("\nPilha Atual\n\n");
     int info;
     while (desempilhar(&pilha, &info))
     {
          printf("%d\n", info);
     }
}

int main()
{

     //Iniciando uma pilha
     def_pilha pilha1;
     pilha1.topo = -1;

     //Menu
     int opc, info;
     char desempilha;
     while (opc != ESC)
     {
          printf("\nPilha Estatica\n\n");
          printf("1 - Empilhar\n\n");
          printf("2 - Desempilhar\n\n");
          printf("3 - Visualizar\n\n\n");
          printf("27 - Sair\n\n");
          printf("Opcao: ");
          scanf("%d", &opc);
          system("cls");
          if (opc == ESC)
          {
               break;
          }

          switch (opc)
          {
          case 1:
               printf("\nEmpilhar\n\n");
               printf("Digite o elemento: ");
               scanf("%d", &info);

               if (empilhar(&pilha1, info))
               {
                    printf("\n\nElemento empilhado com sucesso.\n\n");
               }
               else
               {
                    printf("\n\nErro ao empilhar elemento.\n\n");
               }
               break;

          case 2:
               printf("\nDesempilhar\n\n");
               printf("Deseja realmente desempilhar o ultimo elemento? (S/N): ");
               desempilha = toupper(getch());

               if (desempilha == 'S')
               {
                    if (desempilhar(&pilha1, &info))
                    {
                         printf("\n\nElemento '%d' desempilhado com sucesso.\n\n", info);
                    }
                    else
                    {
                         printf("\n\nErro ao desempilhar elemento.\n\n");
                    }
               }
               break;

          case 3:
               mostrar(pilha1);
               printf("\n\n");
               break;
          }
          system("pause");
          system("cls");
     }

     return 0;
}