/**/

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define GRAU 3

//Estrutura da Árvore Genérica de Grau Pré-Definido (> 2)
typedef struct no
{
     int info;

     //Filhos
     struct no *filhos[GRAU];
} * def_arvore;

//Funções Básicas
//Escopos
void criaRaiz(def_arvore *arvore);
void criaNos(def_arvore *arvore, char raiz);
void criaFilho(def_arvore *arvore);
void mostraArvore(def_arvore arvore, char raiz);
void mostraFilhosNo(def_arvore arvore);

//Criação da Raiz
void criaRaiz(def_arvore *arvore)
{
     printf("\nARVORE GENERICA DINAMICA - GRAU %d\n\n", GRAU);
     printf("\tCRIACAO DA RAIZ\n\n");
     //Auxiliares
     int info, i;
     //Definição da Raiz
     printf("\nDigite o valor inteiro da raiz: ");
     scanf("%d", &info);

     //Alocando espaço na memória para elemento
     (*arvore) = (def_arvore)malloc(sizeof(struct no));
     (*arvore)->info = info;
     //Definindo os Filhos da Raiz com Nulos
     for (i = 0; i < GRAU; i++)
     {
          (*arvore)->filhos[i] = NULL;
     }
}

//Criação dos Nós
void criaNos(def_arvore *arvore, char raiz)
{
     system("cls");
     printf("\nARVORE GENERICA DINAMICA - GRAU %d\n\n", GRAU);
     if (raiz == '1')
     {
          printf("A RAIZ '%d' TEM FILHOS? (S/N)\n", (*arvore)->info);
     }
     else
     {
          printf("O NO '%d' TEM FILHOS? (S/N)\n", (*arvore)->info);
     }

     //Auxiliares
     char opc;
     int i;

     //Opção
     do
     {
          opc = toupper(getch());
     } while (opc != 'S' && opc != 'N');

     //Caso tenha filhos, criar
     if (opc == 'S')
     {
          criaFilho(&(*arvore));
          //Após criar os filhos desejados do nó, criar os filhos desses filhos...
          for (i = 0; i < GRAU; i++)
          {
               if ((*arvore)->filhos[i] != NULL)
                    criaNos(&((*arvore)->filhos[i]), '0');
               system("cls");
          }
     }
}

//Criação dos Filhos
void criaFilho(def_arvore *arvore)
{
     printf("\n\nCRIACAO DOS FILHOS DE '%d'\n\n", (*arvore)->info);

     //Auxiliares
     int i, j, qtd, info;
     def_arvore q;

     //Verificando a quantidade desejada de filhos
     printf("Digite a quantidade de filhos (Min. 1/Max %d): ", GRAU);
     do
     {
          scanf("%d", &qtd);
     } while (qtd > GRAU || qtd < 1);

     //Atribuindo os filhos no nó
     for (i = 0; i < qtd; i++)
     {
          printf("\n\nFilho %d: ", i + 1);
          scanf("%d", &info);

          //Atribuindo o filho
          q = (def_arvore)malloc(sizeof(struct no));
          q->info = info;
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
          printf("\nRAIZ: %d\n", arvore->info);
     }
     else
     {
          printf("\nNO: %d\n", arvore->info);
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
               printf("\tFILHO: %d\n", arvore->filhos[i]->info);
               cont = 1;
          }
     }
     if (cont == 0)
     {
          printf("\tNAO POSSUI FILHOS\n");
     }
     //printf("\n");
}

//Rotina que devolve qtd de nós que são menores que a raiz
void QtdNosMenorRaiz(def_arvore arvore, int *qtd_nos, int raiz)
{
     int i;
     for(i = 0; i < GRAU; i++)
     {
          if(arvore->filhos[i] != NULL)
          {
               QtdNosMenorRaiz(arvore->filhos[i], &(*qtd_nos), raiz);
          }
     }

     //Caso seja menor que a raiz
     if(arvore->info < raiz)
     {
          (*qtd_nos)++;
     }
}

int main()
{

     //Declaração da Árvore
     def_arvore arvore;

     //Criação da Raiz da Árvore
     criaRaiz(&arvore);

     //Criação dos Filhos (Início: Raiz)
     criaNos(&arvore, '1');

     //Mostrando a Árvore
     printf("\nARVORE GENERICA DINAMICA - GRAU %d\n\n", GRAU);
     printf("\tARVORE ATUAL\n\n");
     mostraArvore(arvore, '1');
     printf("\n\n");

     //Qtd de nós que possuem ao menos um filho
     int qtd_nos = 0;
     QtdNosMenorRaiz(arvore, &qtd_nos, arvore->info);
     printf("Qtd de nos sao menores que a raiz: %d\n\n", qtd_nos);

     system("pause");
     system("cls");
     return 0;
}