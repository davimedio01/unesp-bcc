#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
    int n, i, aux=0;
    scanf("%d",&n);
    char EhrriA[max];
    while(n>0)
    {
        scanf("%s", &EhrriA);
        //RA incorreto
        if((EhrriA[0]!='R')||(EhrriA[1]!='A')||(strlen(EhrriA)!=20))
            printf("INVALID DATA\n");
        else
        {
            for(i=2;i<strlen(EhrriA);i++)
            {
                if(EhrriA[i]!='0')
                {
                    aux=i;
                    break;
                }
            }
            if(aux!=0)
            {
                for(i=aux;i<strlen(EhrriA);i++)
                    printf("%c",EhrriA[i]);
                printf("\n");
            }
            else
                printf("INVALID DATA\n");
        }
        n--;
    }
	return 0;
}
