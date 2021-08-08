/*
Trabalho de Zero de Funcoes
Metodos Numericos Computacionais (MNC)

Integrantes                RA
Davi Augusto Neves Leite - 191027383
Giovani Candido          - 191021601
Luis Henrique Morelli    - 181027097
Luiz Fernando Sementille - 191021032
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

double solveFunction(int f, double x){
     switch (f){
          case 1:
               return pow(x, 3) - 5 * pow(x, 2) - x + 5;
          case 2:
               return log(x) - sin(x);
          case 3:
               return log(x) + x - 4;
     }
}

int bisection(int f, double a, double b, double precision, int maxIt, int *numIt, double *root){
     if (solveFunction(f, a) * solveFunction(f, b) >= 0){
          return 0;
     }

     double fA, fB, x, fX, x0;
     int i;

     for (i = 1; i <= maxIt; i++){
          x = (a + b) / 2;

          fA = solveFunction(f, a);
          fB = solveFunction(f, b);
          fX = solveFunction(f, x);

          if (i > 0){
               if (fabs((x - x0) / x) < precision){
                    *root = x;
                    *numIt = i;

                    return 1;
               }
          }

          if (fA * fX < 0){
               b = x;
          }
          else if (fB * fX < 0){
               a = x;
          }

          x0 = x;
     }

     return 0;
}

int falsePosition(int f, double a, double b, double precision, int maxIt, int *numIt, double *root){
     if (solveFunction(f, a) * solveFunction(f, b) >= 0){
          return 0;
     }

     double fA, fB, x, fX, x0;
     int i;

     for (i = 1; i <= maxIt; i++){
          fA = solveFunction(f, a);
          fB = solveFunction(f, b);

          x = ((a * fB) - (b * fA)) / (fB - fA);
          fX = solveFunction(f, x);

          if (i > 0){
               if (fabs((x - x0) / x) < precision){
                    *root = x;
                    *numIt = i;

                    return 1;
               }
          }

          if (fA * fX < 0){
               b = x;
          }
          else if (fB * fX < 0){
               a = x;
          }

          x0 = x;
     }

     return 0;
}

double solveDerivative(int f, double x, double precision, int maxIt){
     double h, d, formerD;
     int i;

     for (i = 1, h = 1; i <= maxIt; i++, h /= 2){
          d = (solveFunction(f, x + h) - solveFunction(f, x - h)) / (2 * h);

          if (i > 1 && fabs((d - formerD) / fmax(1, d)) < precision){
               return d;
          }

          formerD = d;
     }

     return 0;
}

int newton(int f, double x0, double precision, int maxIt, int *numIt, double *root){
     double h, x;
     int i;

     for (i = 1; i <= maxIt; i++){
          h = solveFunction(f, x0) / solveDerivative(f, x0, precision, maxIt);
          x = x0 - h;

          if (fabs((x - x0) / x) < precision){
               *root = x;
               *numIt = i;

               return 1;
          }

          x0 = x;
     }

     return 0;
}

int main()
{
     int function, method, maxIt, numIt;
     double a, b, x0, precision, root;
     char repeat;

     do{
          system("cls||clear");

          do{
               printf("\nEscolha entre as funcoes abaixo\n");
               printf("[1] x^3 - 5x^2 - x + 5\n");
               printf("[2] ln(x) - sen(x)\n");
               printf("[3] ln(x) + x - 4\n");

               printf("Funcao escolhida: ");
               scanf("%d", &function);
          } while (function < 1 || function > 3);

          do{
               printf("\nEscolha entre os metodos abaixo\n");
               printf("[1] Bisseccao\n");
               printf("[2] Posicao Falsa\n");
               printf("[3] Newton\n");

               printf("Metodo escolhido: ");
               scanf("%d", &method);
          } while (method < 1 || method > 3);

          if (method == 3){
               printf("\nX inicial: ");
               scanf("%lf", &x0);
          }
          else{
               printf("\nLimite inferior do intervalo: ");
               scanf("%lf", &a);

               printf("Limite superior do intervalo: ");
               scanf("%lf", &b);
          }

          printf("Precisao: ");
          scanf("%lf", &precision);

          printf("Numero maximo de iteracoes: ");
          scanf("%d", &maxIt);

          int aux;

          switch (method){
               case 1:
                    aux = bisection(function, a, b, precision, maxIt, &numIt, &root);
                    break;
               case 2:
                    aux = falsePosition(function, a, b, precision, maxIt, &numIt, &root);
                    break;
               case 3:
                    aux = newton(function, x0, precision, maxIt, &numIt, &root);
                    break;
          }

          if (aux == 1){
               printf("\nNumero de iteracoes: %d\n", numIt);
               printf("Raiz real aproximada: %.4lf\n", root);
          }
          else if (aux == 0){
               printf("\nNao foi possivel calcular a raiz da funcao desejada!\n");
	       printf("\nNao converge ou nao ha um numero de iteracoes suficiente.\n");
          }

          fflush(stdin);

          do{
               printf("\nDeseja resolver novamente? (S/N) ");
               repeat = toupper(getch());
          } while (repeat != 'S' && repeat != 'N');
     } while (repeat == 'S');

     printf("\n\nFim de execucao...\n");
     system("pause");

     return 0;
}