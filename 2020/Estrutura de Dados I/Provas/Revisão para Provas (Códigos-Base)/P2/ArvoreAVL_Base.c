/*
*****INSERÇÃO DE ELEMENTOS*****

Constata-se facilmente que a árvore se torna desbalanceada apenas se o nó recém-inserido é um
descendente esquerdo de um nó que tinha anteriormente um balanceamento –1 (já que a subárvore
esquerda já era maior e ficou maior ainda). O mesmo acontece se o nó recém-inserido é um
descendente direito de um nó que tinha anteriormente um balanceamento de 1.
------------------------------------------------------------------------------------------------------
*****REMOÇÃO DE ELEMENTOS*****

A árvore pode ficar desbalanceada quando um nó à esquerda for removido e a remoção desse elemento
fizer com que a subárvore esquerda encolha, fazendo com que o lado direito da árvore fique maior, e
assim o balanço da árvore passe a valer 2. Quando isso ocorrer tem-se de fazer rotações à esquerda
(simples ou dupla) para balancear a árvore novamente.
     OU
A árvore pode ficar desbalanceada quando um nó a direita for removido e a remoção desse elemento
fizer com que a subárvore direita encolha, fazendo com que o lado esquerdo da árvore fique maior, e
assim o balanço da árvore passe a valer -2. Quando isso ocorrer faz-se rotações à direita (simples ou
dupla) para balancear a árvore novamente.
*/

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

//Estrutuda da Árvore AVL
typedef struct no{
     int info;

     //Balanceamento
     int balanco;

     //Esquerda e Direita
     struct no *esq;
     struct no *dir;
}*def_arvore;

//Funções Básicas
//Escopos
void InsereArvoreAVL(def_arvore *arvore, int info, int *peso);
void RotacaoDireita(def_arvore *no, int *peso);
void RotacaoEsquerda(def_arvore *no, int *peso);
int RemoveAVL(def_arvore *arvore, int info, int *peso);
void BuscaMenorDireitaRemocao(def_arvore *p, def_arvore *q, int *peso);
void MostraArvore(def_arvore arvore, char raiz);
void PreOrdem(def_arvore arvore);
void PosOrdem(def_arvore arvore);
void RotinaMostrar(def_arvore arvore);
void EmOrdem(def_arvore arvore);

//Inserção na Árvore AVL
void InsereArvoreAVL(def_arvore *arvore, int info, int *peso)
{
     //Auxiliar
     def_arvore aux;

     //Caso o elemento atual seja null, alocar
     if ((*arvore) == NULL)
     {
          aux = (def_arvore)malloc(sizeof(struct no));
          aux->info = info;
          aux->dir = aux->esq = NULL;
          aux->balanco = 0;
          (*arvore) = aux;
          (*peso) = 1;
     }
     else //Do contrário, verificar o local para inserção
     {
          if((*arvore)->info == info)
          {
               printf("\nElemento ja inserido.\n");
          }
          else if ((*arvore)->info > info)
          {
               InsereArvoreAVL(&((*arvore)->esq), info, &(*peso));
               
               //Verificando balanceamento
               if ((*peso) == 1)
               {
                    switch((*arvore)->balanco)
                    {
                         case 1:
                              //Balanceado
                              (*arvore)->balanco = 0;
                              (*peso) = 0;
                              break;

                         case 0:
                              //Desbalanceado
                              (*arvore)->balanco = -1;
                              break;
                         
                         case -1:
                              //Rebalancear (Esquerda)
                              RotacaoEsquerda(arvore, peso);
                              break;
                    }
               }
          }
          else if ((*arvore)->info < info)
          {
               InsereArvoreAVL(&((*arvore)->dir), info, &(*peso));

               //Verificando balanceamento
               if ((*peso) == 1)
               {
                    switch ((*arvore)->balanco)
                    {
                         case -1:
                              //Balanceado
                              (*arvore)->balanco = 0;
                              (*peso) = 0;
                              break;

                         case 0:
                              //Desbalanceado
                              (*arvore)->balanco = 1;
                              break;

                         case 1:
                              //Rebalencear (Direita)
                              RotacaoDireita(arvore, peso);
                              break;
                    }
               }
          }
     }
}

//Rebalanceamento: Rotações
//Rotações Direita
void RotacaoDireita(def_arvore *no, int *peso)
{
     def_arvore q, r;

     switch ((*no)->balanco)
     {
     //1 e 0: trocar balanço, porém equilibrado
     case 1:
          (*no)->balanco = 0;
          break;
     case 0:
          (*no)->balanco = 1;
          (*peso) = 0;
          break;
     case -1:
          //Rotacionar
          q = (*no)->esq;

          //Rotação Simples Direita
          if (q->balanco <= 0)
          {
               (*no)->esq = q->dir;
               q->dir = (*no);
               if (q->balanco == 0)
               {
                    (*no)->balanco = -1;
                    q->balanco = 1;
                    (*peso) = 0;
               }
               else
               {
                    (*no)->balanco = 0;
                    q->balanco = 0;
               }
               (*no) = q;
          }
          //Rotação Dupla Direita
          else
          {
               r = q->dir;
               q->dir = r->esq;
               r->esq = q;
               (*no)->esq = r->dir;
               r->dir = (*no);

               //Trocando balanços
               if (r->balanco == -1)
                    (*no)->balanco = 1;
               else
                    (*no)->balanco = 0;

               if (r->balanco == 1)
                    q->balanco = 1;
               else
                    q->balanco = 0;

               (*no) = r;
               r->balanco = 0;
          }
          break;
     }
}

//Rotações Esquerda
void RotacaoEsquerda(def_arvore *no, int *peso)
{
     def_arvore q, r;

     switch((*no)->balanco)
     {
          //-1 e 0: trocar balanço, porém equilibrado
          case -1:
               (*no)->balanco = 0;
               break;
          case 0:
               (*no)->balanco = 1;
               (*peso) = 0;
               break;
          case 1:
               //Rotacionar
               q = (*no)->dir;

               //Rotação Simples Esquerda
               if(q->balanco >= 0)
               {
                    (*no)->dir = q->esq;
                    q->esq = (*no);
                    if(q->balanco == 0)
                    {
                         (*no)->balanco = 1;
                         q->balanco = -1;
                         (*peso) = 0;
                    }
                    else
                    {
                         (*no)->balanco = 0;
                         q->balanco = 0;
                    }
                    (*no) = q;
               }
               //Rotação Dupla Esquerda
               else
               {
                    r = q->esq;
                    q->esq = r->dir;
                    r->dir = q;
                    (*no)->dir = r->esq;
                    r->esq = (*no);

                    //Trocando balanços
                    if(r->balanco == 1)
                         (*no)->balanco = 1;
                    else
                         (*no)->balanco = 0;
                    
                    if(r->balanco == -1)
                         q->balanco = 1;
                    else
                         q->balanco = 0;
                    
                    (*no) = r;
                    r->balanco = 0;
               }
               break;
     }
}

//Remoção de Elemento
int RemoveAVL(def_arvore *arvore, int info, int *peso)
{
     def_arvore p;

     //Elemento não existe na árvore
     if((*arvore) == NULL)
     {
          return 0;
     }
     //Buscando elemento e verificando balanceamento quando a função retornar
     else if((*arvore)->info > info)
     {
          RemoveAVL(&((*arvore)->esq), info, &(*peso));
          
          //Rotação à Esquerda
          if((*peso) == 1)
               RotacaoEsquerda(arvore, peso);
     }
     else if((*arvore)->info < info)
     {
          RemoveAVL(&((*arvore)->dir), info, &(*peso));

          //Rotação à Direita
          if ((*peso) == 1)
               RotacaoDireita(arvore, peso);
     }
     //Elemento encontrado
     else
     {
          p = (*arvore);

          //Verificando se há filhos
          if (p->dir == NULL)
          {
               (*arvore) = p->esq;
               (*peso) = 1;
          }
          else if (p->esq == NULL)
          {
               (*arvore) = p->dir;
               (*peso) = 1;
          }
          //Mais de dois filhos, necessário manipular
          else
          {
               //Utilização do menor à direita
               BuscaMenorDireitaRemocao(&p, &(p->esq), peso);

               //Rotação à Esquerda
               if((*peso) == 1)
                    RotacaoEsquerda(arvore, peso);
          }
          

          return 1;
     }
}
void BuscaMenorDireitaRemocao(def_arvore *p, def_arvore *q, int *peso)
{
     //Percorrendo menor à direita
     if((*q)->dir != NULL)
     {
          BuscaMenorDireitaRemocao(p, &((*q)->dir), peso);

          //Rotação à Direita
          if((*peso) == 1)
               RotacaoDireita(q, peso);
     }
     else
     {
          (*p)->info = (*q)->info;
          (*p) = (*q);
          (*q) = (*q)->esq;
          (*peso) = 1;
     }
     
}

//Mostrar a Árvore AVL
void MostraArvore(def_arvore arvore, char raiz)
{
     //Verificando se é a raiz
     if (raiz == '1')
          printf("\nRAIZ: %d -> PESO: %d\n", arvore->info, arvore->balanco);
     else
          printf("\nNO: %d -> PESO: %d\n", arvore->info, arvore->balanco);

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
     printf("\nARVORE BINARIA AVL\n\n");
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

int main(){

     //Definição da(s) Árvore(s) AVL
     def_arvore arvore = NULL;
     int peso;

     //Auxiliares
     char opc;
     int info;

     //Inserção na Árvore AVL
     do
     {
          printf("\nARVORE BINARIA AVL\n\n");
          printf("INSERCAO DE ELEMENTOS\n\n");
          printf("Digite o elemento positivo a ser inserido: ");
          do
          {
               scanf("%d", &info);
          } while (info < 0);

          InsereArvoreAVL(&arvore, info, &peso);

          printf("\n\nElemento inserido com sucesso!\n");
          printf("\nDeseja inserir outro elemento? (S/N)");
          do
          {
               opc = toupper(getch());
          } while (opc != 'S' && opc != 'N');
          system("cls");
     } while (opc == 'S');

     //Mostrando a Árvore AVL
     RotinaMostrar(arvore);
     printf("\n\n");
     system("pause");
     system("cls");

     //Remoção de Elementos da Árvore AVL
     do
     {
          printf("\nARVORE BINARIA AVL\n\n");
          printf("REMOCAO DE ELEMENTOS\n\n");
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

          if (RemoveAVL(&arvore, info, &peso))
          {
               printf("\n\nElemento removido com sucesso!\n");
          }
          else
          {
               printf("\n\nElemento nao encontrado. Tente novamente.\n");
          }
          system("pause");
          system("cls");

          //Mostrando a Árvore AVL após remoção
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