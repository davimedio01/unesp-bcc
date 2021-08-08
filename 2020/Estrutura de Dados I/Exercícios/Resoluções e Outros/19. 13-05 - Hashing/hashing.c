/*Criado por Davi Augusto - BCC - UNESP Bauru*/
/**/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define MAX 100

//Funções do Hashing
//Divisão (Inteira)
int DivisaoInteira(int chave, int M)
{
     return (chave % M);
}

//Meio-Quadrado
int MeioQuadrado(unsigned long int chave_quad, int M)
{
     //Convertendo para String
     char nova_chave[MAX];
     sprintf(nova_chave, "%lu", chave_quad);

     //printf("\n%s\n", nova_chave);

     //Recuperando o tamanho de dígitos
     int num_digitos_quad = strlen(nova_chave);

     //Com isso, recuperar a posição do meio
     int meio = (num_digitos_quad/2);
     if(num_digitos_quad % 2 == 0)
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

     while(contador_digitos < num_digitos_tabela)
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
     for(i = 0; i < strlen(fila_esq); i++){
          if(fila_esq[i] != NULL)
          {
               aux_guardaDigitos[j++] = fila_esq[i];
          }
     }
     //Adicionando valor do meio
     aux_guardaDigitos[j++] = nova_chave[meio];
     //Adicionando valores da direita
     for(i = 0; i < strlen(fila_dir); i++)
     {
          if(fila_dir[i] != NULL)
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
     return atoi(digitos);
}


int main(){

     //Tamanho da Tabela
     int M;
     printf("\nDigite o Tamanho da Tabela (M): ");
     do{
          scanf("%d", &M);
     }while(M <= 0);
     fflush(stdin);
     system("cls");

     //Valor da chave
     int chave;

     //Transformção da Raiz = Base;
     int base;

     //Menu com Opções de Hashing
     int opc = 1;
     while(opc != 0)
     {
          printf("\n\tHASHING\n\n");
          printf("\t1 - Divisao Inteira\n\n");
          printf("\t2 - Meio-Quadrado\n\n");
          printf("\t3 - Transformacao da Raiz\n\n");
          printf("\n\t0 - Sair do Programa\n\n");
          printf(" Digite sua opcao: ");
          do{
               scanf("%d", &opc);
          }while(opc < 0 || opc > 3);
          fflush(stdin);
          system("cls");
          if(!opc)
               break;

          do{
               //Solicitando as chave(s) e realizando cálculos
               switch (opc)
               {
               case 1:
                    printf("\n\tDivisao Inteira\n\n");
                    printf("Digite o valor da chave (-1 para sair): ");
                    do
                    {
                         scanf("%d", &chave);
                    } while (chave < -1);
                    if(chave != -1){
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
                    if(chave != -1){
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
                    if(chave != -1){
                         //Printando o valor do índice
                         printf("\n\nValor do Indice: %d\n\n", TransformacaoRaiz(chave, M, base));
                    }
                    break;
               }
               if(chave != -1)
                    system("pause");
               system("cls");
          }while(chave != -1);
          
     }

     return 0;
}