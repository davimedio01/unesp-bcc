#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte "Windows 1252"

int main()
{
	system("COLOR 09");
	setlocale(LC_ALL,"Portuguese");

    char *separa;
    char texto[max];
    gets(texto);
    printf("\n");
    separa = strtok(texto, " -.,");
    while(separa)
    {
        printf("%s\n",separa);
        separa = strtok(NULL," -.,");
    }

    //strtok utilizado acima para separar palavras com delimitadores (uso de ponteiro para tal)
    /*strstr utilizado para delimitar o inicio da string e mostrar o resto (tambem ponteiro)
        char str[max];
        gets(str);
        char definir[max];
        gets(definir);
        char *palavra;
        palavra = strstr (str, definir);
        puts (palavra);
    */
	return 0;
}
