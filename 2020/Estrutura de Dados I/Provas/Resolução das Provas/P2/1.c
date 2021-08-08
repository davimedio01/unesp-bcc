/**/

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define GRAU 5

//Estrutura de uma Árvore Genérica (Dinâmica) com GRAU 5
typedef struct no
{
     //Identificador do Elemento
     int id;

     //Filhos
     struct no *filhos[GRAU];
} * def_arvore;

//Funções Básicas
//Escopos


//Criação da Raiz
void criaRaiz(def_arvore *arvore)
{
     //Auxiliares
     int id, i;
     
     //Definição da Raiz
     id = 1;

     //Alocando espaço na memória para elemento
     (*arvore) = (def_arvore)malloc(sizeof(struct no));
     (*arvore)->id = id;
     //Definindo os Filhos da Raiz com Nulos
     for (i = 0; i < GRAU; i++)
     {
          (*arvore)->filhos[i] = NULL;
     }
}

//Criação dos Nós
void criaNos(def_arvore *arvore, int *id, int *aux_id)
{
     //Auxiliares
     int i;

     criaFilho(&(*arvore), id, aux_id);
     //Após criar os filhos desejados do nó, criar os filhos desses filhos...
     for (i = 0; i < GRAU; i++)
     {
          if ((*arvore)->filhos[i] != NULL)
          {
               (*id)++;
               criaNos(&((*arvore)->filhos[i]), &(*id), &(*aux_id));
          }
     }
}

//Criação dos Filhos
void criaFilho(def_arvore *arvore, int *id, int *aux_id)
{
     //Auxiliares
     int i, j, qtd;
     def_arvore q;

     //Verificando a quantidade desejada de filhos
     qtd = RetornaQtdFilhos((*id));

     //Atribuindo os filhos no nó
     for (i = 0; i < qtd; i++)
     {
          (*aux_id)++;

          //Atribuindo o filho
          q = (def_arvore)malloc(sizeof(struct no));
          q->id = (*aux_id);
          for (j = 0; j < GRAU; j++)
               q->filhos[j] = NULL; //Zerando filhos do filho
          (*arvore)->filhos[i] = q;
     }
}

//Mostrar a Árvore
void mostraArvore(def_arvore arvore, char raiz)
{
     //Verificando se é a raiz
     if (raiz == '1')
     {
          printf("\nRAIZ: %d\n", arvore->id);
     }
     else
     {
          printf("\nNO: %d\n", arvore->id);
     }

     //Mostrando filhos de cada nó
     mostraFilhosNo(arvore);
     //Avançando para os filhos
     int i;
     for (i = 0; i < GRAU; i++)
     {
          //Se existir
          if (arvore->filhos[i] != NULL)
          {
               mostraArvore(arvore->filhos[i], '0');
          }
     }
}
void mostraFilhosNo(def_arvore arvore)
{
     int i, cont = 0;
     for (i = 0; i < GRAU; i++)
     {
          if (arvore->filhos[i] != NULL)
          {
               printf("\tFILHO: %d\n", arvore->filhos[i]->id);
               cont = 1;
          }
     }
     if (cont == 0)
     {
          printf("\tNAO POSSUI FILHOS\n");
     }
     //printf("\n");
}

//Funções Geradoras
char *RetornaNome(int id)
{
     switch (id)
     {
     case 1:
          return "Lapiseira";
          break;
     case 2:
          return "Ponteira";
          break;
     case 3:
          return "Miolo";
          break;
     case 4:
          return "Presilha";
          break;
     case 5:
          return "Corpo Externo";
          break;
     case 6:
          return "Guia";
          break;
     case 7:
          return "Capa";
          break;
     case 8:
          return "Garra";
          break;
     case 9:
          return "Canudo";
          break;
     case 10:
          return "Borracha";
          break;
     case 11:
          return "Tinta";
          break;
     case 12:
          return "Plastico";
          break;
     case 13:
          return "Corante";
          break;
     case 14:
          return "Fio";
          break;
     case 15:
          return "Tira";
          break;
     }
}
int RetornaEstoque(int id)
{
     switch (id)
     {
     case 1:
          return 25;
          break;
     case 2:
          return 70;
          break;
     case 3:
          return 60;
          break;
     case 4:
          return 30;
          break;
     case 5:
          return 5;
          break;
     case 6:
          return 90;
          break;
     case 7:
          return 10;
          break;
     case 8:
          return 5;
          break;
     case 9:
          return 75;
          break;
     case 10:
          return 5;
          break;
     case 11:
          return 280;
          break;
     case 12:
          return 30;
          break;
     case 13:
          return 50;
          break;
     case 14:
          return 640;
          break;
     case 15:
          return 130;
          break;
     }
}

int RetornaQtdFilhos(int id)
{
     switch (id)
     {
     case 1:
          return 5;
          break;
     case 3:
          return 2;
          break;
     case 5:
          return 3;
          break;
     case 7:
          return 2;
          break;
     case 10:
          return 2;
          break;
     default:
          return 0;
          break;
     }
}

//Exercício 2
int RetornaID(char elemento[])
{
     if(stricmp(elemento, "Lapiseira") == 0)
     {
          return 1;
     }
     else if (stricmp(elemento, "Ponteira") == 0)
     {
          return 2;
     }
     else if (stricmp(elemento, "Miolo") == 0)
     {
          return 3;
     }
     else if (stricmp(elemento, "Presilha") == 0)
     {
          return 4;
     }
     else if (stricmp(elemento, "Corpo Externo") == 0)
     {
          return 5;
     }
     else if (stricmp(elemento, "Guia") == 0)
     {
          return 6;
     }
     else if (stricmp(elemento, "Capa") == 0)
     {
          return 7;
     }
     else if (stricmp(elemento, "Garra") == 0)
     {
          return 8;
     }
     else if (stricmp(elemento, "Canudo") == 0)
     {
          return 9;
     }
     else if (stricmp(elemento, "Borracha") == 0)
     {
          return 10;
     }
     else if (stricmp(elemento, "Tinta") == 0)
     {
          return 11;
     }
     else if (stricmp(elemento, "Plastico") == 0)
     {
          return 12;
     }
     else if (stricmp(elemento, "Corante") == 0)
     {
          return 13;
     }
     else if (stricmp(elemento, "Fio") == 0)
     {
          return 14;
     }
     else if (stricmp(elemento, "Tira") == 0)
     {
          return 15;
     }

     return -1;
}
void BuscaElemento(def_arvore arvore, char elemento[])
{
     if(arvore != NULL)
     {
          //Retornando a ID do elemento (facilitar)
          int id = RetornaID(elemento);
          if (arvore->id == id)
          {
               printf("\nElemento encontrado!\n\n");
               printf("ELemento: %s\n\n", RetornaNome(id));
               printf("Filhos:\n");

               int j;
               for (j = 0; j < GRAU; j++)
               {
                    if (arvore->filhos[j] != NULL)
                    {
                         printf("\t%s\n", RetornaNome(arvore->filhos[j]->id));
                    }
               }

               //Verificando e retornando filhos deste elemento
               MostraArvore(arvore, id);
               return;
          }

          //Avançando para os filhos
          int i;
          for (i = 0; i < GRAU; i++)
          {
               //Se existir
               if (arvore->filhos[i] != NULL)
               {
                    BuscaElemento(arvore->filhos[i], elemento);
               }
          }
     }
}
void MostraArvore(def_arvore arvore, int id)
{
     printf("\nElemento:%s\n", RetornaNome(id));

     //Mostrando os filhos de cada nó
     MostraFilhosNo(arvore);
     //Avançando para os filhos
     int i;
     for (i = 0; i < GRAU; i++)
     {
          //Se existir
          if (arvore->filhos[i] != NULL)
          {
               MostraArvore(arvore->filhos[i], id);
          }
     }
}
void MostraFilhosNo(def_arvore arvore)
{
     int i;
     for (i = 0; i < GRAU; i++)
     {
          if (arvore->filhos[i] != NULL)
          {
               printf("\tSub-Elemento: %d\n", RetornaNome(arvore->filhos[i]->id));
          }
     }
}

//Exercício 3
void BuscaEstoque(def_arvore arvore, char elemento[])
{
     if(arvore != NULL)
     {
          //Retornando a ID do elemento (facilitar)
          int id = RetornaID(elemento);
          if (arvore->id == id)
          {
               printf("\nElemento encontrado!\n\n");
               printf("ELemento: %s\n\n", RetornaNome(id));
               printf("Estoque Disp.: %d\n\n", RetornaEstoque(id));

               return;
          }

          //Realizando a busca do elemento
          int i;
          for (i = 0; i < GRAU; i++)
          {
               //Se existir
               if (arvore->filhos[i] != NULL)
               {
                    RetornaComponentes(arvore->filhos[i], elemento);
               }
          }
     }
}

int main()
{

     //Declaração da Árvore
     def_arvore arvore;

     //Criação da Raiz da Árvore
     criaRaiz(&arvore);

     //Criação dos Filhos (Início: Raiz)
     int id = 1, aux_id = 1;
     criaNos(&arvore, &id, &aux_id);

     printf("\nARVORE GENERICA DINAMICA - GRAU %d\n\n", GRAU);
     printf("\tARVORE ATUAL\n\n");
     mostraArvore(arvore, '1');

     printf("\n\n");
     system("pause");
     system("cls");
     return 0;
}