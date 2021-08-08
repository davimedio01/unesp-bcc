#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
	int n,c,s,i;
	scanf("%d %d %d",&n,&c,&s);
	
	int x;
	int pos=1, cont2=0, teste;
	
	if(pos==s)
		cont2++;
			
	for(i=0;i<c;i++)
	{	
		scanf("%d",&x);	
		if(pos+x>n)
			pos=1;
		else if(pos+x<1)
			pos=n;
		else
			pos += x;
		
		if(pos == s)
				cont2++;
		
	}
	printf("%d\n",cont2);
	return 0;
}

