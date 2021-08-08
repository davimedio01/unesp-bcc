/**/

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

//Estrutura da Árvore Binária de Busca
typedef struct no{
     int info;

     //Esquerda e Direita
     struct no *esq;
     struct no *dir;
}*def_arvore;

//Funções Básicas
//Escopos
void InsereArvBinBusca(def_arvore *arvore, int info);
int RemoveTipo1_MenorDireta(def_arvore *arvore, int info);
int RemoveTipo2_MaiorEsquerda(def_arvore *arvore, int info);
void MostraArvore(def_arvore arvore, char raiz);
void PreOrdem(def_arvore arvore);
void EmOrdem(def_arvore arvore);
void PosOrdem(def_arvore arvore);
void RotinaMostrar(def_arvore arvore);
int BuscaElemento(def_arvore arvore, int busca);

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

//Funções de Remoção
//Tipo 1: Menor à Direta
int RemoveTipo1_MenorDireta(def_arvore *arvore, int info)
{
     /*
     p: percorrer a árvore em busca do elemento
     q: marcação do pai do elemento
     rp: relacionado ao tipo de remoção (marca o primeiro elemento)
     f: salva a posição da informação (para colocar o menor à direta ao remover)
     s: utilizado para percorrer e encontrar o menor elemento à direta de "p"
     */
     def_arvore p, q, rp, f, s;

     p = *arvore;
     q = NULL;

     //Buscando o elemento na árvore e salvando o seu antecessor
     while (p != NULL && p->info != info)
     {
          q = p;
          if (info < p->info)
               p = p->esq;
          else
               p = p->dir;
     }

     //Caso o elemento exista
     if (p != NULL)
     {
          //Marcação da existência de um filho
          if (p->esq == NULL)
               rp = p->dir;
          else if (p->dir == NULL)
               rp = p->esq;
          //Marcação para mais de um filho
          else
          {
               //Neste passo é realizado: marcação do elemento (para utilizar como antecessor), marcação do 1° elemento à direita (para buscar o menor)
               f = p;
               rp = p->dir;
               s = rp->esq;

               //Buscando o menor elemento à direita
               while (s != NULL)
               {
                    f = rp;
                    rp = s;
                    s = rp->esq;
               }

               //Caso o antecessor do menor elemento não seja o valor a ser removido, realizar operações para salvar os filhos
               if (f != p)
               {
                    f->esq = rp->dir;
                    rp->dir = p->dir;
               }
               rp->esq = p->esq;
          }

          //Raiz da árvore
          if (q == NULL)
               *arvore = rp;
          else
          {
               if (p == q->esq)
                    q->esq = rp;
               else
                    q->dir = rp;
          }
          free(p);
          return 1;
     }
     return 0;
}
//Tipo 2: Maior à Esquerda
int RemoveTipo2_MaiorEsquerda(def_arvore *arvore, int info)
{
     /*
     p: percorrer a árvore em busca do elemento
     q: marcação do pai do elemento
     rp: relacionado ao tipo de remoção (marca o primeiro elemento)
     f: salva a posição da informação (para colocar o maior à esquerda ao remover)
     s: utilizado para percorrer e encontrar o maior elemento à esquerda de "p"
     */
     def_arvore p, q, rp, f, s;

     p = *arvore;
     q = NULL;

     //Buscando o elemento na árvore e salvando o seu antecessor
     while (p != NULL && p->info != info)
     {
          q = p;
          if (info < p->info)
               p = p->esq;
          else
               p = p->dir;
     }

     //Caso o elemento exista
     if (p != NULL)
     {
          //Marcação da existência de um filho
          if (p->esq == NULL)
               rp = p->dir;
          else if (p->dir == NULL)
               rp = p->esq;
          //Marcação para mais de um filho
          else
          {
               //Neste passo é realizado: marcação do elemento (para utilizar como antecessor), marcação do 1° elemento à esquerda (para buscar o maior)
               f = p;
               rp = p->esq;
               s = rp->dir;

               //Buscando o maior elemento à esquerda
               while (s != NULL)
               {
                    f = rp;
                    rp = s;
                    s = rp->dir;
               }

               //Caso o antecessor do maior elemento não seja o valor a ser removido, realizar operações para salvar os filhos
               if (f != p)
               {
                    f->dir = rp->esq;
                    rp->esq = p->esq;
               }
               rp->dir = p->dir;
          }

          //Raiz da árvore
          if (q == NULL)
               *arvore = rp;
          else
          {
               if (p == q->esq)
                    q->esq = rp;
               else
                    q->dir = rp;
          }
          free(p);
          return 1;
     }
     return 0;
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

//Função de Busca (recursivo)
int BuscaElemento(def_arvore arvore, int busca)
{
     if(arvore == NULL)
          return 0;
     if(arvore->info == busca)
          return 1; //Elemento encontrado
     
     //Percorrer a Esquerda ou Direita
     if(busca < arvore->info)
          return BuscaElemento(arvore->esq, busca);
     if(busca > arvore->info)
          return BuscaElemento(arvore->dir, busca);
}

int main(){

     //Definição da(s) Árvore(s) Binária(s) de Busca
     def_arvore arvore = NULL;

     //Auxiliares
     char opc;
     int info;

     //Inserção na Árvore Binária de Busca
     do{
          printf("\nARVORE BINARIA DE BUSCA\n\n");
          printf("INSERCAO DE ELEMENTOS\n\n");
          printf("Digite o elemento positivo a ser inserido: ");
          do{
               scanf("%d", &info);
          }while(info < 0);

          InsereArvBinBusca(&arvore, info);

          printf("\n\nElemento inserido com sucesso!\n");
          printf("\nDeseja inserir outro elemento? (S/N)");
          do{
               opc = toupper(getch());
          }while(opc != 'S' && opc != 'N');
          system("cls");
     }while(opc == 'S');

     //Mostrando a Árvore Binária
     RotinaMostrar(arvore);
     printf("\n\n");
     system("pause");
     system("cls");

     //Remoção de Elementos - Tipo 1
     do{
          printf("\nARVORE BINARIA DE BUSCA\n\n");
          printf("REMOCAO DE ELEMENTOS - TIPO 1 (MENOR A DIREITA)\n\n");
          printf("Digite o elemento positivo a ser removido (-1 para sair): ");
          do
          {
               scanf("%d", &info);
          } while (info < -1);
          
          if(info == -1)
          {
               system("cls");
               break;
          }

          if(RemoveTipo1_MenorDireta(&arvore, info))
          {
               printf("\n\nElemento removido com sucesso!\n");
          }
          else
          {
               printf("\n\nElemento nao encontrado. Tente novamente.\n");
          }
          system("pause");
          system("cls");

          //Mostrando a Árvore Binária após remoção
          RotinaMostrar(arvore);
          printf("\n\n");
          system("pause");
          system("cls");

          printf("\n\nDeseja remover outro elemento? (S/N)");
          do
          {
               opc = toupper(getch());
          } while (opc != 'S' && opc != 'N');
          system("cls");
     }while(opc == 'S');

     //Remoção de Elementos - Tipo 2
     do
     {
          printf("\nARVORE BINARIA DE BUSCA\n\n");
          printf("REMOCAO DE ELEMENTOS - TIPO 2 (MAIOR A ESQUERDA)\n\n");
          printf("Digite o elemento positivo a ser removido (-1 para sair): ");
          do
          {
               scanf("%d", &info);
          } while (info < -1);

          if (info == -1)
          {
               system("cls");
               break;
          }

          if (RemoveTipo2_MaiorEsquerda(&arvore, info))
          {
               printf("\n\nElemento removido com sucesso!\n");
          }
          else
          {
               printf("\n\nElemento nao encontrado. Tente novamente.\n");
          }
          system("pause");
          system("cls");

          //Mostrando a Árvore Binária após remoção
          RotinaMostrar(arvore);
          printf("\n\n");
          system("pause");
          system("cls");

          printf("\n\nDeseja remover outro elemento? (S/N)");
          do
          {
               opc = toupper(getch());
          } while (opc != 'S' && opc != 'N');
          system("cls");
     } while (opc == 'S');

     return 0;
}