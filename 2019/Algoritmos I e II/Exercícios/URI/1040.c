#include <stdio.h>
#include <stdlib.h>

int main()
{
    float n1,n2,n3,n4,media,exame,media_nova;
    scanf("%f %f %f %f",&n1,&n2,&n3,&n4);
    media= (n1*2+n2*3+n3*4+n4)/10;
    printf("Media: %.1f\n",media);

    if(media>=7.0)
        printf("Aluno aprovado.\n");
    else if(media<5.0)
        printf("Aluno reprovado.\n");
    else
    {
        printf("Aluno em exame.\n");
        scanf("%f",&exame);
        printf("Nota do exame: %.1f\n",exame);
        media_nova=((media+exame)/2);
            if(media_nova>=5.0)
                printf("Aluno aprovado.\n");
            else
                printf("Aluno reprovado.\n");
        printf("Media final: %.1f\n",media_nova);
    }

    return 0;
}
