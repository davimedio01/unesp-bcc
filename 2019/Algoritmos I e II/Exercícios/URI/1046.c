#include <stdio.h>

int main()
{
    int hr_ini, hr_fin, duracao;
    scanf("%i %i",&hr_ini, &hr_fin);
    if((hr_ini>=0 && hr_ini<=23) && (hr_fin>=0 && hr_fin<=23))
    {
        if(hr_ini==hr_fin)
            printf("O JOGO DUROU 24 HORA(S)\n");
        else if(hr_ini>hr_fin)
        {
            duracao = 24 + hr_fin - hr_ini;
            printf("O JOGO DUROU %i HORA(S)\n", duracao);
        }
        else if(hr_ini<hr_fin)
        {
            duracao = hr_fin - hr_ini;
            printf("O JOGO DUROU %i HORA(S)\n", duracao);
        }
    }
    return 0;
}
