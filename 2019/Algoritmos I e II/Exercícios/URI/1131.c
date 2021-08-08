#include <stdio.h>
#include <stdlib.h>

int main()
{
    int gremio,inter,vi=0,vg=0,em=0,qtd=0,nv_gre;
    while(1)
    {
        scanf("%i %i",&inter,&gremio);
        if(inter>gremio)
        {
            vi++;
            qtd++;
        }
        else if(inter<gremio)
        {
            vg++;
            qtd++;
        }
        else if(inter==gremio)
        {
            em++;
            qtd++;
        }
        printf("Novo grenal (1-sim 2-nao)\n");
        scanf("%i",&nv_gre);
        if(nv_gre==2)
            break;
        else if(nv_gre==1)
            continue;
    }
    printf("%i grenais\n",qtd);
    printf("Inter:%i\n",vi);
    printf("Gremio:%i\n",vg);
    printf("Empates:%i\n",em);
    if(vi>vg)
        printf("Inter venceu mais\n");
    else if(vi<vg)
        printf("Gremio venceu mais\n");
    else
        printf("Nao houve vencedor\n");

    return 0;
}
