/*Criado por Davi Augusto - BCC - UNESP Bauru*/
/**/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define MAX 100

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

int main()
{
     //Tamanho da Tabela
     int M;
     printf("\nDigite o Tamanho da Tabela (M): ");
     do
     {
          scanf("%d", &M);
     } while (M <= 0);
     fflush(stdin);
     system("cls");

     //Valor da chave
     int chave;

     //Valor da chave (em string -> 19/05/2020)
     char chave2[MAX];

     //Transformção da Raiz = Base;
     int base;

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
                         printf("\n\nValor do Indice: %d\n\n", DivisaoInteira(chave, M));
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
                         printf("\n\nValor do Indice: %d\n\n", MeioQuadrado(chave * chave, M));
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
                         printf("\n\nValor do Indice: %d\n\n", TransformacaoRaiz(chave, M, base));
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
                         printf("\n\nValor do Indice: %d\n\n", Extracao(chave2, M));
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
                         printf("\n\nValor do Indice: %d\n\n", EnlacamentoDeslocado(chave2, M));
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
                         printf("\n\nValor do Indice: %d\n\n", EnlacamentoLimite(chave2, M));
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
                         printf("\n\nValor do Indice: %d\n\n", Dobra(chave2, M));
                    }
                    break;
               //-----------------------------------------------------------------------------------------------------------//
               }
               if (chave != -1 || atoi(chave2) != -1)
                    system("pause");
               system("cls");
          } while (chave != -1 || atoi(chave2) != -1);
     }

     return 0;
}