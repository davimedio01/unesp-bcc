/**/

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define GRAU 3

//Estrutura da Árvore Genérica de Grau Pré-Definido (> 2)
typedef struct no
{
     int info;

     //Filhos
     struct no *filhos[GRAU];
} * def_arvore;

//Funções Básicas
//Escopos
void criaRaiz(def_arvore *arvore);
void criaNos(def_arvore *arvore, char raiz);
void criaFilho(def_arvore *arvore);
void mostraArvore(def_arvore arvore, char raiz);
void mostraFilhosNo(def_arvore arvore);

//Criação da Raiz
void criaRaiz(def_arvore *arvore)
{
     printf("\nARVORE GENERICA DINAMICA - GRAU %d\n\n", GRAU);
     printf("\tCRIACAO DA RAIZ\n\n");
     //Auxiliares
     int info, i;
     //Definição da Raiz
     printf("\nDigite o valor inteiro da raiz: ");
     scanf("%d", &info);

     //Alocando espaço na memória para elemento
     (*arvore) = (def_arvore)malloc(sizeof(struct no));
     (*arvore)->info = info;
     //Definindo os Filhos da Raiz com Nulos
     for (i = 0; i < GRAU; i++)
     {
          (*arvore)->filhos[i] = NULL;
     }
}

//Criação dos Nós
void criaNos(def_arvore *arvore, char raiz)
{
     system("cls");
     printf("\nARVORE GENERICA DINAMICA - GRAU %d\n\n", GRAU);
     if (raiz == '1')
     {
          printf("A RAIZ '%d' TEM FILHOS? (S/N)\n", (*arvore)->info);
     }
     else
     {
          printf("O NO '%d' TEM FILHOS? (S/N)\n", (*arvore)->info);
     }

     //Auxiliares
     char opc;
     int i;

     //Opção
     do
     {
          opc = toupper(getch());
     } while (opc != 'S' && opc != 'N');

     //Caso tenha filhos, criar
     if (opc == 'S')
     {
          criaFilho(&(*arvore));
          //Após criar os filhos desejados do nó, criar os filhos desses filhos...
          for (i = 0; i < GRAU; i++)
          {
               if ((*arvore)->filhos[i] != NULL)
                    criaNos(&((*arvore)->filhos[i]), '0');
               system("cls");
          }
     }
}

//Criação dos Filhos
void criaFilho(def_arvore *arvore)
{
     printf("\n\nCRIACAO DOS FILHOS DE '%d'\n\n", (*arvore)->info);

     //Auxiliares
     int i, j, qtd, info;
     def_arvore q;

     //Verificando a quantidade desejada de filhos
     printf("Digite a quantidade de filhos (Min. 1/Max %d): ", GRAU);
     do
     {
          scanf("%d", &qtd);
     } while (qtd > GRAU || qtd < 1);

     //Atribuindo os filhos no nó
     for (i = 0; i < qtd; i++)
     {
          printf("\n\nFilho %d: ", i + 1);
          scanf("%d", &info);

          //Atribuindo o filho
          q = (def_arvore)malloc(sizeof(struct no));
          q->info = info;
          for (j = 0; j < GRAU; j++)
               q->filhos[j] = NULL; //Zerando filhos do filho
          (*arvore)->filhos[i] = q;
     }
}

//Mostrar a Árvore
void mostraArvore(def_arvore arvore, char raiz)
{
     //Verificando se é a raiz
     if (raiz == '1')
     {
          printf("\nRAIZ: %d\n", arvore->info);
     }
     else
     {
          printf("\nNO: %d\n", arvore->info);
     }

     //Mostrando filhos de cada nó
     mostraFilhosNo(arvore);
     //Avançando para os filhos
     int i;
     for (i = 0; i < GRAU; i++)
     {
          //Se existir
          if (arvore->filhos[i] != NULL)
          {
               mostraArvore(arvore->filhos[i], '0');
          }
     }
}
void mostraFilhosNo(def_arvore arvore)
{
     int i, cont = 0;
     for (i = 0; i < GRAU; i++)
     {
          if (arvore->filhos[i] != NULL)
          {
               printf("\tFILHO: %d\n", arvore->filhos[i]->info);
               cont = 1;
          }
     }
     if (cont == 0)
     {
          printf("\tNAO POSSUI FILHOS\n");
     }
     //printf("\n");
}

//Rotinas do Exercício
//Letra A: Largura
//Uso de Fila (LCSE)
typedef struct no_fila *def_fila;
struct no_fila
{
     def_arvore info;
     def_fila prox;
};
int verificaFilaVazia(def_fila Fim)
{
     return (Fim == NULL);
}
void enfileirar(def_fila *Fim, def_arvore info)
{
     def_fila p = (def_fila)malloc(sizeof(struct no_fila));
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
void desenfileirar(def_fila *Fim, def_arvore *info)
{
     if (verificaFilaVazia((*Fim)))
     {
          return;
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
}

void Largura(def_arvore arvore)
{
     //Caso não haja elemento
     if(arvore == NULL)
          return;
     
     printf("\n\nLargura: ");

     //Uso de Fila
     def_fila fila = NULL;

     //Enfileirando a Raiz
     enfileirar(&fila, arvore);

     //Percorrendo a árvore e utilizando auxiliar
     def_arvore p;
     int i;
     while(fila != NULL)
     {
          desenfileirar(&fila, &p);
          printf("%d ", p->info);

          //Percorrendo os filhos
          for(i = 0; i < GRAU; i++)
          {
               if(p->filhos[i] != NULL)
               {
                    enfileirar(&fila, p->filhos[i]);
               }
          }
     }

}


//Letra B: Profundidade
//Uso de Pilha (LLSE)
typedef struct no_pilha *def_pilha;
struct no_pilha
{
     def_arvore info;
     def_pilha prox;
};
int verificaPilhaVazia(def_pilha pilha)
{
     return (pilha == NULL);
}

void empilhar(def_pilha *pilha, def_arvore info)
{
     //Alocar memória
     def_pilha p = (def_pilha)malloc(sizeof(struct no_pilha));

     p->info = info;
     p->prox = (*pilha);
     (*pilha) = p;
}
void desempilhar(def_pilha *pilha, def_arvore *info)
{
     //Necessário verificar se pilha está vazia
     if (verificaPilhaVazia((*pilha)))
     {
          return;
     }

     (*info) = (*pilha)->info;
     def_pilha p = (*pilha);
     (*pilha) = (*pilha)->prox;
     free(p);
}

void Profundidade(def_arvore arvore)
{
     //Caso não haja elemento
     if(arvore == NULL)
          return;

     printf("\n\nProfundidade: ");

     //Uso de Pilha
     def_pilha pilha = NULL;

     //Enfileirando a Raiz
     empilhar(&pilha, arvore);

     //Percorrendo a árvore e utilizando auxiliar
     def_arvore p;
     int i;
     while (pilha != NULL)
     {
          desempilhar(&pilha, &p);
          printf("%d ", p->info);

          //Percorrendo os filhos
          for (i = GRAU - 1; i >= 0; i--)
          {
               if (p->filhos[i] != NULL)
               {
                    empilhar(&pilha, p->filhos[i]);
               }
          }
     }
}



int main()
{

     //Declaração da Árvore
     def_arvore arvore;

     //Criação da Raiz da Árvore
     criaRaiz(&arvore);

     //Criação dos Filhos (Início: Raiz)
     criaNos(&arvore, '1');

     //Mostrando a Árvore
     printf("\nARVORE GENERICA DINAMICA - GRAU %d\n\n", GRAU);
     printf("\tARVORE ATUAL\n\n");
     mostraArvore(arvore, '1');
     //printf("\n\n");

     ///////////////////////////////////
     //Largura
     Largura(arvore);
     /////////////////////////////////// 

     ///////////////////////////////////
     //Profundidade
     Profundidade(arvore);
     ///////////////////////////////////
     printf("\n\n");
     system("pause");
     system("cls");
     return 0;
}