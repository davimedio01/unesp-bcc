/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

//Letra A: Declaração da Estrutura (Lista Circular)
typedef struct no *fila_duque;
struct no{
    //Guardando a Informação do Veículo e seu caminho desejado
    int veiculo, rotatoria;
    fila_duque prox;
};
//Letra B: Verificação de Caminhos da Fila
int VerificaPermissao(int veiculo, int rotatoria){
    if ((veiculo == 2 && rotatoria == 1) ||
        (veiculo == 3 && rotatoria == 2) ||
        (veiculo == 4 && rotatoria == 3) ||
        (veiculo == 5 && rotatoria == 4) ||
        (veiculo == 1 && rotatoria == 5))
        return 0;
    return 1;
}
//Letra C: Enfileira e Desenfileirar (Lista Circular)
void Enfileirar(fila_duque *fila, int veiculo, int rotatoria){
    fila_duque q = (fila_duque)malloc(sizeof(struct no));
    //Armazenando a informação na fila
    q->veiculo = veiculo;
    q->rotatoria = rotatoria;
    
    //Se for o primeiro elemento
    if(VerificaVazia((*fila)))
        (*fila) = q;
    else //Do contrário
        q->prox = (*fila)->prox;
    (*fila)->prox = q; //Circular
    (*fila) = q;       //Inserção no Final
}
int Desenfileirar(fila_duque *fila, int *veiculo, int *rotatoria){
    if(VerificaVazia((*fila)))
        return 0;

    fila_duque q = (*fila)->prox;
    //Recuperando a informação
    (*veiculo) = q->veiculo;
    (*rotatoria) = q->rotatoria;

    if(q == (*fila)) //Um elemento
        (*fila) = NULL;
    else //Mais de um elemento
        (*fila)->prox = q->prox;
    free(q);
    return 1;
}
int VerificaVazia(fila_duque fila){
    return (fila == NULL);
}
//Letra D: Simulação do Comportamento do Policial
void Policiamento(fila_duque *principal){
    //Auxiliares
    int veiculo, rotatoria;
    //Ir verificando enquanto desenfileira
    while(Desenfileirar(&(*principal), &veiculo, &rotatoria)){
        printf("\nROTATORIA - AV. DUQUE DE CAXIAS\n\n");
        printf("INFORMACOES DO VEICULO ATUAL:\n\n");
        printf("\tTIPO: %d\n", veiculo);
        printf("\tSAIDA DESEJADA: %d\n\n", rotatoria);
        //Verificando compatibilidade
        if(VerificaPermissao(veiculo, rotatoria) == 0){
            if(rotatoria == 5){
                printf("PERMISSAO: NEGADO\n");
                printf("Veiculo encaminhado para a saida '1' da rotatoria.\n\n");
            }
            else{
                printf("PERMISSAO: NEGADO\n");
                printf("Veiculo encaminhado para a saida '%d' da rotatoria.\n\n", rotatoria+1);
            }
        }
        else{
            printf("PERMISSAO: PERMITIDO\n\n");
        }
        system("pause");
        system("cls");
    }

}

int main(){

    //Declaração da Fila Principal
    fila_duque principal = NULL;
    //Auxiliares
    int veiculo, rotatoria;
    
    //Menu para Inserção dos Veículos na Fila
    do{
        printf("\nROTATORIA - AV. DUQUE DE CAXIAS\n\n");
        printf("VEICULOS DISPONIVEIS (POR TIPO):\n\n");
        printf("\t1 - CARRO\n\n");
        printf("\t2 - CAMINHAO\n\n");
        printf("\t3 - MOTO\n\n");
        printf("\t4 - BICICLETA\n\n");
        printf("\t5 - VANS\n\n");
        printf("Digite o TIPO desejado para insercao na fila (0 para sair): ");
        do{
            scanf("%d", &veiculo);
        }while(veiculo < 0 || veiculo > 5);
        if(veiculo == 0){
            system("cls");
            break;
        }
        printf("Agora, digite a saida da rotatoria (1 a 5) de destino do veiculo indicado: ");
        do{
            scanf("%d", &rotatoria);
        }while(rotatoria < 1 || rotatoria > 5);
        system("cls");

        //Inserindo veículo e caminho desejado na fila
        printf("Inserindo veiculo e caminho desejado. Aguarde...\n\n");
        Sleep(3000);
        Enfileirar(&principal, veiculo, rotatoria);
        printf("Veiculo e caminho inseridos com sucesso!\n\n");
        system("pause");
        system("cls");

    }while(veiculo != 0);
    
    //Após a inserção, basta ir verificando a compatibilidade de veiculo com caminho
    Policiamento(&principal);

    return 0;

}