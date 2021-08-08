#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"
//Verificar se é palíndroma de "vogais"
int main()
{
    char risada[max], aux1[max];
    scanf("%s", &risada);
    int i, j=0, sinal = 1;
    for(i=0; i<strlen(risada); i++)
    {
        if((risada[i] == 'a') || (risada[i] == 'e') || (risada[i] == 'i') || (risada[i] == 'o') || (risada[i] == 'u'))
            aux1[j++] = risada[i];
    }
    aux1[j] = '\0';
    for(i=0; i<strlen(aux1) && sinal; i++)
    {
        if(aux1[i] != aux1[strlen(aux1)-i-1])
            sinal = 0;
    }

    if(sinal)
        printf("S\n");
    else
        printf("N\n");

	return 0;
}
