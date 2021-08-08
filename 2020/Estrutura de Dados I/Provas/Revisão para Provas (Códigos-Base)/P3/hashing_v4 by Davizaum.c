/*Criado por Davi Augusto - BCC - UNESP Bauru*/
/**/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define MAX 100
#define MAX2 30 //26/05/2020

//26/05/2020
//Tratamento de Colisões
struct lista
{
     int info;
     struct lista *prox;
};
typedef struct lista *def_lista;

def_lista cria_no(int nro)
{
     def_lista no = (def_lista)malloc(sizeof(struct lista));
     no->info = nro;
     no->prox = NULL;
     return no;
}
void imprime_lista_recurs(def_lista *Lista)
{
     if (*Lista == NULL)
     {
          printf("NULO");
          return;
     }
     printf("%d\t", (*Lista)->info);
     imprime_lista_recurs(&((*Lista)->prox));
}

//13/05/2020
//-----------------------------------------------------------------------------------------------------------//
//Funções do Hashing
//Divisão (Inteira)
int DivisaoInteira(int chave, int M)
{
     return (chave % M);
}

//Meio-Quadrado***
int MeioQuadrado(unsigned long int chave_quad, int M)
{
     //Convertendo para String
     char nova_chave[MAX];
     sprintf(nova_chave, "%lu", chave_quad);

     printf("\n%s\n", nova_chave);

     //Recuperando o tamanho de dígitos
     int num_digitos_quad = strlen(nova_chave);

     //Com isso, recuperar a posição do meio
     int meio = (num_digitos_quad / 2);
     if (num_digitos_quad % 2 == 0)
          meio--;

     //Recuperando qtd dígitos do limite de M
     int limite = M - 1;
     char aux_limite[MAX];
     sprintf(aux_limite, "%d", limite);
     int num_digitos_tabela = strlen(aux_limite);

     //Guardando dígitos necessários
     int contador_digitos = 1; //Sempre começa com valor do meio
     char fila_esq[MAX], fila_dir[MAX];
     int indice_esq = 0, indice_dir = 0;
     int meio_esq = meio - 1, meio_dir = meio + 1;

     //Iniciando strings
     fila_esq[0] = fila_dir[0] = '\0';

     while (contador_digitos < num_digitos_tabela)
     {
          //Verificando sempre a partir do meio, e salvando nas auxiliares
          if (meio_esq > 0)
          {
               fila_esq[indice_esq++] = nova_chave[meio_esq--];
               contador_digitos++;
          }
          if (meio_dir < strlen(nova_chave))
          {
               fila_dir[indice_dir++] = nova_chave[meio_dir++];
               contador_digitos++;
          }
     }
     fila_esq[indice_esq] = fila_dir[indice_dir] = '\0';

     //String auxiliar para guardar dígitos
     char aux_guardaDigitos[MAX];
     int j = 0;
     //Adicionando valores da esquerda
     int i;
     for (i = 0; i < strlen(fila_esq); i++)
     {
          if (fila_esq[i] != NULL)
          {
               aux_guardaDigitos[j++] = fila_esq[i];
          }
     }
     //Adicionando valor do meio
     aux_guardaDigitos[j++] = nova_chave[meio];
     //Adicionando valores da direita
     for (i = 0; i < strlen(fila_dir); i++)
     {
          if (fila_dir[i] != NULL)
          {
               aux_guardaDigitos[j++] = fila_dir[i];
          }
     }
     aux_guardaDigitos[j] = '\0';

     //Antes de salvar, verificar se o número se está contido no intervalo da tabela
     if (atoi(aux_guardaDigitos) > limite)
     {
          //Eliminar último char
          j--;
          aux_guardaDigitos[j] = '\0';
     }

     //Recuperando string para int
     int indice_final = atoi(aux_guardaDigitos);
     return indice_final;
}

//Transformação da Raiz
int TransformacaoRaiz(int chave, int M, int base)
{
     //Conversão da Chave na Base desejada
     int nova_chave_base = ConverteBase(&chave, base);

     //Retornando índice
     return (nova_chave_base % M);
}
int ConverteBase(int *chave, int base)
{
     //String contendo dígitos
     char digitos[MAX];
     int i = 0;

     //Dividir a chave pela base e colocar os restos no dígitos
     while ((*chave) > 0)
     {
          digitos[i] = ((*chave) % base) + '0';
          i++;
          (*chave) /= base;
     }
     digitos[i] = '\0';

     //Invertendo a string
     strrev(digitos);

     //Retornando o novo valor
     printf("\nCONVERTIDO PRA BASE: %d\n", atoi(digitos));
     return atoi(digitos);
}
//-----------------------------------------------------------------------------------------------------------//

//19/05/2020
//-----------------------------------------------------------------------------------------------------------//
//Funções do Hashing
//Extração
int Extracao(char chave[], int M){
     //Recuperando qtd dígitos do limite de M
     int limite = M - 1;
     char aux_limite[MAX];
     sprintf(aux_limite, "%d", limite);
     int num_digitos_tabela = strlen(aux_limite);

     //Com isso, pegar o início com o fim
     int inicio = num_digitos_tabela/2;
     int fim = num_digitos_tabela - inicio;

     //Percorrendo a string e colocando em auxiliares
     char aux1[MAX], aux2[MAX];
     int i, j = 0;
     for(i = 0; i < inicio; i++){
          aux1[j++] = chave[i];
     }
     j = 0;
     for(i = strlen(chave)-1; i > (strlen(chave) - 1 - fim) ; i--){
          aux2[j++] = chave[i];
     }
     aux2[j] = '\0';
     strrev(aux2);

     //Com isso, tem-se a chave final. Basta verificar se está no intervalo do limite
     int chave_final = atoi(strcat(aux1, aux2));
     
     return (chave_final <= limite) ? chave_final : (chave_final % M);
}

//Enlaçamento Deslocado
int EnlacamentoDeslocado(char chave[], int M){
     //Recuperando qtd dígitos do limite de M
     int limite = M - 1;
     char aux_limite[MAX];
     sprintf(aux_limite, "%d", limite);
     int num_digitos_tabela = strlen(aux_limite);

     //Percorrendo a chave e realizando operações
     int i, j = 0;
     char aux[MAX];
     int num = 0;
     for(i = 0; i<strlen(chave); i++)
     {
          aux[j++] = chave[i];
          //Copiando parte da chave
          if((i + 1) % num_digitos_tabela == 0){
               aux[j] = '\0';
               num += atoi(aux);
               aux[0] = '\0';
               j = 0;
          }
     }
     printf("\nSoma antes do ultimo digito: %d\n", num);
     //Caso tenha sobrado, basta percorrer o aux[i]
     if(aux[0] != '\0'){
          aux[j] = '\0';
          for(i = 0; i<num_digitos_tabela; i++){
               if(aux[i] == '\0'){
                    aux[i] = '0';
                    aux[i+1] = '\0';
               }
          }
          num += atoi(aux);
     }
     printf("\nSoma depois do ultimo digito: %d\n", num);

     //Retornando
     return (num <= limite) ? num : (num % M);
}

//Enlaçamento Limite
int EnlacamentoLimite(char chave[], int M){
     //Recuperando qtd dígitos do limite de M
     int limite = M - 1;
     char aux_limite[MAX];
     sprintf(aux_limite, "%d", limite);
     int num_digitos_tabela = strlen(aux_limite);

     //Percorrendo a chave e realizando operações
     int i, j = 0;
     char aux[MAX];
     int num = 0;
     //Booleana para inverter string
     int verifica = 0;
     for (i = 0; i < strlen(chave); i++)
     {
          aux[j++] = chave[i];
          //Copiando parte da chave
          if ((i + 1) % num_digitos_tabela == 0 && !verifica)
          {
               aux[j] = '\0';
               num += atoi(aux);
               aux[0] = '\0';
               j = 0;
               verifica = 1;
          }
          else if ((i + 1) % num_digitos_tabela == 0 && verifica){
               aux[j] = '\0';
               strrev(aux);
               num += atoi(aux);
               aux[0] = '\0';
               j = 0;
               verifica = 0;
          }
     }
     printf("\nSoma antes do ultimo digito: %d\n", num);
     //Caso tenha sobrado, basta percorrer o aux[i]
     if (aux[0] != '\0')
     {
          aux[j] = '\0';
          for (i = 0; i < num_digitos_tabela; i++)
          {
               if (aux[i] == '\0')
               {
                    aux[i] = '0';
                    aux[i + 1] = '\0';
               }
          }
          if(verifica){
               strrev(aux);
          }
          num += atoi(aux);
     }
     printf("\nSoma depois do ultimo digito: %d\n", num);

     //Retornando
     return (num <= limite) ? num : (num % M);
}

//Dobra
int Dobra(char chave[], int M){
     //Recuperando qtd dígitos do limite de M
     int limite = M - 1;
     char aux_limite[MAX];
     sprintf(aux_limite, "%d", limite);
     int num_digitos_tabela = strlen(aux_limite);

     //Percorrendo a chave e realizando operações
     int i, j = 0, k;
     char aux1[MAX], aux2[MAX], aux_somadigito[2];
     int soma_digito = 0;

     //Percorrendo o primeiro número
     for(i = 0; i < num_digitos_tabela; i++){
          aux1[j++] = chave[i];
          if ((i + 1) % num_digitos_tabela == 0){
               aux1[j] = '\0';
               j = 0;
          }
     }
     for (; i < strlen(chave); i++)
     {
          aux2[j++] = chave[i];

          //Copiando parte da chave
          if ((i + 1) % num_digitos_tabela == 0)
          {
               //Segundo número em diante
               aux2[j] = '\0';
               strrev(aux2);
               //Realizando a soma casa a casa
               for(k = 0; k < num_digitos_tabela; k++){
                    soma_digito = RealizaSomaDigito(aux1[k], aux2[k]);
                    aux_somadigito[k] = soma_digito + '0';
               }
               aux_somadigito[k] = '\0';
               strcpy(aux1, aux_somadigito); //Copiando para o primeiro número da soma
               aux2[0] = '\0';
               aux_somadigito[0] = '\0';
               j = 0;
          }
     }
     //Caso tenha sobrado, basta percorrer o aux2[i]
     if (aux2[0] != '\0')
     {
          aux2[j] = '\0';
          for (i = 0; i < num_digitos_tabela; i++)
          {
               if (aux2[i] == '\0')
               {
                    aux2[i] = '0';
                    aux2[i + 1] = '\0';
               }
          }
          strrev(aux2);
          //Realizando a soma casa a casa
          for (k = 0; k < num_digitos_tabela; k++)
          {
               soma_digito = RealizaSomaDigito(aux1[k], aux2[k]);
               aux_somadigito[k] = soma_digito + '0';
          }
          aux_somadigito[k] = '\0';
          strcpy(aux1, aux_somadigito); //Copiando para o primeiro número da soma
     }

     //Recuperando soma
     int num = atoi(aux1);

     //Retornando
     return (num <= limite) ? num : (num % M);
}
int RealizaSomaDigito(char num1[], char num2[]){
     int aux = num1 - '0';
     aux += (num2 - '0');
     if(aux >= 10){
          aux = (aux % 10);
     }
     return aux;
}
//-----------------------------------------------------------------------------------------------------------//

//26/05/2020
//-----------------------------------------------------------------------------------------------------------//
//Tratamento de Colisões
//Encadamento Interior
typedef struct
{
     int chave;
     int indice_outra;
} def_encadeamento;
void limpaEncadeamentoInterior(def_encadeamento *encadeamento)
{
     int i;
     for (i = 0; i < 2 * MAX2; i++)
     {
          encadeamento[i].chave = encadeamento[i].indice_outra = -1;
     }
}
void imprimeTabelaEncadeamento(def_encadeamento encadeamento[], int total)
{
     printf("\n\nEncadeamento Interior\n\n");
     int i;
     for (i = 0; i < total; i++)
     {
          if (encadeamento[i].chave == -1)
          {
               printf("Encadeamento[%d] = NULO", i);
          }
          else
          {
               if (encadeamento[i].indice_outra != -1)
               {
                    printf("Encadeamento[%d] = %d -> %d", i, encadeamento[i].chave, encadeamento[i].indice_outra);
               }
               else
               {
                    printf("Encadeamento[%d] = %d", i, encadeamento[i].chave);
               }
          }
          printf("\n");
     }
}
//Encadeamento Interior (Uma Região)
int EncadeamentoInteriorUmaRegiao(def_encadeamento *encadeamento, int M, int chave, int indice_chave)
{
     //Caso não haja chave inserida na posição
     if (encadeamento[indice_chave].chave == -1)
     {
          encadeamento[indice_chave].chave = chave;
          return indice_chave;
     }

     //Do contrário, percorrer de cima para baixo e colocar na primeira posição disponível
     int percorre = 0, indice_encadeado = indice_chave;
     int aux = encadeamento[indice_chave].indice_outra;
     while (aux != -1)
     {
          indice_encadeado = aux;
          aux = encadeamento[aux].indice_outra;
     }

     while (percorre < M)
     {
          if (encadeamento[percorre].chave == -1)
          {
               encadeamento[percorre].chave = chave;
               encadeamento[indice_encadeado].indice_outra = percorre;

               return percorre;
          }
          percorre++;
     }
     return -1;
}

//Encadeamento Interior (Duas Regiões)
int EncadeamentoInteriorDuasRegioes(def_encadeamento *encadeamento, int M, int N, int chave, int indice_chave)
{
     //Caso não haja chave inserida na posição
     if (encadeamento[indice_chave].chave == -1)
     {
          encadeamento[indice_chave].chave = chave;
          return indice_chave;
     }

     //Do contrário, percorrer as posições disponíveis na "reserva" (N)
     int percorre_reserva = M, indice_encadeado = indice_chave;
     int aux = encadeamento[indice_chave].indice_outra;
     while (aux != -1)
     {
          indice_encadeado = aux;
          aux = encadeamento[aux].indice_outra;
     }
     while (percorre_reserva < (M + N))
     {
          if (encadeamento[percorre_reserva].chave == -1)
          {
               encadeamento[percorre_reserva].chave = chave;
               encadeamento[indice_encadeado].indice_outra = percorre_reserva;

               return percorre_reserva;
          }

          percorre_reserva++;
     }

     return -1;
}

//Encadeamento Exterior (Lista Linear)
void limpaEncadeamentoExterno(def_lista *TabelaEE){
     int i;
     for (i = 0; i < MAX2; i++)
          TabelaEE[i] = NULL;
}
int encadeamentoExterior(def_lista *TabelaEE, int indice)
{
     if ((*TabelaEE) == NULL)
          (*TabelaEE) = cria_no(indice);
     else
          encadeamentoExterior(&((*TabelaEE)->prox), indice);
     return 1;
}

void imprimir_Tabela_Encad_Exterior(def_lista *TabelaEE, int M)
{
     int i;
     for (i = 0; i < M; i++)
     {
          printf("\nEncadeamento[%d] = ", i);
          imprime_lista_recurs(&TabelaEE[i]);
     }
}
//-----------------------------------------------------------------------------------------------------------//

//27/05/2020
//-----------------------------------------------------------------------------------------------------------//
//Tratamento de Colisões
void limpaEnderecamentoAberto(int *enderecamento){
     int i;
     for(i = 0; i < MAX2; i++){
          enderecamento[i] = -1;
     }
}
void imprimeTabelaEnderecamento(int enderecamento[], int M)
{
     printf("\n\nEnderecamento\n\n");
     int i;
     for (i = 0; i < M; i++)
     {
          if (enderecamento[i] == -1){
               printf("Enderecamento[%d] = NULO", i);
          }
          else{
               printf("Enderecamento[%d] = %d", i, enderecamento[i]);
          }
          printf("\n");
     }
}
//Endereçamento Aberto por Tentativa Linear
int enderecamentoTentativaLinear(int *enderecamento, int M, int chave, int indice)
{
     //Contador a partir do 0
     int k = 0;
     //Fórmula
     int formula = (indice + k) % M;

     //Percorrendo e verificando
     int i;
     for(i = 0; i < M; i++)
     {
          if (enderecamento[formula] == -1)
          {
               enderecamento[formula] = chave;
               return formula;
          }
          k++;
          formula = (indice + k) % M;
     }

     return -1;
}

//Endereçamento Aberto por Tentativa Quadrática
int enderecamentoTentativaQuadratica(int *enderecamento, int M, int chave, int indice, int a0, int a1)
{
     //Contador a partir do 0
     int k = 0;
     //Fórmula
     int formula = (indice + a0*k*k + a1*k) % M;

     //Percorrendo e verificando
     int i;
     for (i = 0; i < M; i++)
     {
          if (enderecamento[formula] == -1)
          {
               enderecamento[formula] = chave;
               return formula;
          }
          k++;
          formula = (indice + a0 * k * k + a1 * k) % M;
     }

     return -1;
}

//Endereçamento Aberto por Dispersão Dupla
int enderecamentoDispersaoDupla(int *enderecamento, int M, int chave, int indice)
{
     //Função pré-definida "g(x)": (2 * chave) + 1
     int funcao_predefinida = chave % 8;

     //Contador a partir do 0
     int k = 0;
     //Fórmula
     int formula = (indice + k*(funcao_predefinida)) % M;

     //Percorrendo e verificando
     int i;
     for (i = 0; i < M; i++)
     {
          if (enderecamento[formula] == -1)
          {
               enderecamento[formula] = chave;
               return formula;
          }
          k++;
          formula = (indice + k * (funcao_predefinida)) % M;
     }

     return -1;
}
//-----------------------------------------------------------------------------------------------------------//
int main()
{
     //Tamanho da Tabela
     int M;
     printf("\nDigite o Tamanho da Tabela (M <= %d): ", MAX2);
     do
     {
          scanf("%d", &M);
     } while (M < 0 || M > MAX2);
     fflush(stdin);
     system("cls");

     //Valor da chave
     int chave;

     //Valor da chave (em string -> 19/05/2020)
     char chave2[MAX];

     //Índice resultante
     int indice;

     //Transformção da Raiz = Base;
     int base;

     //-----------------------------------------------------------------------------------------------------------//
     //Tratamento de Colisões
     int opc_tratamento = -1;

     //Encadeamento Interior
     int N;
     def_encadeamento encadeamento[2 * MAX2];
     limpaEncadeamentoInterior(encadeamento);

     //Encadeamento Exterior
     def_lista TabelaEE[MAX2];
     limpaEncadeamentoExterno(TabelaEE);

     //Endereçamento Aberto
     int enderecamento[MAX2];
     limpaEnderecamentoAberto(enderecamento);
     //Quadrático
     int a0, a1;
     //-----------------------------------------------------------------------------------------------------------//

     //Menu com Opções de Hashing
     int opc = 1;
     while (opc != 0)
     {
          printf("\n\tHASHING\n\n");
          printf("\t1 - Divisao Inteira\n\n");
          printf("\t2 - Meio-Quadrado\n\n");
          printf("\t3 - Transformacao da Raiz\n\n");
          printf("\t4 - Extracao\n\n");
          printf("\t5 - Enlacamento Deslocado\n\n");
          printf("\t6 - Enlacamento Limite\n\n");
          printf("\t7 - Dobra\n\n");
          printf("\n\t0 - Sair do Programa\n\n");
          printf(" Digite sua opcao: ");
          do
          {
               scanf("%d", &opc);
          } while (opc < 0 || opc > 7);
          fflush(stdin);
          system("cls");
          if (!opc)
               break;

          //-----------------------------------------------------------------------------------------------------------//
          //Selecionando tipo de tratamento de colisão
          while(opc_tratamento < 0 || opc_tratamento > 6)
          {
               fflush(stdin);
               printf("\n\tTRATAMENTO DE COLISAO\n\n");
               printf("\t1 - Encadeamento Interior (Uma Regiao)\n\n");
               printf("\t2 - Encadeamento Interior (Duas Regioes)\n\n");
               printf("\t3 - Encadeamento Exterior\n\n");
               printf("\t4 - Enderecamento Aberto por Tentativa Linear\n\n");
               printf("\t5 - Enderecamento Aberto por Tentativa Quadratica\n\n");
               printf("\t6 - Enderecamento Aberto por Dispersao Dupla\n\n");
               printf("\n\t0 - Nenhum Tratamento\n\n");
               printf(" Digite sua opcao: ");
               do
               {
                    scanf("%d", &opc_tratamento);
               } while (opc_tratamento < 0 || opc_tratamento > 6);
               fflush(stdin);
               system("cls");
               if (!opc_tratamento)
                    break;
          }
          //Encadeamento Interior (Duas Regiões) -> Indicação da Reserva
          if(opc_tratamento == 2){
               printf("\nIndique o valor de N ou Reserva da Tabela (N <= 20): ");
               do
               {
                    scanf("%d", &N);
               } while (N < 0 || N > 20);
               system("cls");
          }
          //Endereçamento Aberto por Tentativa Quadrática -> Indicação dos Coeficientes
          else if(opc_tratamento == 5){
               printf("\nIndique o valor do coeficiente A0: ");
               scanf("%d", &a0);
               fflush(stdin);
               printf("\n\nIndique o valor do coeficiente A1: ");
               scanf("%d", &a1);
               fflush(stdin);
               system("cls");
          }
          //-----------------------------------------------------------------------------------------------------------//

          //Iniciando as chaves
          chave = -1;
          strcpy(chave2, "-1");
          do
          {
               //Solicitando as chave(s) e realizando cálculos
               switch (opc)
               {
               //13/05/2020
               //-----------------------------------------------------------------------------------------------------------//
               case 1:
                    printf("\n\tDivisao Inteira\n\n");
                    printf("Digite o valor da chave (-1 para sair): ");
                    do
                    {
                         scanf("%d", &chave);
                    } while (chave < -1);
                    if (chave != -1)
                    {
                         //Printando o valor do índice
                         indice = DivisaoInteira(chave, M);
                         printf("\n\nValor do Indice: %d\n\n", indice);
                    }
                    break;
               case 2:
                    printf("\n\tMeio-Quadrado\n\n");
                    printf("Digite o valor da chave (-1 para sair): ");
                    do
                    {
                         scanf("%d", &chave);
                    } while (chave < -1);
                    if (chave != -1)
                    {
                         //Printando o valor do índice
                         indice = MeioQuadrado(chave * chave, M);
                         printf("\n\nValor do Indice: %d\n\n", indice);
                    }
                    break;
               case 3:
                    printf("\n\tTransformacao da Raiz\n\n");
                    printf("Digite o valor da base (entre 1 e 9): ");
                    do
                    {
                         scanf("%d", &base);
                    } while (base < 0 || base > 9);
                    fflush(stdin);
                    printf("\n\nDigite o valor da chave (-1 para sair): ");
                    do
                    {
                         scanf("%d", &chave);
                    } while (chave < -1);
                    if (chave != -1)
                    {
                         //Printando o valor do índice
                         indice = TransformacaoRaiz(chave, M, base);
                         printf("\n\nValor do Indice: %d\n\n", indice);
                    }
                    break;
               //-----------------------------------------------------------------------------------------------------------//

               //19/05/2020
               //-----------------------------------------------------------------------------------------------------------//
               case 4:
                    printf("\n\tExtracao\n\n");
                    printf("Digite o valor da chave (-1 para sair): ");
                    do
                    {
                         gets(chave2);
                         fflush(stdin);
                    } while (atoi(chave2) < -1);
                    if (atoi(chave2) != -1)
                    {
                         //Printando o valor do índice
                         indice = Extracao(chave2, M);
                         printf("\n\nValor do Indice: %d\n\n", indice);
                    }
                    break;

               case 5:
                    printf("\n\tEnlacamento Deslocado\n\n");
                    printf("Digite o valor da chave (-1 para sair): ");
                    do
                    {
                         gets(chave2);
                         fflush(stdin);
                    } while (atoi(chave2) < -1);
                    if (atoi(chave2) != -1)
                    {
                         //Printando o valor do índice
                         indice = EnlacamentoDeslocado(chave2, M);
                         printf("\n\nValor do Indice: %d\n\n", indice);
                    }
                    break;

               case 6:
                    printf("\n\tEnlacamento Limite\n\n");
                    printf("Digite o valor da chave (-1 para sair): ");
                    do
                    {
                         gets(chave2);
                         fflush(stdin);
                    } while (atoi(chave2) < -1);
                    if (atoi(chave2) != -1)
                    {
                         //Printando o valor do índice
                         indice = EnlacamentoLimite(chave2, M);
                         printf("\n\nValor do Indice: %d\n\n", indice);
                    }
                    break;
               
               case 7:
                    printf("\n\tDobra\n\n");
                    printf("Digite o valor da chave (-1 para sair): ");
                    do
                    {
                         gets(chave2);
                         fflush(stdin);
                    } while (atoi(chave2) < -1);
                    if (atoi(chave2) != -1)
                    {
                         //Printando o valor do índice
                         indice = Dobra(chave2, M);
                         printf("\n\nValor do Indice: %d\n\n", indice);
                    }
                    break;
               }
               //-----------------------------------------------------------------------------------------------------------//
               if (chave == -1 && atoi(chave2) == -1){
                    system("cls");
                    break;
               }

               //26/05/2020
               //-----------------------------------------------------------------------------------------------------------//
               //Tratamento de Colisões
               switch (opc_tratamento)
               {
                    //Encadeamento Interior (Uma Região)
                    case 1:
                         if (EncadeamentoInteriorUmaRegiao(encadeamento, M, chave, indice) != -1)
                         {
                              printf("\nChave tratada com sucesso\n\n");
                         }
                         else
                         {
                              printf("\nErro ao tratar chave. Tente novamente.\n\n");
                         }
                         break;
                    //Encadeamento Interior (Duas Regiões)
                    case 2:
                         if (EncadeamentoInteriorDuasRegioes(encadeamento, M, N, chave, indice) != -1)
                         {
                              printf("\nChave tratada com sucesso\n\n");
                         }
                         else
                         {
                              printf("\nErro ao tratar chave. Tente novamente.\n\n");
                         }
                         break;
                    //Encadeamento Exterior
                    case 3:
                         if (encadeamentoExterior(&TabelaEE, indice))
                         {
                              printf("\nChave tratada com sucesso\n\n");
                         }
                         else
                         {
                              printf("\nErro ao tratar chave. Tente novamente.\n\n");
                         }
                         break;
                    //Endereçamento Aberto por Tentativa Linear
                    case 4:
                         if (enderecamentoTentativaLinear(enderecamento, M, chave, indice) != -1)
                         {
                              printf("\nChave tratada com sucesso\n\n");
                         }
                         else
                         {
                              printf("\nErro ao tratar chave. Tente novamente.\n\n");
                         }
                         break;
                    //Endereçamento Aberto por Tentativa Quadrática
                    case 5:
                         if (enderecamentoTentativaQuadratica(enderecamento, M, chave, indice, a0, a1) != -1)
                         {
                              printf("\nChave tratada com sucesso\n\n");
                         }
                         else
                         {
                              printf("\nErro ao tratar chave. Tente novamente.\n\n");
                         }
                         break;
                    //Endereçamento Aberto por Dispersão Dupla
                    case 6:
                         if (enderecamentoDispersaoDupla(enderecamento, M, chave, indice) != -1)
                         {
                              printf("\nChave tratada com sucesso\n\n");
                         }
                         else
                         {
                              printf("\nErro ao tratar chave. Tente novamente.\n\n");
                         }
                         break;
               }
               system("pause");
               system("cls");

          } while (chave != -1 || atoi(chave2) != -1);

          //-----------------------------------------------------------------------------------------------------------//
          //Mostrando tabelas com base na opção
          switch(opc_tratamento)
          {
               //Encadeamento Interior (Uma Região)
               case 1:
                    imprimeTabelaEncadeamento(encadeamento, M);
                    limpaEncadeamentoInterior(encadeamento);
                    break;
               //Encadeamento Interior (Duas Regiões)
               case 2:
                    imprimeTabelaEncadeamento(encadeamento, M + N);
                    limpaEncadeamentoInterior(encadeamento);
                    break;
               //Encadeamento Exterior
               case 3:
                    printf("\n\nEncadeamento Exterior\n\n");
                    imprimir_Tabela_Encad_Exterior(TabelaEE, M);
                    limpaEncadeamentoExterno(TabelaEE);
                    break;
               //Endereçamento Aberto por Tentativa Linear
               case 4:
                    imprimeTabelaEnderecamento(enderecamento, M);
                    limpaEnderecamentoAberto(enderecamento);
                    break;
               //Endereçamento Aberto por Tentativa Quadrática
               case 5:
                    imprimeTabelaEnderecamento(enderecamento, M);
                    limpaEnderecamentoAberto(enderecamento);
                    break;
               //Endereçamento Aberto por Dispersão Dupla
               case 6:
                    imprimeTabelaEnderecamento(enderecamento, M);
                    limpaEnderecamentoAberto(enderecamento);
                    break;
          }
          opc_tratamento = -1;
          printf("\n\n");
          system("pause");
          system("cls");
          //-----------------------------------------------------------------------------------------------------------//
     }

     return 0;
}