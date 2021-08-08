#include <stdio.h>
#include <math.h>

int main()
{
    int hr_ini,min_ini,hr_fin,min_fin,total_hr,total_min;
    scanf("%i %i %i %i", &hr_ini, &min_ini, &hr_fin, &min_fin);

    if(hr_ini==min_fin && hr_fin==min_fin && min_fin==min_ini)
    {
        total_min=min_ini-min_fin;
        total_hr=24+hr_ini-hr_fin;
        printf("O JOGO DUROU %i HORA(S) E %i MINUTO(S)\n", total_hr, total_min);
    }
    else if(hr_ini==hr_fin && min_ini<min_fin)
    {
        total_min=min_fin-min_ini;
        total_hr=hr_ini-hr_fin;
        printf("O JOGO DUROU %i HORA(S) E %i MINUTO(S)\n", total_hr, total_min);
    }
    else if(hr_ini==hr_fin && min_ini>min_fin)
    {
        total_min=60-min_ini+min_fin;
        total_hr=24-hr_ini+hr_fin-1;
        printf("O JOGO DUROU %i HORA(S) E %i MINUTO(S)\n", total_hr, total_min);
    }
    else if(hr_ini<hr_fin && min_ini==min_fin)
    {
        total_hr=hr_fin-hr_ini;
        printf("O JOGO DUROU %i HORA(S) E 0 MINUTO(S)\n", total_hr);
    }
    else if(hr_ini>hr_fin && min_ini==min_fin)
    {
        total_hr=24-hr_ini+hr_fin;
        printf("O JOGO DUROU %i HORA(S) E 0 MINUTO(S)\n", total_hr);
    }
    else if(hr_ini<hr_fin && min_ini<min_fin)
    {
        total_min=min_fin-min_ini;
        total_hr=hr_fin-hr_ini;
        printf("O JOGO DUROU %i HORA(S) E %i MINUTO(S)\n", total_hr, total_min);
    }
    else if(hr_ini<hr_fin && min_ini>min_fin)
    {
        total_min=60-min_ini+min_fin;
        total_hr=hr_fin-hr_ini-1;
        printf("O JOGO DUROU %i HORA(S) E %i MINUTO(S)\n", total_hr, total_min);
    }
    else if(hr_ini>hr_fin && min_ini<min_fin)
    {
        total_min=min_fin-min_ini;
        total_hr=24-hr_ini+hr_fin-1;
        printf("O JOGO DUROU %i HORA(S) E %i MINUTO(S)\n", total_hr, total_min);
    }
    else if(hr_ini>hr_fin && min_ini>min_fin)
    {
        total_min=60+min_fin-min_ini;
        total_hr=24-hr_ini+hr_fin-1;
        printf("O JOGO DUROU %i HORA(S) E %i MINUTO(S)\n", total_hr, total_min);
    }
    return 0;
}
