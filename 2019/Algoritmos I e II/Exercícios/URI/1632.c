#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int n;
    scanf("%d",&n);

    char senha[20];
    int aux, i;
    while(n>0)
    {
        aux=1;
        scanf("%s",&senha);

        for(i=0; i<strlen(senha); i++)
        {
            if((toupper(senha[i]) == 'A') || (toupper(senha[i]) == 'E') || (toupper(senha[i]) == 'I') || (toupper(senha[i]) == 'O') || (toupper(senha[i]) == 'S'))
                aux *= 3;
            else
                aux *= 2;
        }
        printf("%d\n", aux);
        n--;
    }
	return 0;
}
