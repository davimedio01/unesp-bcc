#include <stdio.h>


int main()
{
    int L,C,branca=1,preta=0;
    scanf("%d",&L);
    scanf("%d",&C);

    printf("%d\n",(1+(L-1)+(C-1))%2);

    return 0;
}
