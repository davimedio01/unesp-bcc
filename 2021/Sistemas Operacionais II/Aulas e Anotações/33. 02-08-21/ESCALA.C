#include <system.h>
#include <stdio.h>

PTR_DESC dmain, dcorA, dcorB, descala;

void far corotina_A(){
  while(1){
    printf("COROTINA-A");
  }
}

void far corotina_B(){
  while(1){
    printf("COROTINA-B");
  }
}

void far escalador(){
  /* Inicializando vari veis de entrada do iotransfer() */
  p_est->p_origem = descala; /* Origem = Escalador   */
  p_est->p_destino = dcorA;  /* Destino = Corotina A */
  p_est->num_vetor = 8;      /* Timer = reg. 8       */

  while(1){
    iotransfer();
    disable();
    if(p_est->p_destino == dcorA){
      /* Trocando o destino para a Corotina B */
      p_est->p_destino = dcorB;
    }
    else{
      /* Trocando o destino para a Corotina A */
      p_est->p_destino = dcorA;
    }
    enable();
  }
}

main(){
  dmain = cria_desc();
  dcorA = cria_desc();
  dcorB = cria_desc();
  descala = cria_desc();

  newprocess(corotina_A, dcorA);
  newprocess(corotina_B, dcorB);
  newprocess(escalador, descala);

  transfer(dmain, descala);

  printf("\nFim Programa\n");
  system("pause");
}