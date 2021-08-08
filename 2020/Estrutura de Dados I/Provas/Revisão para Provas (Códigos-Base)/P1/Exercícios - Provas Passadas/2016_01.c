/**/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define MAX_BOLA 10
#define MAX_SACOLA 5

//Letra A
typedef struct{
     int bola[MAX_BOLA];
     int topo;
}def_pilha;
//Letra B
def_pilha sacolas[MAX_SACOLA];

//Funções Básicas
int verificaCheia(int topo)
{
     return (topo == MAX_BOLA - 1);
}
int verificaVazia(int topo)
{
     return (topo == -1);
}

int empilhar(def_pilha *pilha, int info)
{
     //Necessário verificar se está cheia
     if (verificaCheia(pilha->topo))
     {
          return 0;
     }

     //Aumentar o topo e inserir
     (*pilha).bola[++(*pilha).topo] = info;

     return 1;
}
int desempilhar(def_pilha *pilha, int *info)
{
     //Necessário verificar se está vazia
     if (verificaVazia(pilha->topo))
     {
          return 0;
     }

     //Remover e decrementar o topo
     (*info) = (*pilha).bola[(*pilha).topo];
     (*pilha).bola[(*pilha).topo] = -1; //Marcação de elemento nulo
     (*pilha).topo--;

     return 1;
}

int ProcuraBola(def_pilha *sacola, int num_bola)
{
     int i, bola;
     for(i = 0; i < MAX_SACOLA; i++)
     {
          //Procurando a bola
          while(desempilhar(&sacola[i], &bola))
          {
               if(bola == num_bola)
               {
                    return 1;
               }
          }
     }
     return 0;
}

int main(){

     

     
     return 0;
}