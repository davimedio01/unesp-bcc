#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 1001

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    char mensagem[max];
    //scanf("%s", &mensagem);
    gets(mensagem);

    int i;
    int contp = 0;
    for(i=0; i<strlen(mensagem); i++)
    {
        if(mensagem[i] != 'p')
        {
            printf("%c", mensagem[i]);
            contp = 0;
        }
        else if(mensagem[i] == 'p')
        {
            contp++;
            if(contp % 2 == 0)
                printf("%c", mensagem[i]);
        }

    }
    printf("\n");
	return 0;
}
