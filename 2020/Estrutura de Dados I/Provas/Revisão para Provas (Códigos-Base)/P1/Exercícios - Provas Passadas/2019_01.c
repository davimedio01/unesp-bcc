/**/

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define MAX 100

typedef struct{
     int info[MAX];
     int topo;
}def_pilha;

//Global
int num_cartas;
def_pilha pilha1, pilha2, pilha3;

//Funções Básicas
int verificaCheia(int topo)
{
     return (topo == MAX - 1);
}
int verificaVazia(int topo)
{
     return (topo == -1);
}

void empilhar(def_pilha *pilha, int info)
{
     //Necessário verificar se está cheia
     if (verificaCheia(pilha->topo))
     {
          return;
     }

     //Aumentar o topo e inserir
     (*pilha).info[++(*pilha).topo] = info;

}
int desempilhar(def_pilha *pilha, int *info)
{
     //Necessário verificar se está vazia
     if (verificaVazia(pilha->topo))
     {
          return 0;
     }

     //Remover e decrementar o topo
     (*info) = (*pilha).info[(*pilha).topo];
     (*pilha).info[(*pilha).topo] = -1; //Marcação de elemento nulo
     (*pilha).topo--;

     return 1;
}

void iniciaPilha(def_pilha *pilha)
{
     (*pilha).topo = -1;
}

int Jogo(int topo1, int topo2, int topo3)
{
     //Verifica se está no último elemento
     if(topo1 == topo2 && topo2 == topo3 && topo3 == num_cartas)
     {
          return 1;
     }

     //Todas probabilidades
     if (topo1 < num_cartas && pilha1.info[topo1] % 3 == 0 &&
         Jogo(topo1 + 1, topo2, topo3))
     {
          return 1;
     }
     if (topo2 < num_cartas && pilha2.info[topo2] % 3 == 0 &&
         Jogo(topo1, topo2 + 1, topo3))
     {
          return 1;
     }
     if (topo3 < num_cartas && pilha3.info[topo3] % 3 == 0 &&
         Jogo(topo1, topo2, topo3 + 1))
     {
          return 1;
     }
     if (topo1 < num_cartas && topo2 < num_cartas && (pilha1.info[topo1] + pilha2.info[topo2]) % 3 == 0 &&
         Jogo(topo1 + 1, topo2 + 1, topo3))
     {
          return 1;
     }
     if (topo1 < num_cartas && topo3 < num_cartas && (pilha1.info[topo1] + pilha3.info[topo3]) % 3 == 0 &&
         Jogo(topo1 + 1, topo2, topo3 + 1))
     {
          return 1;
     }
     if (topo2 < num_cartas && topo3 < num_cartas && (pilha2.info[topo2] + pilha3.info[topo3]) % 3 == 0 &&
         Jogo(topo1, topo2 + 1, topo3 + 1))
     {
          return 1;
     }
     if (topo1 < num_cartas && topo2 < num_cartas && topo3 < num_cartas &&
         (pilha1.info[topo1] + pilha2.info[topo2] + pilha3.info[topo3]) % 3 == 0 &&
         Jogo(topo1 + 1, topo2 + 1, topo3 + 1))
     {
          return 1;
     }

     //Caso não funcione uma das opções
     return 0;
}


int main(){

     int i, j;
     int carta1, carta2, carta3;

     while(scanf("%d", &num_cartas))
     {
          if(num_cartas == 0)
               break;
          
          //Iniciando variáveis
          iniciaPilha(&pilha1);
          iniciaPilha(&pilha2);
          iniciaPilha(&pilha3);


          for(i = 0; i < num_cartas; i++)
          {
               scanf("%d %d %d", &carta1, &carta2, &carta3);
               empilhar(&pilha1, carta1);
               empilhar(&pilha2, carta2);
               empilhar(&pilha3, carta3);
          }

          if(Jogo(0, 0, 0)){
               printf("O jogador pode vencer!\n");
               //printf("1\n");
          }
          else{
               printf("O jogador nao pode vencer.\n");
               //printf("0\n");
          }

     }
     
     return 0;
}