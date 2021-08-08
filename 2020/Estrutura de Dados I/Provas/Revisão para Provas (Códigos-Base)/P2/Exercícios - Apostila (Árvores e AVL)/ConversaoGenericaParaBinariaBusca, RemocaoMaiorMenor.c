/*Criado por Davi Augusto - BCC - UNESP Bauru*/
/**/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#define MAX_CAMINHO 100

//Definição da Árvore Genérica (Vetor de Filhos)
#define GRAU 4                                   //Grau Máximo
typedef struct no_generico *def_arvore_generica; //Estrutura Dinâmica
struct no_generico
{
     int info;                         //Informação
     def_arvore_generica filhos[GRAU]; //Filhos
};
//Funções da Árvore Genérica
//Escopos
void CriaRaizGenerico(def_arvore_generica *arv_gen);
void CriaNoGenerico(def_arvore_generica *arv_gen, int raiz);
void CriaFilhoGenerico(def_arvore_generica *arv_gen);
void MostraArvGen(def_arvore_generica arv_gen, int raiz);
void MostraFilhosNoArvGen(def_arvore_generica arv_gen);

//Criação da Raiz
void CriaRaizGenerico(def_arvore_generica *arv_gen)
{
     printf("\nEXERCICIO 6 - ARVORE GENERICA\n\n");
     printf("\tCRIACAO DA RAIZ\n\n");
     //Auxiliares
     int info, i;
     //Definição da Raiz
     printf("\nDigite o valor inteiro da raiz: ");
     scanf("%d", &info);

     //Alocando espaço na memória e criando a Árvore Genérica
     (*arv_gen) = (def_arvore_generica)malloc(sizeof(struct no_generico));
     (*arv_gen)->info = info; //Raiz
     for (i = 0; i < GRAU; i++)
     {
          (*arv_gen)->filhos[i] = NULL; //Filhos da Raiz
     }
     system("cls");
}
//Criação dos Nós
void CriaNoGenerico(def_arvore_generica *arv_gen, int raiz)
{
     system("cls");
     printf("\nEXERCICIO 6 - ARVORE GENERICA\n\n");
     //Verificando se é a raiz ou não
     if (raiz == 1)
     {
          printf("A RAIZ '%d' TEM FILHOS? (S/N)\n", (*arv_gen)->info);
     }
     else
     {
          printf("O NO '%d' TEM FILHOS? (S/N)\n", (*arv_gen)->info);
     }

     //Auxiliares
     char opc;
     int i;

     //Opção
     do
     {
          opc = toupper(getch());
     } while (opc != 'S' && opc != 'N');

     //Caso seja 'S'
     if (opc == 'S')
     {
          //Criar filhos
          CriaFilhoGenerico(&(*arv_gen));

          //Após criar os filhos desse nó, avançar em cada um e criar filhos (se necessário)
          for (i = 0; i < GRAU; i++)
          {
               if ((*arv_gen)->filhos[i] != NULL)
                    CriaNoGenerico(&((*arv_gen)->filhos[i]), 0);
               system("cls");
          }
     }
}
//Criação de Filhos
void CriaFilhoGenerico(def_arvore_generica *arv_gen)
{
     printf("\n\nCRIACAO DOS FILHOS DE '%d'\n\n", (*arv_gen)->info);

     //Auxiliares
     int i, j, qtd, info;
     def_arvore_generica aux;

     //Verificando a quantidade desejada de filhos
     printf("Digite a quantidade de filhos (Min. 1/Max 4): ");
     do
     {
          scanf("%d", &qtd);
     } while (qtd > GRAU || qtd < 1);

     //Atribuindo os filhos do nó
     for (i = 0; i < qtd; i++)
     {
          printf("\n\nFilho %d: ", i + 1);
          scanf("%d", &info);

          //Atribuindo o filho
          aux = (def_arvore_generica)malloc(sizeof(struct no_generico));
          aux->info = info;
          for (j = 0; j < GRAU; j++)
               aux->filhos[j] = NULL;
          (*arv_gen)->filhos[i] = aux;
     }
}
//Mostrar a Árvore Genérica
void MostraArvGen(def_arvore_generica arv_gen, int raiz)
{
     //Verificando se é a raiz
     if (raiz == 1)
     {
          printf("\nRAIZ: %d\n", arv_gen->info);
     }
     else
     {
          printf("\nNO: %d\n", arv_gen->info);
     }

     //Mostrar os filhos de cada nó
     MostraFilhosNoArvGen(arv_gen);

     //Avançando para cada filho
     int i;
     for (i = 0; i < GRAU; i++)
     {
          if (arv_gen->filhos[i] != NULL)
               MostraArvGen(arv_gen->filhos[i], 0);
     }
}
//*Mostrar Filhos de Cada Nó
void MostraFilhosNoArvGen(def_arvore_generica arv_gen)
{
     int i, cont = 0;
     for (i = 0; i < GRAU; i++)
     {
          if (arv_gen->filhos[i] != NULL)
          {
               printf("\tFILHO: %d\n", arv_gen->filhos[i]->info);
               cont = 1;
          }
     }
     if (cont == 0)
     {
          printf("\tNAO POSSUI FILHOS\n");
     }
}

//Definição da Árvore Binária de Busca
typedef struct no_binariabusca *def_arvore_binariabusca; //Estrutura Dinâmica
struct no_binariabusca
{
     int info;                         //Informação
     def_arvore_binariabusca esq, dir; //Filhos
};
//Funções da Árvore Binária de Busca
//Inserção na Árvore Binária de Busca
void InsereArvBinBusca(def_arvore_binariabusca *arv_binbusca, int info)
{
     //Auxiliar
     def_arvore_binariabusca aux;

     //Caso o elemento atual seja null, alocar
     if ((*arv_binbusca) == NULL)
     {
          aux = (def_arvore_binariabusca)malloc(sizeof(struct no_binariabusca));
          aux->info = info;
          aux->dir = aux->esq = NULL;
          (*arv_binbusca) = aux;
     }
     else //Do contrário, verificar o local para inserção
     {
          if ((*arv_binbusca)->info > info)
               InsereArvBinBusca(&((*arv_binbusca)->esq), info);
          else if ((*arv_binbusca)->info < info)
               InsereArvBinBusca(&((*arv_binbusca)->dir), info);
     }
}
//Mostrar a Árvore Binária de Busca
void MostraArvBinBusca(def_arvore_binariabusca arv_binbusca, int raiz)
{
     //Verificando se é a raiz
     if (raiz == 1)
          printf("\nRAIZ: %d\n", arv_binbusca->info);
     else
          printf("\nNO: %d\n", arv_binbusca->info);

     //Mostrando os filhos do nó atual
     if (arv_binbusca->esq != NULL)
          printf("\tFILHO (ESQUERDA): %d\n", arv_binbusca->esq->info);
     if (arv_binbusca->dir != NULL)
          printf("\tFILHO (DIREITA): %d\n", arv_binbusca->dir->info);
     if (arv_binbusca->esq == NULL && arv_binbusca->dir == NULL)
          printf("\tNAO POSSUI FILHOS\n");

     //Avançando nos filhos (pré-ordem)
     if (arv_binbusca->esq != NULL)
          MostraArvBinBusca(arv_binbusca->esq, 0);
     if (arv_binbusca->dir != NULL)
          MostraArvBinBusca(arv_binbusca->dir, 0);
}

//Exercícios: Utilizando a Árvore Binária de Busca do Exercício 6
//Exercício 6: Converter Árvore Genérica em Árvore Binária de Busca
void ConverteArvGenParaArvBinBusca(def_arvore_generica arv_gen, def_arvore_binariabusca *arv_binbusca, int raiz)
{
     //Verificando a raiz para criá-la
     if (raiz == 1)
     {
          (*arv_binbusca) = (def_arvore_binariabusca)malloc(sizeof(struct no_binariabusca));
          (*arv_binbusca)->info = arv_gen->info;
          (*arv_binbusca)->esq = (*arv_binbusca)->dir = NULL;
     }

     //Auxiliares
     int i, info;

     //Percorrendo os filhos de um nó
     for (i = 0; i < GRAU; i++)
     {
          if (arv_gen->filhos[i] != NULL)
          {
               info = arv_gen->filhos[i]->info;
               InsereArvBinBusca(&(*arv_binbusca), info);
          }
     }

     //Percorrendo cada filho
     for (i = 0; i < GRAU; i++)
     {
          if (arv_gen->filhos[i] != NULL)
          {
               ConverteArvGenParaArvBinBusca(arv_gen->filhos[i], &(*arv_binbusca), 0);
          }
     }
}
//Exercício 9: Remover o Maior e Menor elemento de Árvore Binária de Busca
//Remover o Menor
void RemoveMenorArvBinBusca(def_arvore_binariabusca *arv_binbusca, int *menor)
{
     if ((*arv_binbusca)->esq == NULL)
     {
          //Salvando o menor elemento
          (*menor) = (*arv_binbusca)->info;

          //Auxiliar
          def_arvore_binariabusca aux = (*arv_binbusca);
          //Salvando direita caso exista
          (*arv_binbusca) = (*arv_binbusca)->dir;
          free(aux);

          return;
     }
     else
     {
          //Avançando à esquerda
          RemoveMenorArvBinBusca(&((*arv_binbusca)->esq), &(*menor));
     }
}
//Remover o Maior
void RemoveMaiorArvBinBusca(def_arvore_binariabusca *arv_binbusca, int *maior)
{
     if ((*arv_binbusca)->dir == NULL)
     {
          //Salvando o maior elemento
          (*maior) = (*arv_binbusca)->info;

          //Auxiliar
          def_arvore_binariabusca aux = (*arv_binbusca);
          //Salvando esquerda caso exista
          (*arv_binbusca) = (*arv_binbusca)->esq;
          free(aux);

          return;
     }
     else
     {
          //Avançando à direita
          RemoveMaiorArvBinBusca(&((*arv_binbusca)->dir), &(*maior));
     }
}
//Exercício 17: Retornar o caminho feito até um elemento (caso exista) em Árvore Binária de Busca
def_arvore_binariabusca BuscaElementoArvBinBusca(def_arvore_binariabusca arv_binbusca, int info, int *caminho, int *indice)
{
     if (arv_binbusca == NULL)
          return NULL;
     if (arv_binbusca->info == info)
          return arv_binbusca;
     
     //Percorrendo a árvore e salvando posições no vetor
     if (arv_binbusca->info > info)
     {
          caminho[(*indice)++] = arv_binbusca->info;
          BuscaElementoArvBinBusca(arv_binbusca->esq, info, &(*caminho), &(*indice));
     }
     else if (arv_binbusca->info < info)
     {
          caminho[(*indice)++] = arv_binbusca->info;
          BuscaElementoArvBinBusca(arv_binbusca->dir, info, &(*caminho), &(*indice));
     }
}

int main()
{
     ////////////////////////////
     //Exerício 6
     ////////////////////////////

     //Criação da Árvore Genérica
     def_arvore_generica arv_gen;
     CriaRaizGenerico(&arv_gen);
     CriaNoGenerico(&arv_gen, 1);
     //Mostrando a Árvore Genérica
     printf("\nEXERCICIO 6 - ARVORE GENERICA (ATUAL)\n\n");
     MostraArvGen(arv_gen, 1);
     printf("\n\n");

     /////////////////////////////////////////////////
     /*Convertendo para Árvore Binária de Busca
       que também será utilizada nos outros exercícios*/
     /////////////////////////////////////////////////
     def_arvore_binariabusca arv_binbusca;
     ConverteArvGenParaArvBinBusca(arv_gen, &arv_binbusca, 1);
     printf("\nARVORE BINARIA DE BUSCA\n\n");
     MostraArvBinBusca(arv_binbusca, 1);
     printf("\n\n");
     system("pause");

     ////////////////////////////
     //Exerício 9
     ////////////////////////////
     system("cls");
     printf("\nEXERCICIO 9 - ARVORE BINARIA DE BUSCA\n\n");

     //Menor
     printf("\nEliminando menor elemento...");
     int menor;
     RemoveMenorArvBinBusca(&arv_binbusca, &menor);
     printf("\n\nElemento '%d' eliminado com sucesso!\n\n", menor);
     MostraArvBinBusca(arv_binbusca, 0);
     printf("\n");

     //Maior
     printf("\nEliminando maior elemento...");
     int maior;
     RemoveMaiorArvBinBusca(&arv_binbusca, &maior);
     printf("\n\nElemento '%d' eliminado com sucesso!\n\n", maior);
     MostraArvBinBusca(arv_binbusca, 0);
     printf("\n\n");
     system("pause");

     ////////////////////////////
     //Exerício 17
     ////////////////////////////
     system("cls");
     printf("\nEXERCICIO 17 - ARVORE BINARIA DE BUSCA\n\n");

     //Auxiliares
     int info;
     //Perguntando opção para busca
     printf("Digite o elemento desejado para buscar: ");
     scanf("%d", &info);
     printf("\n\n");
     system("cls");
     printf("\nEXERCICIO 17 - ARVORE BINARIA DE BUSCA\n\n");

     //Fila de vetor para armazenar o caminho
     int caminho[MAX_CAMINHO], indice = 0;
     memset(caminho, 0, sizeof(MAX_CAMINHO));

     //Nó contendo o elemento desejado
     def_arvore_binariabusca busca = BuscaElementoArvBinBusca(arv_binbusca, info, &caminho, &indice);

     if (busca == NULL)
     {
          printf("Elemento nao encontrado.\n\n");
     }
     else
     {
          //Printando caminho por meio da fila
          printf("\nCaminho percorrido: ");
          int i;
          for (i = 0; i < indice; i++)
          {
               printf("%d ", caminho[i]);
          }
          printf("\n\nElemento: %d\n\n", busca->info);
     }
     system("pause");

     return 0;
}