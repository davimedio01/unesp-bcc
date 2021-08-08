/**/

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

//Estrutura LLSE da Pilha
typedef struct no *def_pilha;
struct no
{
     int info;
     def_pilha prox;
};

//Funções Básicas
int verificaVaziaPilha(def_pilha pilha)
{
     return (pilha == NULL);
}

void empilhar(def_pilha *pilha, int info)
{
     //Alocar memória
     def_pilha p = (def_pilha)malloc(sizeof(struct no));

     p->info = info;
     p->prox = (*pilha);
     (*pilha) = p;
}
int desempilhar(def_pilha *pilha, int *info)
{
     //Necessário verificar se pilha está vazia
     if (verificaVaziaPilha((*pilha)))
     {
          return 0;
     }

     (*info) = (*pilha)->info;
     def_pilha p = (*pilha);
     (*pilha) = (*pilha)->prox;
     free(p);
}

//Estrutura da Fila
typedef struct no *def_fila;
struct no
{
     int info;
     def_fila prox;
};

//Funções Básicas
int verificaVaziaFila(def_fila Fim)
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
     if (verificaVaziaFila((*Fim)))
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





int main(){

     
     
     return 0;
}