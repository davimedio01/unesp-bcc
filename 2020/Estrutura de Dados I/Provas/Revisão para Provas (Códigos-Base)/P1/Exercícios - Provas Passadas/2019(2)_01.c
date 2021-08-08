/**/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 100
//Estrutura da Pilha
typedef struct{
     int info[MAX];
     int topo;
}def_pilha;

//Funções Básicas
int verificaCheia(int topo){
     return (topo == MAX - 1);
}
int verificaVazia(int topo){
     return (topo == -1);
}

void empilhar(def_pilha *pilha, int info){

     if(verificaCheia(pilha->topo)){
          return;
     }
     (*pilha).info[++(*pilha).topo] = info;
}
int desempilhar(def_pilha *pilha, int *info){

     if(verificaVazia(pilha->topo)){
          return 0;
     }
     (*info) = (*pilha).info[(*pilha).topo--];
     return 1;
}

void iniciaFilaPilha(def_pilha *filaPilha, int num_pilhas)
{
     int i;
     for (i = 0; i <num_pilhas; i++)
     {
          filaPilha[i].topo = -1;
     }
}

int main(){

     int num_caixas, num_pilhas, cont, i, j;
     int posFila, posPilha, tamVet;
     int esf_esq, esf_dir;
     int qtd_caixas, caixa;
     def_pilha fila_pilhas[MAX]; //"Fila de Pilhas"

     while (scanf("%d %d", &num_caixas, &num_pilhas))
     {
          if(num_caixas == 0 && num_pilhas == 0)
               break;
          
          //Iniciando variáveis
          cont = 0;
          esf_dir = esf_esq = 0;
          iniciaFilaPilha(fila_pilhas, num_pilhas);

          //Leitura de cada pilha
          for(i = 0; i < num_pilhas; i++)
          {
               scanf("%d", &qtd_caixas);

               for(j = 0; j < qtd_caixas; j++)
               {
                    scanf("%d", &caixa);
                    empilhar(&fila_pilhas[i], caixa);
                    if(caixa == 1)
                    {
                         posFila = i;
                         posPilha = j;
                    }
               }
          }

          //Verificar "esforço" com relação à esquerda para se chegar na posição da caixa 1
          for(i = posFila + 1; i < num_pilhas; i++)
          {
               if(posPilha < (fila_pilhas[i].topo + 1))
               {
                    esf_dir += fila_pilhas[i].topo + 1 - posPilha;
               }
               else
               {
                    break;
               }
          }

          //Verificar "esforço" com relação à direita para se chegar na posição da caixa 1
          for (i = posFila - 1; i >= 0; i--)
          {
               if (posPilha < (fila_pilhas[i].topo + 1))
               {
                    esf_esq += fila_pilhas[i].topo + 1 - posPilha;
               }
               else
               {
                    break;
               }
          }

          //Pegando o menor esforço
          if(esf_dir < esf_esq)
          {
               cont = esf_dir + fila_pilhas[posFila].topo - posPilha;
          }
          else
          {
               cont = esf_esq + fila_pilhas[posFila].topo - posPilha;
          }
          
          //Saída final
          printf("Saida = %d\n", cont);
     }

     return 0;
}