#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
	int n,m;
	while(scanf("%d %d",&n,&m) != EOF)
	{
		int mat[n][m];
		int i,j;
		int posx_t,posy_t,posx_pok,posy_pok;
		
		for(i=0;i<n;i++)
		{
			for(j=0;j<m;j++)
			{
				scanf("%d",&mat[i][j]);
				if(mat[i][j]==1)
				{
					posx_t = i+1;
					posy_t = j+1;
				}
				
				if(mat[i][j]==2)
				{
					posx_pok = i+1;
					posy_pok = j+1;
				}
			}	
		}
			
		int dist = abs(posx_t - posx_pok) + abs(posy_t - posy_pok);
		printf("%d\n",dist);
	}
	return 0;
}

