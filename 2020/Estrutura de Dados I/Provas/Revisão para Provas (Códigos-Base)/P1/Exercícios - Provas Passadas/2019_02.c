/**/

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

typedef struct no{
     long int info;
     struct no *prox;
}*def_fila;

//Funções Básicas
int verificaVazia(def_fila Inicio)
{
     return (Inicio == NULL);
}

void enfileirar(def_fila *Inicio, def_fila *Fim, long int info)
{
     def_fila p = (def_fila)malloc(sizeof(struct no));
     p->info = info;
     p->prox = NULL;

     if ((*Fim) == NULL)
     {
          (*Inicio) = p;
     }
     else
     {
          (*Fim)->prox = p;
     }

     (*Fim) = p;
}
int desenfileirar(def_fila *Inicio, def_fila *Fim, long int *info)
{
     if (verificaVazia((*Inicio)))
     {
          return 0;
     }

     (*info) = (*Inicio)->info;
     def_fila p = (*Inicio);
     (*Inicio) = (*Inicio)->prox;

     if ((*Inicio) == NULL)
     {
          (*Fim) = NULL;
     }
     free(p);

     return 1;
}

void mostrar(def_fila Inicio)
{
     if (verificaVazia(Inicio))
     {
          printf("Vazia.\n");
          return;
     }

     while (Inicio)
     {
          printf("%d ", Inicio->info);
          Inicio = Inicio->prox;
     }
     printf("\n");
}

int main(){

     long int num_clientes, tempo_process, i;
     unsigned long int tempo1, tempo2;
     long int item;

     def_fila InicioTemp, FinalTemp;
     def_fila InicioPouco, FinalPouco;
     def_fila InicioMuita, FinalMuita;

     //Iniciando variáveis
     tempo1 = tempo2 = 0;
     InicioTemp = FinalTemp = NULL;
     InicioPouco = FinalPouco = NULL;
     InicioMuita = FinalMuita = NULL;

     scanf("%ld %ld", &num_clientes, &tempo_process);
     for(i = 0; i < num_clientes; i++){
          scanf("%ld", &item);
          enfileirar(&InicioTemp, &FinalTemp, item);
     }

     while (desenfileirar(&InicioTemp, &FinalTemp, &item))
     {
          if(item < 10)
          {
               enfileirar(&InicioPouco, &FinalPouco, item);
               tempo1 += tempo_process;
          }
          else
          {
               enfileirar(&InicioMuita, &FinalMuita, item);
               tempo2 += tempo_process;
          }
     }
     
     printf("\nFila com Poucas Mercadorias: ");
     mostrar(InicioPouco);
     printf("Tempo: %lu minutos\n", tempo1);

     printf("\nFila com Muitas Mercadorias: ");
     mostrar(InicioMuita);
     printf("Tempo: %lu minutos\n", tempo2);

     return 0;
}