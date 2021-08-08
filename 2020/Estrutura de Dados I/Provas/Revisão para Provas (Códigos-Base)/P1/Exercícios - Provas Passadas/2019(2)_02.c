/**/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define MAX 50

typedef struct no{
     int info;
     struct no *prox;
}*def_fila;

int verificaVazia(def_fila Inicio){
     return (Inicio == NULL);
}

void empilhar(def_fila *Inicio, def_fila *Final, int info)
{
     def_fila p = (def_fila)malloc(sizeof(struct no));
     p->info = info;
     p->prox = NULL;
     
     if((*Inicio) == NULL){
          (*Inicio) = p;
     }
     else{
          (*Final)->prox = p;
     }
     (*Final) = p;
}
int desempilhar(def_fila *Inicio, def_fila *Final, int *info)
{
     if(verificaVazia((*Inicio))){
          return 0;
     }

     (*info) = (*Inicio)->info;
     def_fila p = (*Inicio);
     (*Inicio) = (*Inicio)->prox;

     if(p == (*Final)){
          (*Final) = NULL;
     }
     free(p);

     return 1;
}



void constroiPilha(def_fila *Inicio, def_fila *Final, int qtd_cartas)
{
     int i;
     for(i = 1; i <= qtd_cartas; i++)
     {
          empilhar(&(*Inicio), &(*Final), i);
     }
}
int main(){

     int qtd_cartas, carta;
     int fila_resp[MAX], pos_filares;
     int i, j, verifica;
     def_fila Inicio, Final;
     Inicio = Final = NULL;

     while(scanf("%d", &qtd_cartas))
     {
          if(qtd_cartas == 0)
               break;

          if(qtd_cartas == 1)
          {
               printf("Remaining card: 1\n");
          }
          else
          {
               //Iniciando variáveis
               pos_filares = verifica = 0;
               constroiPilha(&Inicio, &Final, qtd_cartas);

               while(desempilhar(&Inicio, &Final, &carta))
               {
                    if(verifica == 0)
                    {
                         fila_resp[pos_filares++] = carta;
                         verifica = 1;
                    }
                    else
                    {
                         empilhar(&Inicio, &Final, carta);
                         verifica = 0;
                    }
               }
               
               printf("Discarded cards: ");
               for(i = 0; i < pos_filares - 2; i++)
               {
                    printf("%d, ", fila_resp[i]);
               }
               printf("%d\n", fila_resp[i++]);

               printf("Remaining card: %d\n", fila_resp[i]);
          }    

     }
     
     return 0;
}