/*Criado por Davi Augusto - BCC - UNESP Bauru*/
/*
3. Usando árvore genérica de Grau N (> 2), crie as rotinas:

c) encontre a soma de todos os elementos de uma árvore
f) descubra a quantidade de nós que tem números pares em uma árvore
i) determine a quantidade de nós de uma árvore que possuem somente um filho
     -> nó: cada estrutura (ex: A; B; C; D)

Utilização da Representação 2
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define GRAU 5

//Estrutura da Árvore: Vetor de Filhos
typedef struct no_arvore *def_arvore;
struct no_arvore{
     //Informação
     int info;
     //Filhos
     def_arvore filhos[GRAU];
};

//Escopos das Funções
void criaRaiz(def_arvore *arvore);
void criaFilho(def_arvore *arvore);
void criaNos(def_arvore *arvore, int raiz);
void mostraArvore(def_arvore arvore, int raiz);
void mostraFilhosNo(def_arvore arvore);
void somaTodosElementos(def_arvore arvore, int *soma);
void qtdNosPares(def_arvore arvore, int *qtd_par);
void qtdNosUmFilho(def_arvore arvore, int *qtd_umfilho);

//Criação da Raiz da Árvore
void criaRaiz(def_arvore *arvore)
{
     printf("\nARVORE DINAMICA - EXERCICIO 3\n\n");
     printf("\tCRIACAO DA RAIZ\n\n");
     //Auxiliares
     int info, i;
     //Definição da Raiz
     printf("\nDigite o valor inteiro da raiz: ");
     scanf("%d", &info);

     //Alocando espaço na memória para elemento
     (*arvore) = (def_arvore)malloc(sizeof(struct no_arvore));
     (*arvore)->info = info;
     //Definindo os Filhos da Raiz com Nulos
     for(i = 0; i < GRAU; i++){
          (*arvore)->filhos[i] = NULL;
     }
     system("cls");

}
//Criação dos Nós
void criaNos(def_arvore *arvore, int raiz)
{
     printf("\nARVORE DINAMICA - EXERCICIO 3\n\n");
     if(raiz == 1)
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
     do{
          opc = toupper(getch());
     }while(opc != 'S' && opc != 'N');

     //Caso tenha filhos, criar
     if(opc == 'S')
     {
          criaFilho(&(*arvore));
          //Após criar os filhos desejados do nó, criar os filhos desses filhos...
          for(i = 0; i < GRAU; i++)
          {
               if((*arvore)->filhos[i] != NULL)
                    criaNos(&((*arvore)->filhos[i]), 0);
               system("cls");
          }
     }
}
//Criação dos Filhos de um Nó
void criaFilho(def_arvore *arvore)
{
     printf("\n\nCRIACAO DOS FILHOS DE '%d'\n\n", (*arvore)->info);
     
     //Auxiliares
     int i, j, qtd, info;
     def_arvore q;

     //Verificando a quantidade desejada de filhos
     printf("Digite a quantidade de filhos (Min. 1/Max 5): ");
     do
     {
          scanf("%d", &qtd); 
     } while (qtd > GRAU || qtd < 1);

     //Atribuindo os filhos no nó
     for(i = 0; i < qtd; i++)
     {
          printf("\n\nFilho %d: ", i);
          scanf("%d", &info);

          //Atribuindo o filho
          q = (def_arvore)malloc(sizeof(struct no_arvore));
          q->info = info;
          for(j = 0; j < GRAU; j++)
               q->filhos[j] = NULL; //Zerando filhos do filho
          (*arvore)->filhos[i] = q;
     }
     
}
//Mostrar a Árvore
void mostraArvore(def_arvore arvore, int raiz)
{    
     //Verificando se é a raiz
     if(raiz == 1)
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
     for(i = 0; i < GRAU; i++)
     {
          //Se existir
          if(arvore->filhos[i] != NULL)
          {
               mostraArvore(arvore->filhos[i], 0);
          }
     }
}
//Mostrar os Filhos de Um Nó
void mostraFilhosNo(def_arvore arvore)
{
     int i, cont = 0;
     for(i = 0; i < GRAU; i++)
     {
          if(arvore->filhos[i] != NULL)
          {
               printf("\tFILHO: %d\n", arvore->filhos[i]->info);
               cont = 1;
          }
     }
     if(cont == 0)
     {
          printf("\tNAO POSSUI FILHOS\n");
     }
     //printf("\n");
}

//Exercícios Propostos
//Letra C: Soma de Todos os Elementos
void somaTodosElementos(def_arvore arvore, int *soma)
{
     //Verificando todos elementos nulos
     int i;
     for(i = 0; i < GRAU; i++)
     {
          //Caso não seja nulo, executar ele, até...
          if(arvore->filhos[i] != NULL)
          {
               somaTodosElementos(arvore->filhos[i], &(*soma));
          }
     }
     (*soma) += arvore->info;
}
//Letra F: Quantidade de Nós Existentes com Números Pares
void qtdNosPares(def_arvore arvore, int *qtd_par)
{
     //Verificando todos elementos nulos
     int i;
     for (i = 0; i < GRAU; i++)
     {
          //Caso não seja nulo, executar ele, até...
          if (arvore->filhos[i] != NULL)
          {
               qtdNosPares(arvore->filhos[i], &(*qtd_par));
          }
     }
     //Se for par, adicionar em qtd
     if(arvore->info % 2 == 0)
     {
          (*qtd_par)++;
     }
}
//Letra I: Quantidade de Nós Existentes com Apenas Um Filho
void qtdNosUmFilho(def_arvore arvore, int *qtd_umfilho)
{
     //Verificando todos elementos nulos
     int i, j;
     //Auxiliar contador para número de filhos
     int cont = 0;
     for (i = 0; i < GRAU; i++)
     {
          //Caso não seja nulo, executar ele, até...
          if (arvore->filhos[i] != NULL)
          {
               cont++;
               qtdNosUmFilho(arvore->filhos[i], &(*qtd_umfilho));
          }
     }
     //Caso tenha somente um filho
     if(cont == 1)
     {
          (*qtd_umfilho)++;
     }
}

int main(){

     //Declaração da Árvore
     def_arvore arvore;

     //Criação da Raiz da Árvore
     criaRaiz(&arvore);

     //Criação dos Filhos (Início: Raiz)
     criaNos(&arvore, 1);

     //Mostrando a Árvore Atual e das Respostas
     printf("\nARVORE DINAMICA - EXERCICIO 3\n\n");
     printf("\tARVORE ATUAL\n\n");
     mostraArvore(arvore, 1);
     printf("\n\n");

     //Letra C:
     int soma = 0;
     somaTodosElementos(arvore, &soma);
     printf("Soma de Todos os Elementos: %d\n\n", soma);
     //Letra F:
     int qtd_par = 0;
     qtdNosPares(arvore, &qtd_par);
     printf("Quantidade de Nos (Elementos Pares): %d\n\n", qtd_par);
     //Letra I:
     int qtd_umfilho = 0;
     qtdNosUmFilho(arvore, &qtd_umfilho);
     printf("Quantidade de Nos Com Apenas Um Filho : %d\n\n", qtd_umfilho);

     system("pause");
     system("cls");

     return 0;
}
