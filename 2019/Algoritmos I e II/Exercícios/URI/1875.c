#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int n, gols, i;
    int cont_green, cont_red, cont_blue;
    char primeiro, segundo;
    scanf("%d", &n);
    while(n>0)
    {
        cont_green = 0;
        cont_red = 0;
        cont_blue = 0;
        scanf("%d", &gols);

        for(i=0; i<gols; i++)
        {
            scanf(" %c", &primeiro);
            scanf(" %c", &segundo);
            if(toupper(primeiro)=='R' && toupper(segundo)=='G')
                cont_red += 2;
            else if(toupper(primeiro)=='G' && toupper(segundo)=='B')
                cont_green += 2;
            else if(toupper(primeiro)=='B' && toupper(segundo)=='R')
                cont_blue += 2;
            else if(toupper(primeiro)=='R' && toupper(segundo)=='B')
                cont_red++;
            else if(toupper(primeiro)=='G' && toupper(segundo)=='R')
                cont_green++;
            else if(toupper(primeiro)=='B' && toupper(segundo)=='G')
                cont_blue++;

            fflush(stdin);
        }

        if((cont_red == cont_green) && (cont_blue == cont_green))
            printf("trempate\n");
        else if(cont_red>cont_green && cont_red>cont_blue)
            printf("red\n");
        else if(cont_green>cont_red && cont_green>cont_blue)
            printf("green\n");
        else if(cont_blue>cont_red && cont_blue>cont_green)
            printf("blue\n");
        else if ((cont_red==cont_green)|| (cont_red==cont_blue) ||(cont_blue==cont_green))
            printf("empate\n");
        fflush(stdin);
        n--;
    }
	return 0;
}
