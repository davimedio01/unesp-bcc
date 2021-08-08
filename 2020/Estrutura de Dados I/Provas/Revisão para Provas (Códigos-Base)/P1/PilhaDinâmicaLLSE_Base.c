/**/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define ESC 27

//Estrutura LLSE da Pilha
typedef struct no *def_pilha;
struct no
{
     int info;
     def_pilha prox;
};

//Funções Básicas
int verificaVazia(def_pilha pilha)
{
     return (pilha == NULL);
}

void empilhar(def_pilha *pilha, int info)
{
     //Alocar memória
     def_pilha p = (def_pilha)malloc(sizeof(struct no));

     p->info = info;
     p->prox = (*pilha);
     (*pilha) = p;
}
int desempilhar(def_pilha *pilha, int *info)
{
     //Necessário verificar se pilha está vazia
     if (verificaVazia((*pilha)))
     {
          return 0;
     }

     (*info) = (*pilha)->info;
     def_pilha p = (*pilha);
     (*pilha) = (*pilha)->prox;
     free(p);

     return 1;
}

void mostrar(def_pilha pilha)
{
     if (verificaVazia(pilha))
     {
          printf("\nPilha vazia.\n\n");
          return;
     }

     printf("\nPilha Atual\n\n");
     while (pilha)
     {
          printf("%d\n", pilha->info);
          pilha = pilha->prox;
     }
}

int main()
{
     //Iniciando uma pilha
     def_pilha pilha1;
     pilha1 = NULL;

     //Menu
     int opc, info;
     char desempilha;
     while (opc != ESC)
     {
          printf("\nPilha Dinamica - LLSE\n\n");
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

               empilhar(&pilha1, info);
               printf("\n\nElemento empilhado com sucesso.\n\n");

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