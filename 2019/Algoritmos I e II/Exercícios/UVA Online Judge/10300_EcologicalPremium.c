#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

int main()
{
	int n;
    int t_fazenda, num_animal, ecologico;
    int num_fazendeiro, i;
    scanf("%d",&n);
    while(n>0)
    {
        while(scanf("%d",&num_fazendeiro) != EOF)
        {
            int aux = 0, total = 0;
            for(i=0; i<num_fazendeiro; i++)
            {
                scanf("%d %d %d", &t_fazenda, &num_animal, &ecologico);
                total += (t_fazenda * ecologico);
            }
            printf("%d\n", total);
        }
        n--;
    }
	return 0;
}
