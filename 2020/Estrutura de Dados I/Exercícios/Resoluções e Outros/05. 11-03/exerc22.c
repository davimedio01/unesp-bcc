/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define MAX 10
#define ESC 27
/*Ordem de retirada de veículos (por mim): carros, ônibus, caminhões

Máx permitido:
Carros: 6          
Ônibus: 3 
Caminhões: 2       

Pode trocar: 1 caminhão por 3 carros ou 1 ônibus por 2 carros.
Ou seja, no máximo: 18 carros e nenhum do outro.
*/

//Estrutura das Filas utilizadas no Exercício
typedef struct no *def_fila;
struct no{
    //Char contendo o tipo de elemento
    int veiculo;
    //Fila dinâmica (Lista Circular)
    def_fila prox;
};

//Funções Básicas da Fila (Lista Circular)
int VerificaVazia(def_fila fila){
    return (fila == NULL);
}
void Enfileira(def_fila *fila, int veiculo){
    //Auxiliar contendo informação
    def_fila q = (def_fila)malloc(sizeof(struct no));
    //strcpy(q->veiculo, veiculo);
    q->veiculo = veiculo;

    //Se for primeiro elemento
    if(VerificaVazia((*fila)))
        ((*fila)) = q;
    else //Do contrário
        q->prox = (*fila)->prox;
    (*fila)->prox = q; //Circular
    (*fila) = q; //Inserção no Final

}
int Desenfileira(def_fila *fila, int *veiculo){
    if(VerificaVazia((*fila)))
        return 0;
    
    def_fila q = (*fila)->prox;
    //strcpy(veiculo, q->veiculo); //Salvando informação
    (*veiculo) = q->veiculo;

    if(q == (*fila)) //Um elemento
        (*fila) = NULL;
    else //Mais de um elemento
        (*fila)->prox = q->prox;  
    free(q);
    return 1;
}

//Funções do Exercício
//Verificar validade de veículo
int VerificaVeiculoValido(int veiculo){
    return ((veiculo == 1) ||
            (veiculo == 2) || 
            (veiculo == 3) ||
            (veiculo == 0));
}
//Aumentar contador de veículos
void ContarVeiculo(int *cont, int veiculo){
    if(veiculo == 1)
        cont[0]++;
    else if(veiculo == 2)
        cont[1]++;
    else if(veiculo == 3)
        cont[2]++;
}
//Mostrar o Tipo de Veículo
void MostraVeiculo(int veiculo){
    if (veiculo == 1){
        printf("Carro");
    }
    if (veiculo == 2){
        printf("Onibus");
    }
    if (veiculo == 3){
        printf("Caminhao");
    }
}

//Função Principal: Retirar da "Balsa" para "Estrada" (Final)
void RetiraVeiculo(def_fila *carro, def_fila *onibus,
                   def_fila *caminhao, def_fila *estrada)
{
    //Ordem de retirada (por mim): Carro, Ônibus e Caminhão
    //Auxiliar para guardar informação
    int aux;

    //Retirando "Carros"
    while (Desenfileira(&(*carro), &aux))
    {
        Enfileira(&(*estrada), aux);
    }
    //Retirando "Ônibus"
    while (Desenfileira(&(*onibus), &aux))
    {
        Enfileira(&(*estrada), aux);
    }
    //Retirando "Caminhão"
    while (Desenfileira(&(*caminhao), &aux))
    {
        Enfileira(&(*estrada), aux);
    }

    //Desenfileirando da estrada e mostrando na tela
    while (Desenfileira(&(*estrada), &aux))
    {
        MostraVeiculo(aux);
        printf(" ");
    }
}

int main(){

    /*Neste exercício, usarei um contador que irá guardar
    a quantidade de carros, caminhões e ônibus digitados
    pelo usuário. Após isso, ira enfileirar na "balsa"
    e desenfileirar para a "estrada" (um por vez)
    */

    //Declaração das Filas Principais
    def_fila carro = NULL, onibus = NULL, caminhao = NULL;
    def_fila estrada = NULL;
    //Declaração das Fila Auxiliar (Veículos - Desordenado de Entrada)
    def_fila aux_estrada = NULL;
    //Contador de Elementos (relacionado as trocas, se necessário)
    int cont[3];
    cont[0] = cont[1] = cont[2] = 0;

    //Auxiliares com máximo disponível
    int auxmax[3];
    auxmax[0] = 6; auxmax[1] = 3; auxmax[2] = 2;

    //Outras Auxiliares e Variáveis
    char opcfunc;
    int veiculo;

    //Inserção de Elementos na Estrada
    do{
        printf("\nBALSA DO RIO DAVI\n\n");
        printf("VEICULOS DISPONIVEIS PARA EMBARQUE:\n\n");
        printf("\t1 - CARRO       %d RESTANTE(S)\n\n", auxmax[0]);
        printf("\t2 - ONIBUS      %d RESTANTE(S)\n\n", auxmax[1]);
        printf("\t3 - CAMINHAO    %d RESTANTE(S)\n\n", auxmax[2]);
        printf("Digite a opcao desejada para embarque (0 para sair): ");
        do{
            //veiculo = toupper(getch());
            scanf("%d", &veiculo);
        }while(!VerificaVeiculoValido(veiculo));
        system("cls");

        //Verificando a Opção e acrescentando nas Filas
        switch(veiculo){
        case 1:
            if (auxmax[0] > 0)
            {
                printf("\nAcrescentando 'CARRO' na fila. Aguarde...\n\n");
                Sleep(3000);
                Enfileira(&carro, veiculo);
                Enfileira(&aux_estrada, veiculo); //Mostrar a ordem chamada da estrada
                printf("'CARRO' embarcado com sucesso!\n\n");
                cont[0]++;
                auxmax[0]--;
            }
            else
            {
                printf("\nLimite de 'CARRO' atingido. Tente outra opcao.\n\n");
            }
            system("pause");
            break;
        case 2:
            if (auxmax[1] > 0)
            {
                printf("\nAcrescentando 'ONIBUS' na fila. Aguarde...\n\n");
                Sleep(3000);
                Enfileira(&onibus, veiculo);
                Enfileira(&aux_estrada, veiculo); //Mostrar a ordem chamada da estrada
                printf("'ONIBUS' embarcado com sucesso!\n\n");
                cont[1]++;
                auxmax[1]--;
            }
            else
            {
                printf("\nLimite de 'ONIBUS' atingido. Tente outra opcao.\n\n");
            }
            system("pause");
            break;
        case 3:
            if (auxmax[2] > 0)
            {
                printf("\nAcrescentando 'CAMINHAO' na fila. Aguarde...\n\n");
                Sleep(3000);
                Enfileira(&caminhao, veiculo);
                Enfileira(&aux_estrada, veiculo); //Mostrar a ordem chamada da estrada
                printf("'CAMINHAO' embarcado com sucesso!\n\n");
                cont[2]++;
                auxmax[2]--;
            }
            else
            {
                printf("\nLimite de 'CAMINHAO' atingido. Tente outra opcao.\n\n");
            }
            system("pause");
            break;
        }
        system("cls");
        if((!auxmax[0]) && (!auxmax[1]) && (!auxmax[2])){
            printf("\nOpcoes esgotadas. Saindo da insercao...\n\n");
            Sleep(3000);
            system("cls");
            break;
        }
    }while(veiculo != 0);

    //Mostrando a Estrada digitada
    printf("\nBALSA DO RIO DAVI\n\n");
    printf("\nESTRADA INSERIDA:\n\n");
    while (Desenfileira(&aux_estrada, &veiculo))
    {
        MostraVeiculo(veiculo);
        printf(" ");
    }
    printf("\n\n\n");
    system("pause");
    system("cls");


    //Verificar se deseja trocar, caso disponível, caminhões/ônibus por carros
    int i;
    do{
        printf("\nBALSA DO RIO DAVI\n\n");
        printf("EH POSSIVEL REALIZAR AS SEGUINTES TROCAS ABAIXO:\n\n");
        printf("\t1 - 1 ONIBUS   POR 2 CARROS\n\n");
        printf("\t2 - 1 CAMINHAO POR 3 CARROS\n\n");
        printf("\nTOTAL DE VEICULOS DA BALSA ATUAL:\n\n");
        printf("\t'%d' - CARROS\n\n", cont[0]);
        printf("\t'%d' - ONIBUS\n\n", cont[1]);
        printf("\t'%d' - CAMINHAO\n\n", cont[2]);
        printf("\nDIGITE 0 PARA SAIR DESTE MENU.\n\n");
        printf("Sua opcao: ");
        do{
            //veiculo = toupper(getch());
            scanf("%d", &veiculo);
        }while(veiculo < 0 && veiculo >2);
        system("cls");

        //Verificando a opção e realizando as operações válidas
        switch(veiculo){
        case 1:
            if(cont[1] > 0){
                //Desenfileirar o ONIBUS e enfileirar o CARRO
                printf("\nDesenfileirando e trocando 'ONIBUS' por 'CARROS'. Aguarde...\n");
                Sleep(3000);
                if(Desenfileira(&onibus, &veiculo)){
                    for (i = 1; i <= 2; i++)
                    {
                        Enfileira(&carro, 1);
                    }
                }
                printf("\nTroca realizada com sucesso!\n\n");
                cont[0] += 2;
                cont[1]--;
            }
            else{
                printf("\nLimite de troca de 'ONIBUS' atingido. Tente outra opcao.\n\n");
            }
            system("pause");
            break;
        case 2:
            if (cont[2] > 0)
            {
                //Desenfileirar o CAMINHAO e enfileirar o CARRO
                printf("\nDesenfileirando e trocando 'CAMINHAO' por 'CARROS'. Aguarde...\n");
                Sleep(3000);
                if (Desenfileira(&caminhao, &veiculo))
                {
                    for (i = 1; i <= 3; i++)
                    {
                        Enfileira(&carro, 1);
                    }
                }
                printf("\nTroca realizada com sucesso!\n\n");
                cont[0] += 3;
                cont[2]--;
            }
            else
            {
                printf("\nLimite de troca de 'CAMINHAO' atingido. Tente outra opcao.\n\n");
            }
            system("pause");
            break;
        }
        system("cls");
        if ((!cont[1]) && (!cont[2]))
        {
            printf("\nOpcoes esgotadas. Saindo da troca...\n\n");
            Sleep(3000);
            system("cls");
            break;
        }
    }while(veiculo!=0);

    //Por fim, joga da balsa na estrada e mostra tudo em ordem
    printf("\nBALSA DO RIO DAVI\n\n");
    printf("\nRETIRADA DA BALSA PARA A ESTRADA DO OUTRO LADO:\n\n");
    //Retirando veículos da balsa e colocando na estrada
    RetiraVeiculo(&carro, &onibus, &caminhao, &estrada);
    printf("\n\n\n");
    system("pause");
    system("cls");

    return 0;

}