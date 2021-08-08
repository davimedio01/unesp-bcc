/*Criado por Davi Augusto - BCC - UNESP Bauru*/
/*
11. Duas árvores binárias são “iguais” se são ambas vazias, ou então se armazenam valores “iguais”
em suas raízes, suas subárvores esquerdas são iguais e suas subárvores direitas também são “iguais”.
Desenvolva a função lógica Igual(Arv1, Arv2) que determina se duas árvores binária Arv1 e Arv2 são
“iguais”.
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
void criaRaiz(def_arvore *arvore, int num);
void criaNo(def_arvore *arvore, int raiz, int num);
void mostraArvore(def_arvore arvore, int raiz);
int verificaArvoresIguais(def_arvore arvore1, def_arvore arvore2);

//Criação da Raiz
void criaRaiz(def_arvore *arvore, int num)
{
     printf("\nARVORE BINARIA '%d' - EXERCICIO 11\n\n", num);
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
void criaNo(def_arvore *arvore, int raiz, int num)
{
     system("cls");
     printf("\nARVORE BINARIA '%d' - EXERCICIO 11\n\n", num);
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
               criaNo(&((*arvore)->esq), 0, num);
          if ((*arvore)->dir != NULL)
               criaNo(&((*arvore)->dir), 0, num);
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

//Exercício 11
//Verificação de Árvores iguais
int verificaArvoresIguais(def_arvore arvore1, def_arvore arvore2)
{
     //Se forem nulas
     if(arvore1 == NULL && arvore2 == NULL)
          return 1;
     
     //Se não forem nulas, comparar
     if(arvore1 != NULL && arvore2 != NULL)
     {
          //Se dados forem iguais...
          if(arvore1->info == arvore2->info)
          {
               //Comparar esquerda e direita
               if (verificaArvoresIguais(arvore1->esq, arvore2->esq) &&
                   verificaArvoresIguais(arvore1->dir, arvore2->dir))
                    return 1;
               else
                    return 0;
          }
          else
               return 0;
          
     }

     //Se uma estiver vazia e a outra não, falso
     return 0;
}

int main()
{
     //Árvore 1
     //Definição da(s) Árvore(s) Binária(s)
     def_arvore arvore1;
     //Criação da(s) Raíz(es)
     criaRaiz(&arvore1, 1);
     //Criação do(s) Filho(s)
     criaNo(&arvore1, 1, 1);

     //Árvore 2
     //Definição da(s) Árvore(s) Binária(s)
     def_arvore arvore2;
     //Criação da(s) Raíz(es)
     criaRaiz(&arvore2, 2);
     //Criação do(s) Filho(s)
     criaNo(&arvore2, 1, 2);

     //Mostrando a(s) Árvore(s) atual(is)
     printf("\nARVORE BINARIA - EXERCICIO 11\n\n\n");
     printf("\tARVORE 1\n");
     mostraArvore(arvore1, 1);
     printf("\n");
     
     printf("\n\n\tARVORE 2\n");
     mostraArvore(arvore2, 1);
     printf("\n");

     //Exercício 11: Verificar se são iguais
     if (verificaArvoresIguais(arvore1, arvore2))
     {
          printf("\nAs arvores sao iguais!\n\n");
     }
     else
     {
          printf("\nAs arvores sao diferentes.\n\n");
     }

     system("pause");
     system("cls");


     return 0;
}