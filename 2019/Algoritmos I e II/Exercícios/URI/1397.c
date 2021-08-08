#include <stdio.h>

int main()
{
	int n;
	while(1)
	{
		scanf("%d",&n);
		if(n==0)
			break;
		int a, b, i, cont1=0, cont2=0;
		//Utiliza dois contadores e verifica quem marcou mais ponto para aumetá-los
		for(i=0;i<n;i++)
		{
			scanf("%d %d",&a,&b);
			if(a>b)
				cont1++;
			else if(a<b)
				cont2++;
		}
		printf("%d %d\n",cont1,cont2);
	}
	return 0;
}

