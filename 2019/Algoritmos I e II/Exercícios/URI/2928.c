#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte "Windows 1252"

int main()
{

    int n;
    scanf("%d",&n);

    char mapa[n][10];
    int i;
    for(i=0;i<n;i++)
            scanf("%s",&mapa[i]);

    int aux=0, cont=0;
    if(n==1)
    {
        if(mapa[0][0]=='.')
            printf("1\n");
        else
            printf("0\n");
    }
    else
    {
        for(i=0;i<n;i++)
        {
            if(mapa[i][0] == '.')
            {
                aux++;
                if(aux<=2)
                {
                    if(i+1>=n||mapa[i+1][0]=='-')
                        cont++;
                }
                else
                {
                    cont=-1;
                    break;
                }
            }
            else
                aux=0;
        }
    }

    if(cont>=0)
        printf("%d\n",cont);
    else
        printf("N\n");

	return 0;
}
