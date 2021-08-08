#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"
//Uma carta voltar na posi��o, todas voltam. (Printar solu��o e ver comportamento)
//Dobra a posi��o em que est�

/*Exemplo (n=6):
1 2 3 4 5 6
1 2 3   4 5 6

4 1 5 2 6 3
4 1 5   2 6 3

2 4 6 1 3 5
2 4 6   1 3 5

1 2 3 4 5 6
Total: 3 procedimentos

1 2 3 4 5 6 7 8 9 10
1 2 3 4 5  6 7 8 9 10

6 1 7 2 8 3 9 4 10 4
6 1 7 2 8    3 9 4 10 5

3 6 9 1 4 7 10 2 5 8
3 6 9 1 4    7 10 2 5 8

7 3 10 6 2 9 5 1 8 4
7 3 10 6 2    9 5 1 8 4        1 8 4 7 3 10 6 2 9    (anda 16 posi��es tirando a dela)

9 7 5 3 1 10 8 6 4 2
9 7 5 3 1  10 8 6 4 2

10 9 8 7 6 5 4 3 2 1

1 2 3 4
3 1 4 2
4 3 2 1
2 4 1 3

A posi��o do '1' anda sempre o dobro da que estava (anterior)
Quando o '1' chegar na ultima posi��o, dobra-se o processo
(ou seja, para n=4, o '1' chega na posi��o 4 com 2 procedimentos, necessitando +2 para voltar para 1� posi��o)
Al�m disso, quando ele ultrapassa a metade, � como se o processo se repetisse (invertido),
ou seja, ele anda (n+1-posi��o)

*/
//2 = 2; 4 = 4; 6 = 3; 8 = 6; 10 = 10;

int main()
{
    int n;
    scanf("%d",&n);

    int primeira_pos = 2; //contando sempre o primeiro passo, ele ir� para a segunda posi��o
    int cont=1; //contando j� o primeiro passo

    while(primeira_pos!=1)
    {
        if(primeira_pos<=n/2)
            primeira_pos *= 2; //andar sempre o dobro da posi��o anterior (ou a pr�pria posi��o)
        else
            primeira_pos -= (n+1-primeira_pos); //quando ele ultrapassar a metade do total, ele vai voltar (ou, a grosso modo, fazer a volta na sequ�ncia com o dobro da posi��o atual)
        cont++;
    }
    printf("%d\n", cont);

	return 0;
}
