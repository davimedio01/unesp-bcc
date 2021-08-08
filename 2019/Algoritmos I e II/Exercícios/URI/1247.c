#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>

#define max 100

//Utilizar o Atom para compilar com a fonte/encoding "Windows 1252"

int main()
{
	system("COLOR 09");
	setlocale(LC_ALL,"Portuguese");

	int d, vf, vg;
	while(scanf("%d %d %d",&d, &vf, &vg) != EOF)
	{
		float tempo_guarda = ((sqrt(pow(12,2) + pow(d,2)))/vg)*1.0;
		float tempo_ladrao = (12.0/vf);
		if(tempo_guarda<=tempo_ladrao)
			printf("S\n");
		else
			printf("N\n");
	}

	return 0;
}
