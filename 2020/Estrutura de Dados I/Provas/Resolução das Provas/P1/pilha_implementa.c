/**/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define MAX_JOGO_COPOS 40
#define MAX_ESTEIRA 5
#define MAX_CAIXA_TRANSPORTE 10

typedef struct
{
     int id_fabrica;
     int modelo_copo;
     int qtd; //6 ou 8
} jogo_copos;
typedef struct no_pilha
{
     jogo_copos dados;
     struct no_pilha *prox;
} * def_pilha;

typedef def_pilha modelos[MAX_ESTEIRA];
typedef def_pilha modelos_quantidade[MAX_ESTEIRA][2];
typedef def_pilha caixas_transporte[MAX_CAIXA_TRANSPORTE];

//Rotinas Básicas
int verificaVazia(def_pilha pilha)
{
     return (pilha == NULL);
}

char *RetornaNome(int modelo)
{
     switch (modelo)
     {
     case 1:
          return "Bristol";
          break;
     case 2:
          return "Oca";
          break;

     case 3:
          return "Brisa";
          break;

     case 4:
          return "Capri";
          break;

     case 5:
          return "Estrela";
          break;
     }
}

//2A
void empilhar(def_pilha *pilha, jogo_copos info)
{
     //Alocar memória
     def_pilha p = (def_pilha)malloc(sizeof(struct no_pilha));

     p->dados = info;
     p->prox = (*pilha);
     (*pilha) = p;
}
int desempilhar(def_pilha *pilha, jogo_copos *info)
{
     //Necessário verificar se pilha está vazia
     if (verificaVazia((*pilha)))
     {
          return 0;
     }

     (*info) = (*pilha)->dados;
     def_pilha p = (*pilha);
     (*pilha) = (*pilha)->prox;
     free(p);

     return 1;
}

//2B
void FuncionarioX1(def_pilha *esteira, modelos *modelo)
{
     int i;
     for (i = 0; i < MAX_ESTEIRA; i++)
     {
          (*modelo)[i] = NULL;
     }

     jogo_copos info;
     while (desempilhar(esteira, &info))
     {
          //Empilhando em modelos
          empilhar(&(*modelo)[info.modelo_copo - 1], info);
     }
}
//2C
void FuncionarioX2(modelos *modelo, modelos_quantidade *modelo_qtd)
{
     int i, j;
     for (i = 0; i < MAX_ESTEIRA; i++)
     {
          for (j = 0; j < 2; j++)
          {
               (*modelo_qtd)[i][j] = NULL;
          }
     }

     jogo_copos info;
     for (i = 0; i < MAX_ESTEIRA; i++)
     {
          while (desempilhar(&((*modelo)[i]), &info))
          {
               //Empilhar nas quantidades
               if (info.qtd == 6)
               {
                    empilhar(&(*modelo_qtd)[i][0], info);
               }
               else if (info.qtd == 8)
               {
                    empilhar(&(*modelo_qtd)[i][1], info);
               }
          }
     }
}
//2D
void FuncionarioX3(modelos_quantidade *modelo_qtd, caixas_transporte *caixa_transporte)
{
     int i;
     for (i = 0; i < MAX_CAIXA_TRANSPORTE; i++)
     {
          (*caixa_transporte)[i] = NULL;
     }

     jogo_copos info;
     int j, k = 0, l = 0;
     for (i = 0; i < 2; i++)
     {
          for (j = 0; j < MAX_ESTEIRA; j++)
          {
               while (desempilhar(&((*modelo_qtd)[j][i]), &info))
               {
                    if (k == 4)
                    {
                         k = 0;
                         l++;
                    }
                    empilhar(&((*caixa_transporte)[l]), info);
                    k++;
               }
          }
     }
}
//2E
int VerificaEspecificacoes(def_pilha espec[])
{
     int i, j;
     int cont = 0; //Contador de iguais
     for (i = 0; i < 3; i++)
     {
          for (j = i + 1; j < 4; j++)
          {
               if (espec[i]->dados.id_fabrica ==
                       espec[j]->dados.id_fabrica &&
                   espec[i]->dados.modelo_copo ==
                       espec[j]->dados.modelo_copo &&
                   espec[i]->dados.qtd ==
                       espec[j]->dados.qtd)
               {
                    cont++;
               }
          }
     }

     return cont;
}
void FuncionarioX4(caixas_transporte *caixas_transporte)
{
     def_pilha aux[4];
     int i;
     for (i = 0; i < 4; i++)
     {
          aux[i] = NULL;
     }
     jogo_copos info;
     int j = 0, k, cont = 0;
     for (i = 0; i < MAX_CAIXA_TRANSPORTE; i++)
     {
          while (desempilhar(&((*caixas_transporte)[i]), &info))
          {
               empilhar(&aux[j++], info);
          }
          j = 0;

          //Verificando especificações e acrescentando no contador
          cont = VerificaEspecificacoes(aux);
          if(cont == 4)
          {
               printf("\nCaixa de Transporte %d esta com as mesmas especificacoes.\n\n", i + 1);
          }
          else
          {
               printf("\nCaixa de Transporte %d NAO esta com as mesmas especificacoes.\n\n", i + 1);
          }

          //Empilhando de volta as caixas de transporte
          while(desempilhar(&aux[j++], &info))
          {
               empilhar(&((*caixas_transporte)[i]), info);
          }
          j = 0;
          
     }

}

//2F
void MostraEsteira(def_pilha esteira)
{
     if (esteira == NULL)
     {
          printf("Esteira vazia.\n\n");
          return;
     }

     while (esteira)
     {
          printf("ID de Fabrica: %d\n", esteira->dados.id_fabrica);
          printf("Modelo: %s\n", RetornaNome(esteira->dados.modelo_copo));
          printf("Quantidade: %d\n\n", esteira->dados.qtd);
          esteira = esteira->prox;
     }
     printf("\n");
}
//2G
void MostraModelo(modelos modelo)
{
     int i;
     for (i = 0; i < MAX_ESTEIRA; i++)
     {
          if (modelo[i] == NULL)
          {
               printf("Mesa vazia.\n\n");
          }
          else
          {
               while (modelo[i])
               {
                    printf("Mesa %d\n", i + 1);
                    printf("ID de Fabrica: %d\n", modelo[i]->dados.id_fabrica);
                    printf("Modelo: %s\n", RetornaNome(modelo[i]->dados.modelo_copo));
                    printf("Quantidade: %d\n\n", modelo[i]->dados.qtd);
                    modelo[i] = modelo[i]->prox;
               }
               printf("\n");
          }
     }
}
//2H
void MostraModeloQuantidade(modelos_quantidade modelo_qtd)
{
     int i, j;
     for (i = 0; i < 2; i++)
     {
          for (j = 0; j < MAX_ESTEIRA; j++)
          {
               if (modelo_qtd[j][i] == NULL)
               {
                    printf("Mesa vazia.\n\n");
               }
               else
               {
                    while (modelo_qtd[j][i])
                    {
                         printf("Mesa %d\n", j + 1);
                         printf("ID de Fabrica: %d\n", modelo_qtd[j][i]->dados.id_fabrica);
                         printf("Modelo: %s\n", RetornaNome(modelo_qtd[j][i]->dados.modelo_copo));
                         printf("Quantidade: %d\n\n", modelo_qtd[j][i]->dados.qtd);
                         modelo_qtd[j][i] = modelo_qtd[j][i]->prox;
                    }
                    printf("\n\n");
               }
          }
     }
}
//2I
void MostraCaixaTransporte(caixas_transporte caixa_transporte)
{
     int i;
     jogo_copos info;
     for (i = 0; i < MAX_CAIXA_TRANSPORTE; i++)
     {
          while (desempilhar(&(caixa_transporte[i]), &info))
          {
               printf("Caixa de Transporte %d\n", i + 1);
               printf("ID de Fabrica: %d\n", info.id_fabrica);
               printf("Modelo: %s\n", RetornaNome(info.modelo_copo));
               printf("Quantidade: %d\n\n", info.qtd);
          }
          printf("\n\n");
     }
}

int main()
{
     //Dados
     jogo_copos dados;

     //Estrutura da Esteira (Pilha)
     def_pilha esteira;
     esteira = NULL;

     //I) Estrutura do Final da Esteira (por modelo)
     modelos modelo;

     //II) Estrutura da Separação por Modelo e Quantidade
     modelos_quantidade modelo_quantidade;

     //III) Estrutura da Caixa de Transporte (<= 4 jogos para cada posição do vetor)
     caixas_transporte caixa_transporte;

     //Auxiliares
     int i = 0, j = 1, aux = 1;
     int id_fabrica, modelo_copo, qtd_embalagem;
     char opc_esteira = 'S';

     //Iniciando Menu
     while (opc_esteira != 'N')
     {
          fflush(stdin);
          printf("\nFabrica de Copos - Nadir Figueiredo\n");
          printf("Insercao de jogo de copos na esteira\n\n");
          printf("Jogo de Copos %d\n\n", aux++);

          printf("\nDigite o ID do Local de Fabrica: ");
          scanf("%d", &id_fabrica);

          printf("Digite o modelo do copo: ");
          scanf("%d", &modelo_copo);

          printf("Digite a qtd na embalagem (6 ou 8): ");
          scanf("%d", &qtd_embalagem);

          //Inserindo no "Cliente"
          dados.id_fabrica = id_fabrica;
          dados.modelo_copo = modelo_copo;
          dados.qtd = qtd_embalagem;

          printf("\nJogo de Copo enfileirado\n");
          printf("Deseja inserir outro? (S/N)");
          opc_esteira = toupper(getch());

          //Enfileirando
          empilhar(&esteira, dados);
          system("cls");
     }

     printf("\nFabrica de Copos - Nadir Figueiredo\n");
     printf("Esteira Atual\n\n");
     MostraEsteira(esteira);
     system("pause");
     system("cls");

     //Funcionário X1
     printf("\nFabrica de Copos - Nadir Figueiredo\n");
     printf("Funcionario X1\n\n");
     FuncionarioX1(&esteira, &modelo);
     MostraModelo(modelo);
     system("pause");
     system("cls");

     //Funcionário X2
     printf("\nFabrica de Copos - Nadir Figueiredo\n");
     printf("Funcionario X2\n\n");
     FuncionarioX2(&modelo, &modelo_quantidade);
     MostraModeloQuantidade(modelo_quantidade);
     system("pause");
     system("cls");

     //Funcionário X3
     printf("\nFabrica de Copos - Nadir Figueiredo\n");
     printf("Funcionario X3\n\n");
     FuncionarioX3(&modelo_quantidade, &caixa_transporte);
     MostraCaixaTransporte(caixa_transporte);
     system("pause");
     system("cls");

     //Funcionário X4
     printf("\nFabrica de Copos - Nadir Figueiredo\n");
     printf("Funcionario X4\n\n");
     FuncionarioX4(&caixa_transporte);
     
     system("pause");

     return 0;
}