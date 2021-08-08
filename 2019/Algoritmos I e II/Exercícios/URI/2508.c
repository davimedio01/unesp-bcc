#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 101

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    char nome[max], aux1[5], aux2;
    int soma=0, total=0, i;
    while(fgets(nome, max, stdin) != NULL)
    {
        soma = 0;
        for(i=0; i<strlen(nome); i++)
        {
            aux2 = toupper(nome[i]);
            if((aux2=='A') || (aux2=='J') || (aux2=='S'))
                soma += 1;
            else if((aux2=='B') || (aux2=='K') || (aux2=='T'))
                soma += 2;
            else if((aux2=='C') || (aux2=='L') || (aux2=='U') || (aux2=='Ç'))
                soma += 3;
            else if((aux2=='D') || (aux2=='M') || (aux2=='V'))
                soma += 4;
            else if((aux2=='E') || (aux2=='N') || (aux2=='W'))
                soma += 5;
            else if((aux2=='F') || (aux2=='O') || (aux2=='X'))
                soma += 6;
            else if((aux2=='G') || (aux2=='P') || (aux2=='Y'))
                soma += 7;
            else if((aux2=='H') || (aux2=='Q') || (aux2=='Z'))
                soma += 8;
            else if((aux2=='I') || (aux2=='R'))
                soma += 9;
        }

        sprintf(aux1, "%d", soma);
        total = 0;
        for(i=0; i<strlen(aux1); i++)
            total += (aux1[i] - '0');

        sprintf(aux1, "%d", total);
        total = 0;
        for(i=0; i<strlen(aux1); i++)
            total += (aux1[i] - '0');
        
        printf("%d\n", total);
    }
	return 0;
}
