/**/

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

//Estrutura da Árvore Binária
typedef struct no
{
     float info;

     //Esquerda e Direita
     struct no *esq;
     struct no *dir;
} * def_arvore;

//Funções Básicas
//Escopos
void criaRaiz(def_arvore *arvore);
void criaNos(def_arvore *arvore, char raiz);
void criaFilho(def_arvore *arvore);
void mostraArvore(def_arvore arvore, char raiz);

//Criação da Raiz
void criaRaiz(def_arvore *arvore)
{
     printf("\nARVORE BINARIA\n\n");
     printf("\tCRIACAO DA RAIZ\n\n");

     //Informação
     float info;
     printf("Digite o valor da raiz: ");
     scanf("%f", &info);

     //Iniciando a árvore
     (*arvore) = (def_arvore)malloc(sizeof(struct no));
     (*arvore)->info = info;
     (*arvore)->dir = NULL;
     (*arvore)->esq = NULL;
}

//Criação dos Nós
void criaNos(def_arvore *arvore, char raiz)
{
     system("cls");
     printf("\nARVORE BINARIA\n\n");
     if (raiz == '1')
          printf("A RAIZ '%.0f' TEM FILHOS? (S/N)\n", (*arvore)->info);
     else
          printf("O NO '%.0f' TEM FILHOS? (S/N)\n", (*arvore)->info);

     //Opção
     char opc;
     do
     {
          opc = toupper(getch());
     } while (opc != 'S' && opc != 'N');

     //Caso tenha filhos, criar o da esquerda e direita
     if (opc == 'S')
     {
          printf("\n\nCRIACAO DOS FILHOS DE '%.0f'\n\n", (*arvore)->info);

          //Auxiliares
          def_arvore q;
          float info;

          //Esquerda
          printf("Entre com o valor do filho da ESQUERDA (-1 para cancelar): ");
          scanf("%f", &info);
          if (info != -1)
          {
               q = (def_arvore)malloc(sizeof(struct no));
               q->info = info;
               q->dir = NULL;
               q->esq = NULL;
               (*arvore)->esq = q;
          }
          //Direita
          printf("Entre com o valor do filho da DIREITA (-1 para cancelar): ");
          scanf("%f", &info);
          if (info != -1)
          {
               q = (def_arvore)malloc(sizeof(struct no));
               q->info = info;
               q->dir = NULL;
               q->esq = NULL;
               (*arvore)->dir = q;
          }

          //Configurando os filhos...
          if ((*arvore)->esq != NULL)
               criaNos(&((*arvore)->esq), '0');
          if ((*arvore)->dir != NULL)
               criaNos(&((*arvore)->dir), '0');
     }
     system("cls");
}

//Mostrar a Árvore Binária
void mostraArvore(def_arvore arvore, char raiz)
{
     //Verificando se é a raiz
     if (raiz == '1')
          printf("\nRAIZ: %.0f\n", arvore->info);
     else
          printf("\nNO: %.0f\n", arvore->info);

     //Mostrando os filhos do nó atual
     if (arvore->esq != NULL)
          printf("\tFILHO (ESQUERDA): %.0f\n", arvore->esq->info);
     if (arvore->dir != NULL)
          printf("\tFILHO (DIREITA): %.0f\n", arvore->dir->info);
     if (arvore->esq == NULL && arvore->dir == NULL)
          printf("\tNAO POSSUI FILHOS\n");

     //Avançando nos filhos (pré-ordem)
     if (arvore->esq != NULL)
          mostraArvore(arvore->esq, 0);
     if (arvore->dir != NULL)
          mostraArvore(arvore->dir, 0);
}

//Funções de Percurso: Pré-Ordem, Em-Ordem, Pós-Ordem
void PreOrdem(def_arvore arvore)
{
     if (arvore != NULL)
     {
          printf("%.0f ", arvore->info);
          PreOrdem(arvore->esq);
          PreOrdem(arvore->dir);
     }
}
void EmOrdem(def_arvore arvore)
{
     if (arvore != NULL)
     {
          EmOrdem(arvore->esq);
          printf("%.0f ", arvore->info);
          EmOrdem(arvore->dir);
     }
}
void PosOrdem(def_arvore arvore)
{
     if (arvore != NULL)
     {
          PosOrdem(arvore->esq);
          PosOrdem(arvore->dir);
          printf("%.0f ", arvore->info);
     }
}

////////////////////////////////////////
//Letra A
void MediaNosDoisFilhos(def_arvore arvore, float *resultado, float *media)
{
     if(arvore != NULL)
     {
          //Caso existam os dois filhos
          if (arvore->esq != NULL && arvore->dir != NULL)
          {
               (*resultado) += (arvore->info);
               (*media)++;
          }

          //Percorrendo a árvore
          if(arvore->esq != NULL)
          {
               MediaNosDoisFilhos(arvore->esq, &(*resultado), &(*media));
          }
          if(arvore->dir != NULL)
          {
               MediaNosDoisFilhos(arvore->dir, &(*resultado), &(*media));
          }
     }
    
}

//Letra B
void DivisaoPrimeiroSegundoFilho(def_arvore arvore)
{
     if (arvore != NULL)
     {
          //Condições do exercício
          if (arvore->esq != NULL && arvore->dir != NULL)
          {
               printf("NO '%.0f': %.2f\n", arvore->info, (arvore->esq->info / arvore->dir->info));
          }
          else if(arvore->esq == NULL && arvore->dir == NULL)
          {
               printf("NO '%.0f': 0\n", arvore->info);
          }
          else if(arvore->esq != NULL || arvore->dir != NULL)
          {
               if(arvore->esq != NULL)
                    printf("NO '%.0f': %.0f\n", arvore->info, arvore->esq->info);
               else if(arvore->dir != NULL)
                    printf("NO '%.0f': %.0f\n", arvore->info, arvore->dir->info);
          }

          //Percorrendo a árvore
          if (arvore->esq != NULL)
          {
               DivisaoPrimeiroSegundoFilho(arvore->esq);
          }
          if (arvore->dir != NULL)
          {
               DivisaoPrimeiroSegundoFilho(arvore->dir);
          }
     }
}

////////////////////////////////////////

int main()
{

     //Definição da(s) Árvore(s) Binária(s)
     def_arvore arvore;

     //Criação da(s) Raíz(es)
     criaRaiz(&arvore);
     //Criação do(s) Filho(s)
     criaNos(&arvore, '1');

     //Mostrando a Árvore Binária
     printf("\nARVORE BINARIA\n\n");
     printf("\tARVORE ATUAL\n\n");
     mostraArvore(arvore, '1');
     printf("\n\n");

     //Mostrando percursos
     printf("\tPERCURSOS\n\n");
     printf("PRE-ORDEM: ");
     PreOrdem(arvore);

     printf("\n\nEM-ORDEM: ");
     EmOrdem(arvore);

     printf("\n\nPOS-ORDEM: ");
     PosOrdem(arvore);

     ////////////////////////////////////////
     //Letra A
     float letraA = 0.0f, cont_media = 0.0f;
     MediaNosDoisFilhos(arvore, &letraA, &cont_media);
     printf("\n\n\nLETRA A: %.1f\n", (letraA / cont_media));

     //Letra B
     printf("\nLETRA B\n\n");
     DivisaoPrimeiroSegundoFilho(arvore);
     ////////////////////////////////////////

     printf("\n\n");
     system("pause");
     system("cls");

     return 0;
}