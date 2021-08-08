/**/

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define ESC 27

//Definição do Tamanho da Árvore e o Grau de Cada Nó
#define MAX_ARVORE 20
#define GRAU 5

//Estrutura da Árvore Estática (Método 3)
typedef int filhos_vet[GRAU];
typedef struct{
     int info;
     filhos_vet filhos;
}posicao;
typedef posicao def_arvore[MAX_ARVORE];

//Funções Básicas
void IniciaArvore(def_arvore arvore)
{
     int i, j;
     for(i = 0; i < MAX_ARVORE; i++)
     {
          arvore[i].info = -1;
          for(j = 0; j < GRAU; j++)
          {
               arvore[i].filhos[j] = 0;
          }
     }
}

void InsereEstatico(def_arvore *arvore)
{
     //Definindo a raiz
     int raiz;
     printf("\nARVORE GENERICA - ESTATICA\n\n");
     printf("Digite um numero positivo para a raiz: ");
     do
     {
          scanf("%d", &raiz);
     } while (raiz < 0);

     //Atribuindo a raiz para o vetor
     (*arvore)[0].info = raiz;
     system("cls");


     //Definindo e atribuindo os filhos
     int pai = 0, pos_atual = 1, qtd_filhos, info;
     char opc;
     int i, j;
     for(i = 1; i < MAX_ARVORE; i++)
     {
          //Caso o elemento não esteja configurado
          if((*arvore)[pai].info != -1)
          {
               printf("\nARVORE GENERICA - ESTATICA\n\n");

               //Raiz
               if(pai == 0)
               {
                    printf("A raiz '%d' tem filhos? (S/N)\n", (*arvore)[pai].info);
                    do
                    {
                         opc = toupper(getch());
                    } while (opc != 'S' && opc != 'N');
               }
               //Nó
               else
               {
                    printf("O no '%d' tem filhos? (S/N)\n", (*arvore)[pai].info);
                    do
                    {
                         opc = toupper(getch());
                    } while (opc != 'S' && opc != 'N');
               }
               
               //Configurando filhos
               if(opc == 'S')
               {
                    system("cls");
                    printf("\nARVORE GENERICA - ESTATICA\n\n");

                    //Raiz
                    if(pai == 0)
                         printf("CRIACAO DO(S) FILHO(S) DA RAIZ '%d'\n\n", (*arvore)[pai].info);
                    //Nó
                    else
                         printf("CRIACAO DO(S) FILHO(S) DO NO '%d'\n\n", (*arvore)[pai].info);
               
                    printf("Indique a quantidade de filhos (Min. 1/Max. %d): ", GRAU);
                    do
                    {
                         scanf("%d", &qtd_filhos);
                    } while (qtd_filhos < 1 || qtd_filhos > GRAU);
                    
                    //Configurando CADA filho
                    for(j = 0; j < qtd_filhos; j++)
                    {
                         printf("\n\nFilho %d: ", j + 1);
                         do{
                              scanf("%d", &info);
                         }while(info < 0);

                         (*arvore)[pos_atual].info = info;
                         (*arvore)[pai].filhos[j] = pos_atual;
                         pos_atual++;
                    }
               }
               system("cls");
          }

          //Configurando o próximo nó
          pai++;
     }
}

void MostraEstatico(def_arvore arvore)
{
     //Auxiliares
     int pai = 0, pos_atual = 0, qtd_filhos, info;

     //Mostrando a partir da raiz
     int i, j;

     printf("\nARVORE GENERICA - ESTATICA\n\n");
     printf("RAIZ: %d\n", arvore[pai].info);
     for(i = 1; i < MAX_ARVORE; i++)
     {
          //Caso exista elemento
          if(arvore[pai].info != -1)
          {
               if(pai != 0)
                    printf("\nNO '%d'\n", arvore[pai].info);
               printf("\tFILHOS: ");
               qtd_filhos = 0;
               for(j = 0; j < GRAU; j++)
               {
                    if(arvore[pai].filhos[j] != 0)
                    {
                         pos_atual = arvore[pai].filhos[j];
                         if(qtd_filhos == 0)
                              printf("\t%d\n", arvore[pos_atual].info);
                         else
                              printf("\t\t\t%d\n", arvore[pos_atual].info);
                         qtd_filhos++;
                    }
               }
               //Caso não existam filhos
               if(qtd_filhos == 0)
               {
                    printf(" NENHUM FILHO.\n");
               }
          }
          pai++;
     }
     printf("\n\n");
     system("pause");
}

int main(){

     //Declaração da Árvore Genérica Estática
     def_arvore arvore;

     //Iniciando Árvore
     IniciaArvore(arvore);

     //Inserção
     InsereEstatico(arvore);

     //Mostrando
     MostraEstatico(arvore);
     
     return 0;
}