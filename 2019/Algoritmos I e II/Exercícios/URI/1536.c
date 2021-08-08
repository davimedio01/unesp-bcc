#include <stdio.h>
#include <math.h>

int main()
{
	int n,i,j;
	scanf("%d",&n);
	
	for(i=0;i<n;i++)
	{
		int time1_1, time1_2, time2_1, time2_2;
		scanf("%d x %d", &time1_1, &time2_1);
		scanf("%d x %d", &time2_2, &time1_2);
		
		int saldo1 = time1_1 + time1_2;
		int saldo2 = time2_1 + time2_2;
		
		if(saldo1>saldo2)
			printf("Time 1\n");
		else if ((saldo1==saldo2)&&(time1_2>time2_1))
			printf("Time 1\n");
		else if (saldo2>saldo1)
			printf("Time 2\n");
		else if((saldo1==saldo2)&&(time2_1>time1_2))
			printf("Time 2\n");
		else if((saldo1==saldo2)&&(time1_1==time2_2)&&(time2_1==time1_2))
			printf("Penaltis\n");
	}
	
	return 0;	
}
