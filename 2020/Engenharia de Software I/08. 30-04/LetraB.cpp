/*Criado por Davi Augusto - BCC - UNESP Bauru*/
/**/

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

//1 (INÍCIO DA FUNÇÃO)
void Funcao(int x, int y)
{
     //2
     int p = 0, z = 0;

     //3
     if (y > 0)
     {
          //4
          p = y;
     }
     //3
     else if (y <= 0)
     {
          //5
          p = (-y);
     }

     //6
     z = 1;

     //7
     while (p != 0)
     {
          //8
          p--;    //p = p - 1;
          z *= x; //z = z*x;
     }

     //9

     //10
     if (y < 0)
     {
          //11
          z = (1 / z);
     }

     //12; 13 (FIM DA FUNÇÃO)
}

int main(){

     //Declaração de X, Y
     int x, y;

     ////////////////////////
     //Atribuição de X e Y //
     ////////////////////////
     x = y = 2;

     //Execução da "Funcao"
     Funcao(x, y);
     
     return 0;
}