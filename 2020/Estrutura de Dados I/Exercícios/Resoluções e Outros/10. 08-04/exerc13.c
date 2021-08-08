/*Criado por Davi Augusto - BCC - UNESP Bauru*/
/*
13. Crie uma rotina que verifique se uma árvore binária é estritamente binária (SEM FILHOS ou COM DOIS FILHOS).
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

//Estrutura da Árvore Binária
typedef struct no *def_arvore;
struct no
{
     //Informação
     int info;
     //Esquerda e Direita
     def_arvore esq, dir;
};

//Escopos
void criaRaiz(def_arvore *arvore);
void criaNo(def_arvore *arvore, int raiz);
void mostraArvore(def_arvore arvore, int raiz);

//Criação da Raiz
void criaRaiz(def_arvore *arvore)
{
     printf("\nARVORE BINARIA - EXERCICIO 13\n\n");
     printf("\tCRIACAO DA RAIZ\n\n");

     //Informação
     int info;
     printf("Digite o valor da raiz: ");
     scanf("%d", &info);

     //Iniciando a árvore
     (*arvore) = (def_arvore)malloc(sizeof(struct no));
     (*arvore)->info = info;
     (*arvore)->dir = NULL;
     (*arvore)->esq = NULL;
}
//Criação dos Filhos (Nós)
void criaNo(def_arvore *arvore, int raiz)
{
     system("cls");
     printf("\nARVORE BINARIA - EXERCICIO 13\n\n");
     if (raiz == 1)
          printf("A RAIZ '%d' TEM FILHOS? (S/N)\n", (*arvore)->info);
     else
          printf("O NO '%d' TEM FILHOS? (S/N)\n", (*arvore)->info);

     //Opção
     char opc;
     do
     {
          opc = toupper(getch());
     } while (opc != 'S' && opc != 'N');

     //Caso tenha filhos, criar o da esquerda e direita
     if (opc == 'S')
     {
          printf("\n\nCRIACAO DOS FILHOS DE '%d'\n\n", (*arvore)->info);

          //Auxiliares
          def_arvore q;
          int info;

          //Esquerda
          printf("Entre com o valor do filho da ESQUERDA (-1 para cancelar): ");
          scanf("%d", &info);
          if (info != -1)
          {
               q = (def_arvore)malloc(sizeof(struct no));
               q->info = info;
               q->dir = NULL;
               q->esq = NULL;
               (*arvore)->esq = q;
          }
          //Direita
          printf("Entre com o valor do filho da DIREITA (-1 para cancelar): ");
          scanf("%d", &info);
          if (info != -1)
          {
               q = (def_arvore)malloc(sizeof(struct no));
               q->info = info;
               q->dir = NULL;
               q->esq = NULL;
               (*arvore)->dir = q;
          }

          //Configurando os filhos...
          if ((*arvore)->esq != NULL)
               criaNo(&((*arvore)->esq), 0);
          if ((*arvore)->dir != NULL)
               criaNo(&((*arvore)->dir), 0);
     }
     system("cls");
}
//Mostrar a Árvore Binária
void mostraArvore(def_arvore arvore, int raiz)
{
     //Verificando se é a raiz
     if (raiz == 1)
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
          mostraArvore(arvore->esq, 0);
     if (arvore->dir != NULL)
          mostraArvore(arvore->dir, 0);
}

//Exercício 13
//Verificar se é estritamente binária (sem filhos ou dois filhos)
int verificaEstritamenteBinaria(def_arvore arvore)
{
     if(arvore == NULL)
          return 1;
     
     if((arvore->esq == NULL && arvore->dir != NULL) ||
     (arvore->esq != NULL && arvore->dir == NULL))
     {
          return 0;
     }

     return (verificaEstritamenteBinaria(arvore->esq) &&
             verificaEstritamenteBinaria(arvore->dir));
}

int main()
{

     //Definição da(s) Árvore(s) Binária(s)
     def_arvore arvore;

     //Criação da(s) Raíz(es)
     criaRaiz(&arvore);

     //Criação do(s) Filho(s)
     criaNo(&arvore, 1);

     //Mostrando a(s) Árvore(s) atual(is)
     printf("\nARVORE BINARIA - EXERCICIO 13\n\n");
     printf("\tARVORE ATUAL\n");
     mostraArvore(arvore, 1);
     printf("\n");

     //Exercício 13: Verificar se é estritamente binária
     //int cont = 1;
     //verificaEstritamenteBinaria(arvore, &cont);
     if (verificaEstritamenteBinaria(arvore))
     {
          printf("\nA arvore eh estritamente binaria!\n\n");
     }
     else
     {
          printf("\nA arvore nao eh estritamente binaria.\n\n");
     }

     system("pause");
     system("cls");

     return 0;
}