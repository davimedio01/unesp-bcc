#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

//! F(X) = X^3 - 5*X^2 - X + 5
double FuncGenerica(double x)
{
     //return pow(x, 3) - 5*pow(x, 2) - x + 5;
     return log(x) - sin(x);
}

void PosicaoFalsa(int NumFuncao, double *X0, double *LimInf, double *LimSup, double Precisao, int *It, int MaxIt)
{
     double erro = 0.0f;
     double FLimInf, FLimSup, FX0;
     double XAux = 0.0f;

     for((*It) = 0; (*It) <= MaxIt; (*It)++)
     {
          switch(NumFuncao)
          {
               //! F(X) = X^3 - 5*X^2 - X + 5
               case 1:
                    //F(LimInf)
                    FLimInf = FuncGenerica((*LimInf));

                    //F(LimSup)
                    FLimSup = FuncGenerica((*LimSup));

                    //X0 = (LimInf * FLimSup - LimSup * FLimInf)/(FLimSup - FLimInf)
                    (*X0) = ((*LimInf) * FLimSup - (*LimSup) * FLimInf) / (FLimSup - FLimInf);

                    //F(X0)
                    FX0 = FuncGenerica((*X0));

                    break;
          }

          printf("ITERACAO %d\n\n", (*It));          

          printf("A%d = %.4lf\n", (*It), (*LimInf));
          printf("B%d = %.4lf\n", (*It), (*LimSup));
          printf("X%d = %.4lf\n\n", (*It), (*X0));

          printf("F(A%d) = %.4lf\n", (*It), FLimInf);
          printf("F(B%d) = %.4lf\n", (*It), FLimSup);
          printf("F(X%d) = %.4lf\n\n", (*It), FX0);

          //Erro
          if((*It) != 0)
          {
               erro = fabs(XAux - (*X0))/fabs((*X0));

               printf("Erro: %.4lf\n\n", erro);
               if (erro < Precisao)
               {
                    printf("\nRaiz de X = %.4lf\n\n", (*X0));
                    return;
               }
          }
          XAux = (*X0);

          //Analisando condições do Método
          if (FLimInf * FX0 < 0)
          {
               (*LimSup) = (*X0);
          }
          else
          {
               (*LimInf) = (*X0);
          }
     }

     //Convergência ou Número de Iterações Insuficiente
     printf("\n\nO metodo nao converge ou nao ha um numero de iteracoes suficiente para calculo da raiz.\n\n");
}

int main(){

     //!!! DEFINIÇÃO DA PRECISÃO GENÉRICA!!!
     double Precisao = 0.01f;
     double X0, LimInf, LimSup;
     int MaxIt, It;

     printf("\nPOSICAO FALSA - FUNCAO GENERICA\n\n");
     printf("F(x) = x^3 - cos(x)\n\n");
     printf("Precisao = %.4f\n\n", Precisao);
     printf("Intervalo: [a,b]\n\n\n");

     printf("Digite o valor do Limite Inferior (a): ");
     scanf("%lf", &LimInf);
     printf("\n\nDigite o valor do Limite Superior (b): ");
     scanf("%lf", &LimSup);
     printf("\n\nDigite o valor maximo de iteracoes: ");
     scanf("%d", &MaxIt);

     system("cls");

     printf("\nPOSICAO FALSA - FUNCAO GENERICA\n\n");
     printf("F(x) = x^3 - cos(x)\n\n");
     printf("Precisao = %.4lf\n\n", Precisao);
     printf("Intervalo Inicial: [%.4lf, %.4lf]\n\n\n", LimInf, LimSup);

     //! CALCULANDO PELA POSIÇÃO FALSA
     PosicaoFalsa(1, &X0, &LimInf, &LimSup, Precisao, &It, MaxIt);

     return 0;
}