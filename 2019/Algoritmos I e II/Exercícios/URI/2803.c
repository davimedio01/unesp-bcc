#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    char batata[15];
    scanf("%s", &batata);

    if(!(strcmp(batata,"roraima")) || !(strcmp(batata,"acre")) || !(strcmp(batata,"amapa")) || !(strcmp(batata,"amazonas")) || !(strcmp(batata, "para")) || !(strcmp(batata, "rondonia")) || !(strcmp(batata,"tocantins")))
        printf("Regiao Norte\n");
    else
        printf("Outra regiao\n");
    return 0;
}
