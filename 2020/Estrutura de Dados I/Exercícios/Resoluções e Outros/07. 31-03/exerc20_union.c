/*Criado por Davi Augusto - BCC - UNESP Bauru*/
/*
Existem partes de sistemas operacionais que cuidam da ordem em que os programas devem ser
executados. Por exemplo, em um sistema de computação de tempo compartilhado (do inglês timeshared)
existe a necessidade de manter um conjunto de processos em uma fila, esperando para
serem executados. 
Escreva um programa que seja capaz de ler uma série de solicitações para: 
(i) incluir novos processos na fila de processos; 
(ii) retirar da fila o processo com o maior tempo de espera; 
(iii) imprimir o conteúdo da lista de processos em determinado momento. 

Assuma que cada processo é representado por um número identificador do processo.

Identificadores:
1 - int
2 - float

Além disso, deve-se ter o nome do processo (máx. 15 carac.)
e o tipo de documento (máx. 4 carac.)
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define ESC 27

//Definições dos Identificadores
#define I1 1 //Int
#define I2 2 //Float
#define I3 3 //Nome
#define I4 4 //Extensao

//Estruturas
//Union: identificador
typedef union
{
     int int_id;
     float float_id;
     char nome_id[16];
     char extensao_id[5];
}no_id;

//Estrutura com informações em cada célula
typedef struct no_info
{
     int tipo;             //Tipo do processo
     no_id id;             //ID do processo

     struct no_info *prox; //Campo próximo
} no_fila;

//Declaração da Fila (Linear Simplismente Encadeada)
typedef struct
{
     no_fila *inicio, *fim;
} def_fila;
//Estrutura Auxiliar para Captar Células de informação (Facilidade)
typedef struct aux_info
{
     int tipo;         //Tipo do processo (1 - int/2 - float)
     no_id id;         //ID do processo
}*Aux_Info;

//Funções
//Verifica Vazia
int VerificaVazia(def_fila fila)
{
     return (fila.inicio == NULL);
}
//Enfileirar
void Enfileirar(def_fila *fila, Aux_Info info)
{
     //Criar Nó
     no_fila *q = (no_fila *)malloc(sizeof(no_fila));
     //Armazenando informações
     q->tipo = info->tipo;
     q->id = info->id;
     //strcpy(q->nome, info->nome);
     //strcpy(q->extensao, info->extensao);
     //Campo próximo
     q->prox = NULL;

     //Se estiver vazia, o início aponta pro elemento
     if(VerificaVazia((*fila)))
          (*fila).inicio = q;
     else //Do contrário, o último deve apontar para "q"
          (*fila).fim->prox = q;
     
     (*fila).fim = q;
}
//Desenfileirar
int Desenfileirar(def_fila *fila, Aux_Info *info)
{
     //Se estiver vazia, retorna falso
     if(VerificaVazia((*fila)))
          return 0;

     no_fila *q = (*fila).inicio; //Auxiliar
     
     //Recuperando informações
     (*info)->tipo = q->tipo;
     (*info)->id = q->id;
     //strcpy((*info)->nome, q->nome);
     //strcpy((*info)->extensao, q->extensao);

     //Se tiver só um elemento
     if((*fila).inicio == (*fila).fim)
          (*fila).fim = NULL;
     //Avançando início
     (*fila).inicio = q->prox;
     free(q);
     return 1;
}
//Visualizar
void Visualizar(def_fila fila)
{
     if(VerificaVazia(fila))
     {
          printf("\nSem processos em espera de execucao.\n\n");
          return;
     }

     printf("\nPROCESSOS EM FILA\n\n\n");
     printf("TIPO DO PROCESSO (INT/FLOAT)/NOME DO PROCESSO/EXTENSAO DO PROCESSO\n\n");
     no_fila *q = fila.inicio;
     while(q)
     {
          //Captando informações
          switch(q->tipo)
          {
               //Int
               case I1:
                    //printf("%d\t%s.%s", q->id.int_id, q->nome, q->extensao);
                    printf("%d ", q->id.int_id);
                    break;
               //Float
               case I2:
                    //printf("%.2f\t%s.%s", q->id.float_id, q->nome, q->extensao);
                    printf("%.2f ", q->id.float_id);
                    break;
               //Nome
               case I3:
                    printf("%s ", q->id.nome_id);
                    break;
               //Extensão
               case I4:
                    printf("%s ", q->id.extensao_id);
                    break;
          }
          q = q->prox;
     }
     printf("\n\n");
}


int main()
{
     //Declaração da Fila de Processos
     def_fila processos;
     processos.inicio = processos.fim = NULL;
     //Declaração de Auxiliar para Informações
     Aux_Info info;
     //Auxiliar para Tipo de Dado
     int tipo_dado;
     //Auxiliar para manipulação das opções
     char opc_menu, opc_func;

     while (opc_menu != ESC)
     {
          printf("\nSISTEMA OPERACIONAL - FILA DE PROCESSOS\n\n");
          printf("1 - Incluir um Processo\n");
          printf("2 - Retirar um Processo\n");
          printf("3 - Visualizar os Processos\n");
          printf("\nESC - Sair\n\n");
          printf("Sua opcao: ");
          opc_menu = toupper(getch());
          system("cls");
          if (opc_menu == ESC)
               break;
          switch (opc_menu)
          {
          case '1':
               do
               {
                    //Alocando o Dado
                    info = (Aux_Info)malloc(sizeof(struct aux_info));
                    system("cls");
                    printf("\nINSERIR PROCESSO\n\n");
                    printf("TIPO DE PROCESSO:\n\n");
                    printf("\t1 - INTEIRO\n\n");
                    printf("\t2 - FLOAT\n\n");
                    printf("\t3 - NOME\n\n");
                    printf("\t4 - EXTENSAO\n\n");
                    printf("Digite o tipo de processo a ser inserido: ");
                    do{
                         scanf("%d", &tipo_dado);
                    } while (tipo_dado < 1 || tipo_dado > 4);
                    info->tipo = tipo_dado;
                    fflush(stdin);
                    system("cls");
                    switch (tipo_dado)
                    {
                         case I1:
                              printf("\nINSERIR PROCESSO - INTEIRO\n\n");
                              printf("Digite o identificador do processo (inteiro): ");
                              scanf("%d", &info->id.int_id);
                              fflush(stdin);
                              system("cls");
                              printf("\nInserindo processo. Aguarde...\n\n");
                              //Enfileirando
                              Enfileirar(&processos, info);
                              printf("\nProcesso inserido com sucesso!\n\n");
                              break;
                         case I2:
                              printf("\nINSERIR PROCESSO - FLOAT\n\n");
                              printf("Digite o identificador do processo (float): ");
                              scanf("%f", &info->id.float_id);
                              fflush(stdin);
                              system("cls");
                              printf("\nInserindo processo. Aguarde...\n\n");
                              //Enfileirando
                              Enfileirar(&processos, info);
                              printf("\nProcesso inserido com sucesso!\n\n");
                              break;
                         case I3:
                              printf("\nINSERIR PROCESSO - NOME\n\n");
                              printf("Digite o identificador do processo (nome): ");
                              gets(info->id.nome_id);
                              fflush(stdin);
                              system("cls");
                              printf("\nInserindo processo. Aguarde...\n\n");
                              //Enfileirando
                              Enfileirar(&processos, info);
                              printf("\nProcesso inserido com sucesso!\n\n");
                              break;
                         case I4:
                              printf("\nINSERIR PROCESSO - NOME\n\n");
                              printf("Digite o identificador do processo (extensao): ");
                              gets(info->id.extensao_id);
                              fflush(stdin);
                              system("cls");
                              printf("\nInserindo processo. Aguarde...\n\n");
                              //Enfileirando
                              Enfileirar(&processos, info);
                              printf("\nProcesso inserido com sucesso!\n\n");
                              break;
                    }
                    system("pause");
                    system("cls");
                    printf("\nDeseja inserir outro processo? (S/N)\n");
                    do{
                         opc_func = toupper(getch());
                    }while(opc_func != 'S' && opc_func != 'N');
                    free(info);
               }while(opc_func != 'N');
               break;
          case '2':
               do
               {
                    system("cls");
                    printf("\nREMOVER PROCESSO\n\n");
                    printf("Deseja executar (remover) o primeiro processo? (S/N)\n");
                    do
                    {
                         opc_func = toupper(getch());
                    } while (opc_func != 'S' && opc_func != 'N');
                    if(opc_func == 'S')
                    {
                         system("cls");
                         printf("\nRemovendo o processo. Aguarde...\n\n");
                         //Alocando o Dado
                         info = (Aux_Info)malloc(sizeof(struct aux_info));
                         if(Desenfileirar(&processos, &info))
                         {
                              printf("TIPO DO PROCESSO (INT/FLOAT)/NOME DO PROCESSO/EXTENSAO DO PROCESSO\n\n");
                              //Captando informações
                              switch (info->tipo)
                              {
                              //Int
                              case I1:
                                   //printf("%d\t%s.%s", q->id.int_id, q->nome, q->extensao);
                                   printf("%d", info->id.int_id);
                                   break;
                              //Float
                              case I2:
                                   printf("%.2f", info->id.float_id);
                                   break;
                              //Nome
                              case I3:
                                   printf("%s", info->id.nome_id);
                                   break;
                              //Extensão
                              case I4:
                                   printf("%s", info->id.extensao_id);
                                   break;
                              }
                              printf("\n\n\n");
                              printf("Processo removido com sucesso!\n\n");
                         
                         }
                         else{
                              printf("Erro ao remover processo. Tente novamente.\n\n");
                              opc_func = 'N';
                         }
                         free(info);
                         system("pause");
                    }
               } while (opc_func != 'N');
               break;
          case '3':
               Visualizar(processos);
               system("pause");
               break;
          default:
               printf("\nOpcao incorreta. Tente novamente.\n\n");
               printf("Retornando ao menu...\n");
               Sleep(3000);
               break;
          }
          system("cls");
     }

     return 0;
}