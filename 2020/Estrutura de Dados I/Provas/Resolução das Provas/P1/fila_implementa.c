/**/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define MAX 20

typedef struct
{
     int id_prod;
     int qtd;
} def_produto;
typedef struct
{
     def_produto produto[MAX];
     int pre_processa;   //Verificar se é pré-processado
     int qtd_total_prod; //Qtd. total de produtos (economizar tempo ao invés de percorrer vetor)
     int cont_prod;      //Qtd. de posições produtos (percorrer o vetor acima)
} def_cliente;

//A
typedef struct no_fila
{
     def_cliente cliente;
     struct no_fila *prox;
} * def_fila;

//Rotinas Básicas
int verificaVazia(def_fila Fim)
{
     return (Fim == NULL);
}

//B
void enfileirar(def_fila *Fim, def_cliente cliente)
{
     def_fila p = (def_fila)malloc(sizeof(struct no_fila));
     p->cliente = cliente;

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

//C
int desenfileirar(def_fila *Fim, def_cliente *cliente)
{
     if (verificaVazia((*Fim)))
     {
          return 0;
     }

     (*cliente) = (*Fim)->prox->cliente;
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
     return 1;
}

//Verificação de Tempo
int TempoProduto(int id)
{
     if (id == 1 || id == 2)
          return 20;
     else if (id == 3)
          return 10;
     else if (id == 4 || id == 5)
          return 150;
     else if (id == 6 || id == 7)
          return 50;
     else if (id == 8 || id == 9)
          return 100;
     else if (id == 10)
          return 300;
     else
          return 0;
}

//Calcular tempo de um Cliente
int CalculaTempoCliente(def_cliente Cliente)
{
     int i, tempo_total, tempo_id;
     tempo_total = 0;

     for (i = 0; i < Cliente.cont_prod; i++)
     {
          tempo_id = TempoProduto(Cliente.produto[i].id_prod);
          tempo_total += (tempo_id * Cliente.produto[i].qtd);
     }
     return tempo_total;
}

//D: 1° Simulação
int PrimeiraSimulacao(def_fila *Fim)
{
     //Separação em outras duas filas
     def_fila fila_aux1, fila_aux2;
     fila_aux1 = fila_aux2 = NULL;

     //Tempo de Cada Fila
     int tempo_fila1, tempo_fila2;
     tempo_fila1 = tempo_fila2 = 0;

     //Tempo Total
     int tempo_total = 0;

     def_cliente cliente_aux;
     while (desenfileirar(&(*Fim), &cliente_aux))
     {
          //Clientes com até 10 itens (inclusivo)
          if (cliente_aux.qtd_total_prod <= 10)
          {
               enfileirar(&fila_aux1, cliente_aux);
          }
          //Clientes com mais de 10 itens
          else
          {
               enfileirar(&fila_aux2, cliente_aux);
          }
     }

     //Calculando tempo das filas
     while (desenfileirar(&fila_aux1, &cliente_aux))
     {
          tempo_fila1 += CalculaTempoCliente(cliente_aux);
     }
     while (desenfileirar(&fila_aux2, &cliente_aux))
     {
          tempo_fila2 += CalculaTempoCliente(cliente_aux);
     }

     //Tempo total
     tempo_total = tempo_fila1 + tempo_fila2;

     return tempo_total;
}

//E: 2° Simulação
int SegundaSimulacao(def_fila *Fim)
{
     //Separação em outras duas filas
     def_fila fila_aux1, fila_aux2;
     fila_aux1 = fila_aux2 = NULL;

     //Tempo de Cada Fila
     int tempo_fila1, tempo_fila2;
     tempo_fila1 = tempo_fila2 = 0;

     //Tempo Total
     int tempo_total = 0;

     def_cliente cliente_aux;
     int tempo_cliente = 0;
     while (desenfileirar(&(*Fim), &cliente_aux))
     {
          tempo_cliente = CalculaTempoCliente(cliente_aux);

          //Clientes que fizeram pré-processamento e que a soma do tempo dê menor que 500s
          if (cliente_aux.pre_processa == 1 && (tempo_cliente / 2) < 500)
          {
               enfileirar(&fila_aux1, cliente_aux);
          }
          //Clientes sem pré-processamento ou que a soma tenha dado maior ou igual a 500s
          else
          {
               enfileirar(&fila_aux2, cliente_aux);
          }
     }

     //Calculando tempo das filas
     while (desenfileirar(&fila_aux1, &cliente_aux))
     {
          tempo_fila1 += CalculaTempoCliente(cliente_aux);
     }
     while (desenfileirar(&fila_aux2, &cliente_aux))
     {
          //Desconsiderando tempo dos pré-processados
          if (cliente_aux.pre_processa == 1)
          {
               tempo_cliente = CalculaTempoCliente(cliente_aux);
               tempo_cliente /= 2;
               tempo_fila2 += tempo_cliente;
          }
          else
          {
               tempo_fila2 += CalculaTempoCliente(cliente_aux);
          }
     }

     //Tempo total
     tempo_total = (tempo_fila1 / 2) + tempo_fila2;

     return tempo_total;
}

//F: 3° Simulação
int TerceiraSimulacao(def_fila *Fim)
{
     //Separação em outras duas filas
     def_fila fila_aux1, fila_aux2, fila_aux3;
     fila_aux1 = fila_aux2 = fila_aux3 = NULL;

     //Tempo de Cada Fila
     int tempo_fila1, tempo_fila2, tempo_fila3;
     tempo_fila1 = tempo_fila2 = tempo_fila3 = 0;

     //Tempo Total
     int tempo_total = 0;

     def_cliente cliente_aux;
     int tempo_cliente = 0;
     while (desenfileirar(&(*Fim), &cliente_aux))
     {
          //Clientes com até 10 itens (inclusivo)
          if (cliente_aux.qtd_total_prod <= 10)
          {
               enfileirar(&fila_aux1, cliente_aux);
          }
          //Clientes com pré-processamento
          else if (cliente_aux.pre_processa == 1)
          {
               enfileirar(&fila_aux2, cliente_aux);
          }
          //Clientes sem pré-processamento ou mais de 10 itens
          else
          {
               enfileirar(&fila_aux3, cliente_aux);
          }
     }

     //Calculando tempo das filas
     while (desenfileirar(&fila_aux1, &cliente_aux))
     {
          //Desconsiderando tempo dos pré-processados
          if (cliente_aux.pre_processa == 1)
          {
               tempo_cliente = CalculaTempoCliente(cliente_aux);
               tempo_cliente /= 2;
               tempo_fila1 += tempo_cliente;
          }
          else
          {
               tempo_fila1 += CalculaTempoCliente(cliente_aux);
          }
     }
     while (desenfileirar(&fila_aux2, &cliente_aux))
     {
          tempo_fila2 += CalculaTempoCliente(cliente_aux);
     }
     while (desenfileirar(&fila_aux3, &cliente_aux))
     {
          tempo_fila3 += CalculaTempoCliente(cliente_aux);
     }

     //Tempo total
     tempo_total = tempo_fila1 + (tempo_fila2 / 2) + tempo_fila3;

     return tempo_total;
}

//Iniciação de Cliente
void IniciaCliente(def_cliente *Cliente)
{
     (*Cliente).pre_processa = 0;
     (*Cliente).qtd_total_prod = 0;
     (*Cliente).cont_prod = 0;
}

int main()
{

     //Produto
     int id_prod = -1, qtd_prod;

     //Cliente
     def_cliente cliente;
     IniciaCliente(&cliente);

     //Filas de Simulação
     def_fila Fila1, Fila2, Fila3;
     Fila1 = Fila2 = Fila3 = NULL;

     //Auxiliares
     int i = 0, j = 1, aux = 1;
     char opc_prod, opc_cliente = 'S', pre_processa;

     //Iniciando Menu
     while (opc_cliente != 'N')
     {
          fflush(stdin);
          printf("\nAtendimento da Fila - Supermercado Bauru\n");
          printf("Identificacao dos clientes e produtos comprados\n\n");
          printf("Cliente %d\n\n", aux++);
          printf("Eh pre-processado? (S/N): ");
          pre_processa = toupper(getch());
          if (pre_processa == 'S')
          {
               cliente.pre_processa = 1;
          }

          i = 0;
          j = 1;
          do
          {
               printf("\n\nProduto %d", j++);
               printf("\nDigite o ID do Produto: ");
               scanf("%d", &id_prod);

               printf("Digite a quantidade desse produto (> 0): ");
               scanf("%d", &qtd_prod);

               //Inserindo no "Cliente"
               cliente.qtd_total_prod += qtd_prod;
               cliente.produto[i].id_prod = id_prod;
               cliente.produto[i++].qtd = qtd_prod;
               cliente.cont_prod = i;

               printf("\nProduto armazenado.\n");
               printf("Deseja inserir outro produto para esse cliente? (S/N)");
               opc_prod = toupper(getch());
          } while (opc_prod != 'N');

          //Enfileirando
          enfileirar(&Fila1, cliente);
          enfileirar(&Fila2, cliente);
          enfileirar(&Fila3, cliente);

          //Perguntando se deseja mais um cliente
          printf("\n\nCliente inserido com sucesso na fila.\n");
          printf("Deseja inserir outro cliente? (S/N)");
          opc_cliente = toupper(getch());
          system("cls");
     }

     printf("\nAtendimento da Fila - Supermercado Bauru\n");
     printf("Simulacoes\n\n");

     printf("Primeira Simulacao: %d segundo(s)\n", PrimeiraSimulacao(&Fila1));
     printf("Segunda Simulacao: %d segundo(s)\n", SegundaSimulacao(&Fila2));
     printf("Terceira Simulacao: %d segundo(s)\n\n", TerceiraSimulacao(&Fila3));

     system("pause");
     return 0;
}