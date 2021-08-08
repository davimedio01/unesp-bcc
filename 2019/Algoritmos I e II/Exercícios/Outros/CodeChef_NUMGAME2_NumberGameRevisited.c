#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

int main()
{
    int t, n;
    scanf("%d", &t);
    while(t>0)
    {
        scanf("%d", &n);
        if(n%4 == 1)
            printf("ALICE\n");
        else
            printf("BOB\n");

        t--;
    }
	return 0;
}

/*Sequ�ncia de Jogada (In�cio com o Bob) e sempre tirando o maior primo:

Supondo que o n�mero de in�cio seja N=1, o Bob n�o consegue tirar nada = Alice ganha;
Agora, supondo que seja N=2, o Bob pode tirar 1 = Bob ganha;
Agora, supondo que seja N=3, o Bob pode tirar 2 = Bob ganha;
Agora, supondo que seja N=4, o Bob pode tirar 3 = Bob ganha;
Contudo, supondo que seja N=5, o Bob pode tirar no m�ximo 3, Alice tira 1 = Alice ganha;
(Mesmo se ele tirar 2 ou 1, Alice ainda ir� vencer se tirar 2 ou 3, respectivamente)

Essa sequ�ncia se repete para um N qualquer.
Ou seja, a sequ�ncia � do tipo 4x+1 para Alice vencer
(precisa sobrar 1 para o Bob perder na sequ�ncia, sempre supondo que ele comece jogando).

Logo, se o resto de N por 4 (maior n�mero n�o primo do in�cio da sequ�ncia e que,
supondo N=5 o Bob subtraisse o maior primo at� ali (3),
Alice sempre ir� ganhar com mais uma jogada) for igual a 1 (que � o que vai sobrar da ultima jogada da Alice,
impedindo o Bob de tirar outro valor (lembrando que ele pode tirar x<N)) implica na vit�ria da Alice
*/
