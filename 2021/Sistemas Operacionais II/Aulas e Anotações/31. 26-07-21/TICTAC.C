#include <system.h>
#include <stdio.h>

/* Criando ponteiros para corotinas */
PTR_DESC dmain, dtic, dtac;

void far tic(){
     while(1){
       printf("tic");
       /* Transferindo controle para a corotina "tac" */
       transfer(dtic, dtac);
     }
}

void far tac(){
     while(1){
       printf("tac");
       /* Transferindo controle para a corotina "tic" */
       transfer(dtac, dtic);
     }
}

main(){
    /* Inicializando descritores (ponteiros) */
    dmain = cria_desc();
    dtic = cria_desc();
    dtac = cria_desc();
    /* Criando processos associados as corotinas. A do main j  ‚ realizada pelo SO. */
    newprocess(tic, dtic);
    newprocess(tac, dtac);
    /* Iniciando corotina tic */
    transfer(dmain, dtic);
}