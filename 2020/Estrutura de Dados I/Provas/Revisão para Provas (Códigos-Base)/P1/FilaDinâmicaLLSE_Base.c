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
int verificaVazia(def_fila Inicio)
{
     return (Inicio == NULL);
}

void enfileirar(def_fila *Inicio, def_fila *Fim, int info)
{
     def_fila p = (def_fila)malloc(sizeof(struct no));
     p->info = info;
     p->prox = NULL;

     if ((*Fim) == NULL)
     {
          (*Inicio) = p;
     }
     else
     {
          (*Fim)->prox = p;
     }

     (*Fim) = p;
}
int desenfileirar(def_fila *Inicio, def_fila *Fim, int *info)
{
     if (verificaVazia((*Inicio)))
     {
          return 0;
     }

     (*info) = (*Inicio)->info;
     def_fila p = (*Inicio);
     (*Inicio) = (*Inicio)->prox;

     if ((*Inicio) == NULL)
     {
          (*Fim) = NULL;
     }
     free(p);

     return 1;
}

void mostrar(def_fila Inicio)
{
     if (verificaVazia(Inicio))
     {
          printf("\nFila vazia.\n\n");
          return;
     }

     printf("\nFila Atual\n\n");
     while (Inicio)
     {
          printf("%d ", Inicio->info);
          Inicio = Inicio->prox;
     }
     printf("\n");
}

int main()
{
     //Iniciando uma fila
     def_fila Inicio, Fim;
     Inicio = Fim = NULL;

     //Menu
     int opc, info;
     char desenfilera;
     while (opc != ESC)
     {
          printf("\nFila Dinamica - LLSE\n\n");
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

               enfileirar(&Inicio, &Fim, info);
               printf("\n\nElemento enfileirado com sucesso.\n\n");

               break;

          case 2:
               printf("\nDesenfileirar\n\n");
               printf("Deseja realmente desenfileirar o primeiro elemento? (S/N): ");
               desenfilera = toupper(getch());

               if (desenfilera == 'S')
               {
                    if (desenfileirar(&Inicio, &Fim, &info))
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
               mostrar(Inicio);
               printf("\n\n");
               break;
          }
          system("pause");
          system("cls");
     }

     return 0;
}