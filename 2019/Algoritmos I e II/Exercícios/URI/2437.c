#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte "Windows 1252"

int main()
{
	int x1,y1,x2,y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    int dist_man;
    dist_man = abs(x1-x2) + abs(y1-y2);
    printf("%d\n",dist_man);

	return 0;
}
