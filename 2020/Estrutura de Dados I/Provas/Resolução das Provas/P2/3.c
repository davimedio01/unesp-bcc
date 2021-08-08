/**/

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

//Estrutura da Árvore Binária de Busca
typedef struct no
{
     int info;

     //Esquerda e Direita
     struct no *esq;
     struct no *dir;
} * def_arvore;

//Funções Básicas
//Escopos
void InsereArvBinBusca(def_arvore *arvore, int info);
void MostraArvore(def_arvore arvore, char raiz);
void PreOrdem(def_arvore arvore);
void PosOrdem(def_arvore arvore);
void EmOrdem(def_arvore arvore);
void RotinaMostrar(def_arvore arvore);

void VerificaAlturaEsquerdoDireito(def_arvore arvore, int *esquerda, int *direita);
int DFS(def_arvore arvore, int altura);

//Inserção na Árvore Binária de Busca
void InsereArvBinBusca(def_arvore *arvore, int info)
{
     //Auxiliar
     def_arvore aux;

     //Caso o elemento atual seja null, alocar
     if ((*arvore) == NULL)
     {
          aux = (def_arvore)malloc(sizeof(struct no));
          aux->info = info;
          aux->dir = aux->esq = NULL;
          (*arvore) = aux;
     }
     else //Do contrário, verificar o local para inserção
     {
          if ((*arvore)->info > info)
               InsereArvBinBusca(&((*arvore)->esq), info);
          else if ((*arvore)->info < info)
               InsereArvBinBusca(&((*arvore)->dir), info);
     }
}

//Mostrar a Árvore Binária de Busca
void MostraArvore(def_arvore arvore, char raiz)
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
          MostraArvore(arvore->esq, 0);
     if (arvore->dir != NULL)
          MostraArvore(arvore->dir, 0);
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

void RotinaMostrar(def_arvore arvore)
{
     printf("\nARVORE BINARIA DE BUSCA\n\n");
     printf("\tARVORE ATUAL\n\n");
     MostraArvore(arvore, '1');
     printf("\n\n");

     //Mostrando percursos
     printf("\tPERCURSOS\n\n");
     printf("PRE-ORDEM: ");
     PreOrdem(arvore);

     printf("\n\nEM-ORDEM: ");
     EmOrdem(arvore);

     printf("\n\nPOS-ORDEM: ");
     PosOrdem(arvore);
}

/////////////////////////////////////
//Rotina que identifica a altura do lado direito e esquerdo
void VerificaAlturaEsquerdoDireito(def_arvore arvore, int *esquerda, int *direita)
{
     if(arvore != NULL)
     {
          (*esquerda) = RetornaAltura(arvore->esq, 0);
          (*direita) = RetornaAltura(arvore->dir, 0);
     }
}

//Função para Buscar a Altura
int RetornaAltura(def_arvore arvore, int altura)
{
     //Caso chegue no elemento nulo, retorna o valor máximo que encontrou
     if(arvore == NULL){
          return altura;
     }

     //Percorrendo a árvore
     int esq, dir;
     esq = RetornaAltura(arvore->esq, altura + 1);
     dir = RetornaAltura(arvore->dir, altura + 1);

     //Retorna o valor máximo
     return ((esq > dir) ? esq : dir);
}
/////////////////////////////////////

int main()
{

     //Definição da(s) Árvore(s) Binária(s) de Busca
     def_arvore arvore = NULL;

     //Auxiliares
     char opc;
     int info;

     //Inserção na Árvore Binária de Busca
     do
     {
          printf("\nARVORE BINARIA DE BUSCA\n\n");
          printf("INSERCAO DE ELEMENTOS\n\n");
          printf("Digite o elemento positivo a ser inserido: ");
          do
          {
               scanf("%d", &info);
          } while (info < 0);

          InsereArvBinBusca(&arvore, info);

          printf("\n\nElemento inserido com sucesso!\n");
          printf("\nDeseja inserir outro elemento? (S/N)");
          do
          {
               opc = toupper(getch());
          } while (opc != 'S' && opc != 'N');
          system("cls");
     } while (opc == 'S');

     //Mostrando a Árvore Binária
     RotinaMostrar(arvore);
     
     /////////////////////////////////////
     int esquerda, direita;
     esquerda = direita = 0;

     VerificaAlturaEsquerdoDireito(arvore, &esquerda, &direita);

     printf("\n\nALTURA DO LADO ESQUERDO: %d", esquerda);
     printf("\n\nALTURA DO LADO DIREITO: %d", direita);
     /////////////////////////////////////
     printf("\n\n");
     system("pause");
     system("cls");

     return 0;
}