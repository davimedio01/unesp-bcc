/**/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define ESC 27
#define MAX 5

//Método 1
//Estrutura da Fila
typedef struct
{
     int info[MAX];   //Elementos
     int inicio, fim; //Marcações
} def_fila;

//Funções Básicas
int verificaCheia(int fim)
{
     return (fim == MAX - 1);
}
int verificaVazia(int inicio, int fim)
{
     return (inicio == -1 || inicio == fim + 1);
}

int enfileirar(def_fila *fila, int info)
{
     //Verificação de fila cheia
     if (verificaCheia((*fila).fim))
     {
          return 0;
     }

     (*fila).info[++(*fila).fim] = info;

     if ((*fila).inicio == -1)
     {
          (*fila).inicio++;
     }

     return 1;
}
int desenfileirar(def_fila *fila, int *info)
{
     //Verificação de fila vazia
     if (verificaVazia((*fila).inicio, (*fila).fim))
     {
          return 0;
     }

     (*info) = (*fila).info[(*fila).inicio];
     (*fila).info[(*fila).inicio++] = -1;

     return 1;
}

void mostrar(def_fila fila)
{
     if (verificaVazia(fila.inicio, fila.fim))
     {
          printf("\nFila vazia.\n\n");
          return;
     }

     printf("\nFila Atual\n\n");
     int info;
     while (desenfileirar(&fila, &info))
     {
          printf("%d ", info);
     }
     printf("\n");
}

int main()
{
     //Iniciando uma fila
     def_fila fila1;
     fila1.inicio = fila1.fim = -1;

     //Menu
     int opc, info;
     char desenfilera;
     while (opc != ESC)
     {
          printf("\nFila Estatica\n\n");
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

               if (enfileirar(&fila1, info))
               {
                    printf("\n\nElemento enfileirado com sucesso.\n\n");
               }
               else
               {
                    printf("\n\nErro ao enfileirar elemento.\n\n");
               }

               break;

          case 2:
               printf("\nDesenfileirar\n\n");
               printf("Deseja realmente desenfileirar o primeiro elemento? (S/N): ");
               desenfilera = toupper(getch());

               if (desenfilera == 'S')
               {
                    if (desenfileirar(&fila1, &info))
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
               mostrar(fila1);
               printf("\n\n");
               break;
          }
          //Resetando fila
          if (verificaVazia(fila1.inicio, fila1.fim) && verificaCheia(fila1.fim))
          {
               fila1.inicio = fila1.fim = -1;
          }
          system("pause");
          system("cls");
     }

     return 0;
}