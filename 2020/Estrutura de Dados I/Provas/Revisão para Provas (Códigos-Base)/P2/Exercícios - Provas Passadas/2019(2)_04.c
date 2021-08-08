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
     int info;

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
     int info;
     printf("Digite o valor da raiz: ");
     scanf("%d", &info);

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
          printf("A RAIZ '%d' TEM FILHOS? (S/N)\n", (*arvore)->info);
     else
          printf("O NO '%d' TEM FILHOS? (S/N)\n", (*arvore)->info);

     //Opção
     char opc;
     do
     {
          opc = toupper(getch());
     } while (opc != 'S' && opc != 'N');

     //Caso tenha filhos, criar o da esquerda e direita
     if (opc == 'S')
     {
          printf("\n\nCRIACAO DOS FILHOS DE '%d'\n\n", (*arvore)->info);

          //Auxiliares
          def_arvore q;
          int info;

          //Esquerda
          printf("Entre com o valor do filho da ESQUERDA (-1 para cancelar): ");
          scanf("%d", &info);
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
          scanf("%d", &info);
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
          printf("\nRAIZ: %d\n", arvore->info);
     else
          printf("\nNO: %d\n", arvore->info);

     //Mostrando os filhos do nó atual
     if (arvore->esq != NULL)
          printf("\tFILHO (ESQUERDA): %d\n", arvore->esq->info);
     if (arvore->dir != NULL)
          printf("\tFILHO (DIREITA): %d\n", arvore->dir->info);
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
          printf("%d ", arvore->info);
          PreOrdem(arvore->esq);
          PreOrdem(arvore->dir);
     }
}
void EmOrdem(def_arvore arvore)
{
     if (arvore != NULL)
     {
          EmOrdem(arvore->esq);
          printf("%d ", arvore->info);
          EmOrdem(arvore->dir);
     }
}
void PosOrdem(def_arvore arvore)
{
     if (arvore != NULL)
     {
          PosOrdem(arvore->esq);
          PosOrdem(arvore->dir);
          printf("%d ", arvore->info);
     }
}

//Rotina do Exercício
void CalculaMultiplicaX(def_arvore arvore, float *resultado, int X)
{
     if(arvore != NULL)
     {
          if (arvore->esq != NULL && arvore->dir != NULL)
          {
               (*resultado) *= ((arvore->info) / X);
          }
     }
     
     if(arvore->esq != NULL)
     {
          CalculaMultiplicaX(arvore->esq, &(*resultado), X);
     }
     if(arvore->dir != NULL)
     {
          CalculaMultiplicaX(arvore->dir, &(*resultado), X);
     }
}

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

     printf("\n\n");

     //Calcular multiplicação dos elementos (que possuem dois filhos) dividos por X
     int X;
     float resultado = 1.0f;
     printf("\nDigite o valor de X: ");
     do{
          scanf("%d", &X);
     }while(X < 0);
     CalculaMultiplicaX(arvore, &resultado, X);
     printf("\nResultado da Rotina: %f\n\n", resultado);

     system("pause");
     system("cls");

     return 0;
}