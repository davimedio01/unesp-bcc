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

    char texto[max][max], aux[max];
    int n,i,j;
    scanf("%d",&n);

    for(i=0;i<n;i++)
        scanf("%s",&texto[i]);
    printf("\n");
    for(i=1;i<n;i++)
    {
        for(j=0;j<n-i;j++)
        {
            if(stricmp(texto[j],texto[j+1])>0)
            {
                strcpy(aux,texto[j]);
                strcpy(texto[j],texto[j+1]);
                strcpy(texto[j+1],aux);
            }
        }
    }
    for(i=0;i<n;i++)
        printf("%s\n",texto[i]);

	return 0;
}
