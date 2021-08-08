/**/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define ESC 27

//Estrutura da Fila
typedef struct no *def_fila;
struct no
{
     int info;
     def_fila prox;
};

//Funções Básicas
int verificaVazia(def_fila Fim)
{
     return (Fim == NULL);
}

void enfileirar(def_fila *Fim, int info)
{
     def_fila p = (def_fila)malloc(sizeof(struct no));
     p->info = info;

     if ((*Fim) == NULL)
     {
          (*Fim) = p;
     }
     else
     {
          p->prox = (*Fim)->prox;
     }
     (*Fim)->prox = p;
     (*Fim) = p;
}
int desenfileirar(def_fila *Fim, int *info)
{
     if (verificaVazia((*Fim)))
     {
          return 0;
     }

     (*info) = (*Fim)->prox->info;
     def_fila p = (*Fim)->prox;

     if (p == (*Fim))
     {
          (*Fim) = NULL;
     }
     else
     {
          (*Fim)->prox = p->prox;
     }
     free(p);
     return 1;
}

void mostrar(def_fila Fim)
{
     if (verificaVazia(Fim))
     {
          printf("\nFila vazia.\n\n");
          return;
     }

     printf("\nFila Atual\n\n");
     def_fila p = Fim->prox;
     do
     {
          printf("%d ", p->info);
          p = p->prox;
     } while (p != Fim->prox);
}

int main()
{
     //Iniciando uma fila
     def_fila Fim = NULL;

     //Menu
     int opc, info;
     char desenfilera;
     while (opc != ESC)
     {
          printf("\nFila Dinamica - LCSE\n\n");
          printf("1 - Enfileirar\n\n");
          printf("2 - Desenfileirar\n\n");
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
               printf("\nEnfileirar\n\n");
               printf("Digite o elemento: ");
               scanf("%d", &info);

               enfileirar(&Fim, info);
               printf("\n\nElemento enfileirado com sucesso.\n\n");

               break;

          case 2:
               printf("\nDesenfileirar\n\n");
               printf("Deseja realmente desenfileirar o primeiro elemento? (S/N): ");
               desenfilera = toupper(getch());

               if (desenfilera == 'S')
               {
                    if (desenfileirar(&Fim, &info))
                    {
                         printf("\n\nElemento '%d' desenfileirado com sucesso.\n\n", info);
                    }
                    else
                    {
                         printf("\n\nErro ao desenfileirar elemento.\n\n");
                    }
               }
               break;

          case 3:
               mostrar(Fim);
               printf("\n\n");
               break;
          }
          system("pause");
          system("cls");
     }

     return 0;
}