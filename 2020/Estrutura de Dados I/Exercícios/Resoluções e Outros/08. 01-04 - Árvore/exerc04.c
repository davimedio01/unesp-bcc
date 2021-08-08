/*Criado por Davi Augusto - BCC - UNESP Bauru*/
/*
Árvore Binária Estática - Gerenciamento de Pastas (SO)

Pense num sistema de gerenciamento de pastas de um Sistema Operacional. A cada criação de pasta
você escolhe uma pasta que abrigará a sub-pasta a ser criada (evidentemente a raiz é o drive A, C ou
D). A remoção de uma pasta consiste em escolher a pasta e apagá-la (aqui, se houver arquivos e/ou
pastas dentro da pasta apagada, tudo será removido junto). Implemente essas ações seguindo as
diretrizes abaixo:
(a) Defina uma estrutura que comporte o sistema de pastas do SO
(b) Faça a rotina de criação de pasta neste sistema, onde é passada a árvore inteira, a pasta “mãe” e
o nome da sub-pasta.

Método Utilizado: 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define ESC 27

//Definição do Tamanho da Árvore e o Grau de Cada Nó
#define MAXPASTAS 50
#define MAXNOME 100
#define GRAU 5
//Letra A - Estrutura da Árvore Estática (Pastas): Método 3
typedef int grau[GRAU];
typedef struct{
     //Nome da Pasta
     char nome[MAXNOME];
     //Hierarquia de Cada Pasta
     grau subpastas;
} gerenciador;
typedef gerenciador pastas[MAXPASTAS];

//Inicializa a Árvore (Zerar nome das pastas)
void iniciaGerenciador(pastas gerenciaPastas)
{
     int i, j;
     for(i = 0; i < MAXPASTAS; i++)
     {
          //Zerando os nomes
          strcpy(gerenciaPastas[i].nome, "*");
          for(j = 0; j < GRAU; j++)
          {
               //Zerando os graus de cada nó
               gerenciaPastas[i].subpastas[j] = 0;
          }
     }
}

//Definindo a Raiz e Criação de Pastas
void criaPastas(pastas gerenciaPastas)
{
     //Definindo a raiz
     char raiz[2];
     printf("\nGERENCIADOR DE PASTAS  - SO\n\n");
     printf("NOMES DISPONIVEIS PARA RAIZ: 'A', 'C', 'D'\n\n");
     printf("Indique o nome desejado para a raiz: ");
     do{
          gets(raiz);
     } while (!validaRaiz(raiz));
     fflush(stdin);
     strcpy(gerenciaPastas[0].nome, raiz); //Copiando para o Gerenciador
     system("cls");

     //Variáveis: "super_pasta" (configura o pai/super pasta); "pos_atual" (indica a posição atual do filho); "qtd_subpasta" (indica a qtd de subpastas associadas)
     int super_pasta = 0, pos_atual = 1, qtd_subpastas;
     //Auxiliares para nome da pastas e para verificar se tem sub-pastas associadas
     char nome_pastas[MAXNOME], verificaSubPasta;
     //Acrescentando sub-pastas no SO
     int i, j;
     for(i = 1; i < MAXPASTAS; i++)
     {
          //Caso o pai não esteja configurado
          if(strcmp(gerenciaPastas[super_pasta].nome, "*") != 0)
          {
               printf("\nGERENCIADOR DE PASTAS  - SO\n\n");
               if(super_pasta == 0)
               {
                    //Raiz
                    printf("A raiz '%s' tem sub-pastas associadas? (S/N)\n", gerenciaPastas[super_pasta].nome);
                    do{
                         verificaSubPasta = toupper(getch());
                    }while(verificaSubPasta != 'S' && verificaSubPasta != 'N');
               }
               else
               {
                    //Demais pastas
                    printf("A pasta '%s' tem sub-pastas associadas? (S/N)\n", gerenciaPastas[super_pasta].nome);
                    do
                    {
                         verificaSubPasta = toupper(getch());
                    } while (verificaSubPasta != 'S' && verificaSubPasta != 'N');
               }
               fflush(stdin);
               //Caso tenha sub-pastas associadas, configurar cada uma
               if(verificaSubPasta == 'S')
               {
                    system("cls");
                    printf("\nGERENCIADOR DE PASTAS  - SO\n\n");
                    if(super_pasta == 0)
                    {
                         printf("CRIACAO DA(S) SUB-PASTA(S) DA RAIZ '%s'\n\n", gerenciaPastas[super_pasta].nome);
                    }
                    else
                    {
                         printf("CRIACAO DA(S) SUB-PASTA(S) DA PASTA '%s'\n\n", gerenciaPastas[super_pasta].nome);
                    }    
                    printf("Indique a quantidade de sub-pastas presentes (Min. 1/Max. 5): ");
                    do{
                         scanf("%d", &qtd_subpastas);
                    }while(qtd_subpastas < 1 || qtd_subpastas > GRAU);
          
                    //Com a quantidade de sub-pastas, configurar CADA uma
                    for(j = 0; j < qtd_subpastas; j++)
                    {
                         printf("\n\nNome da sub-pasta %d (digite '*' para anular): ", j+1);
                         do{
                              gets(nome_pastas);
                         }while(strlen(nome_pastas) == 0);
                         fflush(stdin);

                         //Caso não tenha cancelado, atribuir nas posição correta
                         if(strcmp(nome_pastas, "*") != 0)
                         {
                              strcpy(gerenciaPastas[pos_atual].nome, nome_pastas);
                              gerenciaPastas[super_pasta].subpastas[j] = pos_atual;
                         }
                         pos_atual++;
                    }
               }
               system("cls");
          }

          //Configurando o próximo pai
          super_pasta++;
     }   
}
//Verificando se a raiz é válida
int validaRaiz(char raiz[])
{
     return ((strcmp(raiz, "A") == 0) ||
             (strcmp(raiz, "C") == 0) ||
             (strcmp(raiz, "D") == 0));
}
//Mostrando as Pastas e Sub-Pastas (Árvore)
void mostraPastas(pastas gerenciaPastas)
{
     //Variáveis: "super_pasta" (mostra o pai/super pasta); "pos_atual" (indica a posição atual do filho); "qtd_subpasta" (indica a qtd de subpastas associadas)
     int super_pasta = 0, pos_atual = 0, qtd_subpastas;

     //Mostrando as Pastas a partir da Raiz
     int i, j;
     printf("\nGERENCIADOR DE PASTAS  - SO\n\n");
     printf("RAIZ: %s\n\n", gerenciaPastas[0].nome);
     for(i = 1; i < MAXPASTAS; i++)
     {
          //Caso exista elemento no "pai"
          if(strcmp(gerenciaPastas[super_pasta].nome, "*") != 0)
          {
               printf("\nPASTA ATUAL: '%s'\n", gerenciaPastas[super_pasta].nome);
               printf("\tSUB-PASTAS:");
               qtd_subpastas = 0;
               //Verificando se existem sub-pastas associadas
               for(j = 0; j < GRAU; j++)
               {
                    if (gerenciaPastas[super_pasta].subpastas[j] != 0)
                    {
                         pos_atual = gerenciaPastas[super_pasta].subpastas[j];
                         if (qtd_subpastas == 0)
                              printf("\t%s\n", gerenciaPastas[pos_atual].nome);
                         else
                              printf("\t\t\t%s\n", gerenciaPastas[pos_atual].nome);
                         qtd_subpastas++;
                    }
               }
               //Caso não existam elementos
               if (qtd_subpastas == 0)
               {
                    printf(" NENHUMA ASSOCIADA.\n");
               }
          }
          super_pasta++;
     }
     printf("\n\n");
     system("pause");
}
//Remover pastas (se desejado)
int removePastas(pastas gerenciaPastas)
{
     int verifica = 0;
     char verificaRemocao, raiz[2];
     printf("\n\nDeseja remover alguma pasta acima? (S/N)\n");
     do{
          verificaRemocao = toupper(getch());
     }while(verificaRemocao != 'S' && verificaRemocao != 'N');
     strcpy(raiz, gerenciaPastas[0].nome);

     //Caso deseje remover
     if(verificaRemocao == 'S')
     {
          char pasta_remover[MAXNOME];
          printf("\nDigite o nome da pasta para remover: ");
          do{
               gets(pasta_remover);
          }while(strlen(pasta_remover) == 0);
          fflush(stdin);
          //Verificando a existência da pasta digitada para remoção
          int super_pasta = 0, pos_atual = 0;
          int i, j, k;

          for(i = 1; i < MAXPASTAS && !verifica; i++)
          {
               //Verificando os filhos da pasta pai (haja visto que começa na raiz, e não se pode remover a raiz)
               if(strcmp(gerenciaPastas[super_pasta].nome, "*") != 0)
               {
                    //Procurando a pasta digitada...
                    for(j = 0; j < GRAU; j++)
                    {
                         //Se o elemento for diferente de 0, verificar o nome
                         if(gerenciaPastas[super_pasta].subpastas[j] != 0)
                         {
                              pos_atual = gerenciaPastas[super_pasta].subpastas[j];
                              //Verificando o nome
                              if(stricmp(gerenciaPastas[pos_atual].nome, pasta_remover) == 0)
                              {
                                   //Removendo sub-pastas associadas
                                   apagaSubPastasAssociadas(gerenciaPastas, pos_atual);
                                   //Removendo pasta (nome)
                                   strcpy(gerenciaPastas[pos_atual].nome, "*");
                                   //Colocando a posição 0 nos elementos associados a essa pasta
                                   memset(gerenciaPastas[pos_atual].subpastas, 0, sizeof(gerenciaPastas[pos_atual].subpastas));
                                   //Colocando a posição 0 na super_pasta
                                   gerenciaPastas[super_pasta].subpastas[j] = 0;
                                   //Acabar com a verificação das super_pastas
                                   verifica = 1;
                                   break;
                              }
                         }
                    }
               }
               //Acrescentando a super pasta
               super_pasta++;
          }
     }
     strcpy(gerenciaPastas[0].nome, raiz);
     return verifica;
}
//Apagar sub-pastas associadas
void apagaSubPastasAssociadas(pastas gerenciaPastas, int pos_atual) 
{
     //Vetor auxiliar contendo máximo de pastas
     int aux_sub[MAXPASTAS];

     //Pegando as posições da pos_atual e salvando no vetor acima
     int i, j = 0, aux = 0;

     //Pegando as posições da pos_atual e salvando no vetor auxilar
     for (i = 0; i < GRAU; i++)
     {
          if (gerenciaPastas[pos_atual].subpastas[i] != 0)
          {
               aux_sub[j] = gerenciaPastas[pos_atual].subpastas[i];
               j++;
          }
     }

     //Verificando todas as sub-pastas das sub-pastas
     while(aux < j)
     {
          pos_atual = aux_sub[aux];
          for(i = 0; i < GRAU; i++)
          {
               if (gerenciaPastas[pos_atual].subpastas[i] != 0)
               {
                    aux_sub[j] = gerenciaPastas[pos_atual].subpastas[i];
                    j++;
               }
          }
          aux++;
     }

     //Varrendo o vetor principal com as posições do auxiliar
     for(i = 0; i < j; i++)
     {
          //Zerando o nome
          strcpy(gerenciaPastas[aux_sub[i]].nome, "*");
          //Zerando as posições associadas
          memset(gerenciaPastas[aux_sub[i]].subpastas, 0, sizeof(gerenciaPastas[aux_sub[i]].subpastas));
          /*
          for (aux = 0; aux < GRAU; aux++)
          {
               gerenciaPastas[aux_sub[i]].subpastas[aux] = 0;
          }*/
     }
}

int main(){

     //Gerenciador de Pastas - SO
     pastas gerenciaPastas;
     
     //Inicialização do Gerenciador
     iniciaGerenciador(gerenciaPastas);
     
     //Criação de Pastas no SO
     criaPastas(gerenciaPastas);     

     //Remoção de Pastas do SO
     char opc;
     do{

          //Mostrando a Hierarquia de Pastas do SO
          mostraPastas(gerenciaPastas);

          //Removendo as Pastas Desejadas
          if(removePastas(gerenciaPastas))
          {
               printf("\nPasta removida com sucesso!\n\n");
          }
          else{
               printf("\nErro ao remover pasta. Tente novamente.\n\n");
          }
          system("pause");
          system("cls");

          printf("\nDeseja remover outra pasta? (S/N)\n");
          do{
               opc = toupper(getch());
          }while(opc != 'S' && opc != 'N');
          system("cls");
     }while(opc == 'S');

     //Mostrando a Hierarquia de Pastas do SO
     mostraPastas(gerenciaPastas);

     return 0;
}