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
#define I4 4 //Extensão

//Estruturas
//Tipos de Processos
typedef struct processo_int
{
     int id;
}Processo_Int;
typedef struct processo_float
{
     float id;
} Processo_Float;
typedef struct processo_nome
{
     char id[16];
} Processo_Nome;
typedef struct processo_extensao
{
     char id[6];
} Processo_Extensao;

//Informações da Fila
typedef struct no_info{
     int tipo;         //Tipo de Processo
     void *id;         //ID do Processo
     struct no_info *prox; //Campo próximo
}No_Info;
//Estrutura da Fila Linear Simplismente Encadeada
typedef struct Descritor{
     No_Info *inicio;
     No_Info *fim;
}*def_fila;
//Estrutura contendo as informações do No (Facilidade)
typedef struct aux_info{
     int tipo;         //Tipo de Processo
     void *id;         //ID do Processo
}*Aux_Info;

//Funções
//Iniciar a Fila
void IniciarFila(def_fila *fila)
{
     (*fila) = (def_fila)malloc(sizeof(struct Descritor));
     (*fila)->inicio = (*fila)->fim = NULL;
}
//Verifica Vazia
int VerificaVazia(def_fila fila)
{
     return (fila->inicio == NULL);
}
//Criação dos Processos
No_Info *Cria_Processo_Int(int id)
{
     Processo_Int *process_int;
     No_Info *q;

     //Alocando o elemento
     process_int = (Processo_Int*)malloc(sizeof(Processo_Int));
     process_int->id = id;

     //Devolvendo a Fila
     q = (No_Info*)malloc(sizeof(struct no_info));
     q->tipo = I1;
     q->id = process_int;
     q->prox = NULL;

     return q;
}
No_Info *Cria_Processo_Float(float id)
{
     Processo_Float *process_float;
     No_Info *q;

     //Alocando o elemento
     process_float = (Processo_Float*)malloc(sizeof(Processo_Float));
     process_float->id = id;

     //Devolvendo a Fila
     q = (No_Info *)malloc(sizeof(No_Info));
     q->tipo = I2;
     q->id = process_float;
     q->prox = NULL;

     return q;
}
No_Info *Cria_Processo_Nome(char *id)
{
     Processo_Nome *process_nome;
     No_Info *q;

     //Alocando o elemento
     process_nome = (Processo_Nome *)malloc(sizeof(Processo_Nome));
     strcpy(process_nome->id, id);

     //Devolvendo a Fila
     q = (No_Info *)malloc(sizeof(No_Info));
     q->tipo = I3;
     q->id = process_nome;
     q->prox = NULL;

     return q;
}
No_Info *Cria_Processo_Extensao(char *id)
{
     Processo_Extensao *process_extensao;
     No_Info *q;

     //Alocando o elemento
     process_extensao = (Processo_Extensao *)malloc(sizeof(Processo_Extensao));
     strcpy(process_extensao->id, id);

     //Devolvendo a Fila
     q = (No_Info *)malloc(sizeof(No_Info));
     q->tipo = I4;
     q->id = process_extensao;
     q->prox = NULL;

     return q;
}
//Enfileirar
void Enfileirar(def_fila *fila, No_Info *info)
{
     //Se estiver vazia, início recebe a informação
     if(VerificaVazia((*fila)))
          (*fila)->inicio = info;
     else //Último elemento aponta pra atual
          (*fila)->fim->prox = info;
     (*fila)->fim = info;
}
//Desenfileirar
int Desenfileirar(def_fila *fila, Aux_Info *info)
{
     if(VerificaVazia((*fila)))
          return 0;
     
     No_Info *q = (*fila)->inicio;

     Aux_Info aux = (Aux_Info)malloc(sizeof(struct aux_info));
     //Armazenando o tipo da informação
     aux->tipo = q->tipo;
     //Verificando tipo de informação
     switch(q->tipo)
     {
          case I1:
               aux->id = q->id;
               break;
          case I2:
               aux->id = q->id;
               break;
          case I3:
               //strcpy(aux->id, q->id);
               aux->id = q->id;
               break;
          case I4:
               //strcpy(aux->id, q->id);
               aux->id = q->id;
               break;
     }

     //Recuperando informações
     (*info) = aux;

     //Removendo início
     if((*fila)->inicio == (*fila)->fim)
          (*fila)->fim = NULL;
     (*fila)->inicio = q->prox;
     free(q);
     return 1;
}


//Visualizar
void Visualizar(def_fila fila)
{
     if (VerificaVazia(fila))
     {
          printf("\nSem processos em espera de execucao.\n\n");
          return;
     }

     printf("\nPROCESSOS EM FILA\n\n\n");
     printf("TIPO DO PROCESSO (INT/FLOAT)/NOME DO PROCESSO/EXTENSAO DO PROCESSO\n\n");
     No_Info *q = fila->inicio;
     Processo_Int *process_int;
     Processo_Float *process_float;
     /*Processo_Nome *process_nome;
     Processo_Extensao *process_extensao;*/

     while (q)
     {
          //Captando informações
          switch (q->tipo)
          {
          //Int
          case I1:
               process_int = (Processo_Int*)q->id;
               printf("%d  ", process_int->id);
               break;
          //Float
          case I2:
               process_float = (Processo_Float*)q->id;
               printf("%.2f  ", process_float->id);
               break;
          //Nome
          case I3:
               /*strcpy(process_nome, (Processo_Nome *)q->id);
               printf("%s ", process_nome->id);*/
               printf("%s  ", q->id);
               break;
          //Extensão
          case I4:
               /*strcpy(process_extensao, (Processo_Extensao *)q->id);
               printf("%s ", process_extensao->id);*/
               printf("%s  ", q->id);
               break;
          }
          q = q->prox;
     }
     printf("\n\n");
}
//Visualizar: Desenfileirar
void VisualizarDesenfileira(Aux_Info aux)
{
     
     //Declarar cada tipo para printar
     Processo_Int *process_int;
     Processo_Float *process_float;
     /*Processo_Nome *process_nome;
     Processo_Extensao *process_extensao;*/

     printf("TIPO DO PROCESSO (INT/FLOAT)/NOME DO PROCESSO/EXTENSAO DO PROCESSO\n\n");
     switch(aux->tipo)
     {
     //Int
     case I1:
          process_int = (Processo_Int*)aux->id;
          printf("%d  ", process_int->id);
          break;
     //Float
     case I2:
          process_float = (Processo_Float*)aux->id;
          printf("%.2f  ", process_float->id);
          break;
     //Nome
     case I3:
          printf("%s  ", aux->id);
          break;
     //Extensão
     case I4:
          printf("%s  ", aux->id);
          break;
     }
}

int main()
{
     //Criando a Fila de Processos
     def_fila processos;
     IniciarFila(&processos);
     //Célula da Fila para Dados e Alocação
     No_Info *info;
     //Auxiliar para Captação dos Dados (Remoção)
     Aux_Info aux; 

     //Auxiliares para Captação da Dados
     int tipo_dado, id_inteiro;
     float id_float;
     char nome[16], extensao[6];
     //Auxiliar para manipulação das opções
     char opc_menu, opc_func;

     while (opc_menu != ESC)
     {
          printf("\nSistema Operacional - FILA DE PROCESSOS\n\n");
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
                    system("cls");
                    printf("\nINSERIR PROCESSO\n\n");
                    printf("TIPO DE PROCESSO:\n\n");
                    printf("\t1 - INTEIRO\n\n");
                    printf("\t2 - FLOAT\n\n");
                    printf("\t3 - NOME\n\n");
                    printf("\t4 - EXTENSAO\n\n");
                    printf("Digite o tipo de processo a ser inserido: ");
                    do
                    {
                         scanf("%d", &tipo_dado);
                    } while (tipo_dado < 1 || tipo_dado > 4);
                    fflush(stdin);
                    system("cls");
                    switch (tipo_dado)
                    {
                    case I1:
                         printf("\nINSERIR PROCESSO - INTEIRO\n\n");
                         printf("Digite o identificador do processo (inteiro): ");
                         scanf("%d", &id_inteiro);
                         fflush(stdin);
                         system("cls");
                         printf("\nInserindo processo. Aguarde...\n\n");
                         //Alocando elementos
                         info = Cria_Processo_Int(id_inteiro);
                         printf("\nProcesso inserido com sucesso!\n\n");
                         break;
                    case I2:
                         printf("\nINSERIR PROCESSO - FLOAT\n\n");
                         printf("Digite o identificador do processo (float): ");
                         scanf("%f", &id_float);
                         fflush(stdin);
                         system("cls");
                         printf("\nInserindo processo. Aguarde...\n\n");
                         //Alocando elementos
                         info = Cria_Processo_Float(id_float);
                         printf("\nProcesso inserido com sucesso!\n\n");
                         break;
                    case I3:
                         printf("\nINSERIR PROCESSO - NOME\n\n");
                         printf("Digite o identificador do processo (nome): ");
                         gets(nome);
                         fflush(stdin);
                         system("cls");
                         printf("\nInserindo processo. Aguarde...\n\n");
                         //Alocando elementos
                         info = Cria_Processo_Nome(nome);
                         printf("\nProcesso inserido com sucesso!\n\n");
                         break;
                    case I4:
                         printf("\nINSERIR PROCESSO - EXTENSAO\n\n");
                         printf("Digite o identificador do processo (extensao): ");
                         gets(extensao);
                         fflush(stdin);
                         system("cls");
                         printf("\nInserindo processo. Aguarde...\n\n");
                         //Alocando elementos
                         info = Cria_Processo_Extensao(extensao);
                         printf("\nProcesso inserido com sucesso!\n\n");
                         break;
                    }
                    //Enfileirando
                    Enfileirar(&processos, info);
                    system("pause");
                    system("cls");
                    printf("\nDeseja inserir outro processo? (S/N)\n");
                    do
                    {
                         opc_func = toupper(getch());
                    } while (opc_func != 'S' && opc_func != 'N');
               } while (opc_func != 'N');
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
                    if (opc_func == 'S')
                    {
                         system("cls");
                         printf("\nRemovendo o processo. Aguarde...\n\n");
                         if (Desenfileirar(&processos, &aux))
                         {
                              VisualizarDesenfileira(aux);
                              printf("\n\n\nProcesso acima removido com sucesso!\n\n");
                         }
                         else
                         {
                              printf("Erro ao remover processo. Tente novamente.\n\n");
                              opc_func = 'N';
                         }
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