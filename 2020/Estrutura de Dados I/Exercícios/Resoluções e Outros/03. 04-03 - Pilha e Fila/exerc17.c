/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>

//Declaração das Estruturas das Pilhas
typedef struct no_pilha01{
    float dado;
    struct no_pilha01 *prox;
}*def_pilha01;
typedef struct no_pilha02{
    char dado;
    struct no_pilha02 *prox;
}*def_pilha02;

//Verificação de Pilha 01 Nula
int VerificaVazia_01(def_pilha01 pilha){
    return (pilha == NULL);
}
//Verificação de Pilha 02 Nula
int VerificaVazia_02(def_pilha02 pilha){
    return (pilha == NULL);
}

//Inserção (Empilha) para Pilha 01
void Empilha_01(def_pilha01 *pilha, float *info){
    def_pilha01 p;
    CriarNo_1(&p, &(*info));
    p->prox = (*pilha);
    (*pilha) = p;
}
//Inserção (Empilha) para Pilha 02
void Empilha_02(def_pilha02 *pilha, char info){
    def_pilha02 p;
    CriarNo_2(&p, info);
    p->prox = (*pilha);
    (*pilha) = p;
}
//Função para Criar Nó (Pilha 01)
void CriarNo_1(def_pilha01 *pilha, float *info){
    def_pilha01 p = (def_pilha01)malloc(sizeof(struct no_pilha01));
    p->dado = (*info);
    p->prox = NULL;
    (*pilha) = p;
}
//Função para Criar Nó (Pilha 02)
void CriarNo_2(def_pilha02 *pilha, char info){
    def_pilha02 p = (def_pilha02)malloc(sizeof(struct no_pilha02));
    p->dado = (info);
    p->prox = NULL;
    (*pilha) = p;
}

//Remoção (Desempilha) para Pilha 01
void Desempilha_01(def_pilha01 *pilha){
    if(VerificaVazia_01((*pilha)))
        return;
    def_pilha01 p = (*pilha);
    (*pilha) = (*pilha)->prox;
    free(p);
    //return 1;
}
//Remoção (Desempilha) para Pilha 02
void Desempilha_02(def_pilha02 *pilha){
    if(VerificaVazia_02((*pilha)))
        return;
    def_pilha02 p = (*pilha);
    (*pilha) = (*pilha)->prox;
    free(p);
    //return 1;
}

//Visualizar as Pilhas 01
void Imprime_01(def_pilha01 pilha, char opc){
    if(opc == '4'){
        printf("\nPilha Final\n\n");
    }
    else{
        printf("\nPilha %c\n\n", opc);
    }
    while(pilha){
        printf("%.1f\n", pilha->dado);
        pilha = pilha->prox;
    }
    printf("\n");
}
//Visualizar a Pilha 02
void Imprime_02(def_pilha02 pilha){
    printf("\nPilha 2\n\n");
    while(pilha){
        printf("%c\n", pilha->dado);
        pilha = pilha->prox;
    }
    printf("\n");
}

//Função Final para Somar as Pilhas
void OperacaoPilhas(def_pilha01 *pilha1, def_pilha02 *pilha2,
                def_pilha01 *pilha3, def_pilha01 *pilha_final)
{

    //Criação da Pilha Aux para as Respostas
    def_pilha01 pilha_aux = NULL;
    float aux = 0.0;

    //Realizando as operações e colocando as respostas na pilha auxiliar
    do{
        //Soma
        if((*pilha2)->dado == '+'){
            aux = (float)((*pilha1)->dado) + ((*pilha3)->dado);
        } //Subtração
        else if((*pilha2)->dado == '-'){
            aux = (float)((*pilha1)->dado) - ((*pilha3)->dado);
        } //Multiplicação
        else if((*pilha2)->dado == '*'){
            aux = (float)((*pilha1)->dado) * ((*pilha3)->dado);
        } //Divisão
        else if((*pilha2)->dado == '/'){
            aux = (float)((*pilha1)->dado) / ((*pilha3)->dado);
        }
        //printf("\n%.1f\n\n", aux);
        Empilha_01(&pilha_aux, &aux);
        Desempilha_01(&(*pilha1));
        Desempilha_02(&(*pilha2));
        Desempilha_01(&(*pilha3));
        aux = 0.0;

    }while(VerificaVazia_01((*pilha1)) == 0 ||
    VerificaVazia_02((*pilha2)) == 0 ||
    VerificaVazia_01((*pilha3)) == 0);

    //"Invertendo" a pilha auxiliar para a pilha final
    do{
        //aux = pilha_aux->dado;
        Empilha_01(&(*pilha_final), &(pilha_aux->dado));
        Desempilha_01(&pilha_aux);
    } while (VerificaVazia_01(pilha_aux) == 0);
}

int main(){

    //Declaração das Pilhas Tipo 01
    def_pilha01 pilha01 = NULL, pilha03 = NULL; 
    //Declaração da Pilha Tipo 02
    def_pilha02 pilha02 = NULL;
    //Declaração das Auxiliares para Pilhas
    float info_01; char info_02;
    //Outras Auxiliares
    char opc; int cont[2];
    cont[0] = cont[1] = 0;

    //Manipulação Pilha 01
    do{
        printf("\nPilha 01\n\n");
        printf("Digite um elemento float a ser empilhado: ");
        scanf("%f", &info_01);
        printf("\n\nEmpilhando o elemento. Aguarde...\n");
        Sleep(3000);
        //info_01 = (float)info_01;
        Empilha_01(&pilha01, &info_01);
        //printf("\n%.1f\n\n", info_01);
        printf("\nElemento empilhado com sucesso!\n\n");
        cont[0]++; cont[1]++;
        system("pause");
        system("cls");
        printf("\nDeseja empilhar mais um elemento?(S/N)\n");
        do{
            opc = toupper(getch());
        }while(opc != 'S' && opc != 'N');
        system("cls");
    }while(opc == 'S');

    //Manipulação Pilha 02
    do{
        fflush(stdin);
        printf("\nPilha 02 - %d operador(es) restante(s)\n\n", cont[0]);
        printf("Digite um operador matematico (+ - * /) a ser empilhado: ");
        //scanf("%c", &info_01);
        do{
            info_02 = toupper(getchar());
        }while(info_02 != '+' && info_02 != '-' && info_02 != '*' && info_02 != '/');
        printf("\n\nEmpilhando o operador. Aguarde...\n");
        Sleep(3000);
        Empilha_02(&pilha02, info_02);
        //printf("\n%c\n\n", info_02);
        printf("\nOperador empilhado com sucesso!\n\n");
        system("pause");
        system("cls");
        /*printf("\nDeseja empilhar mais um operador?(S/N)\n");
        do
        {
            opc = toupper(getch());
        } while (opc != 'S' && opc != 'N');
        system("cls");*/
    }while(--cont[0]);

    fflush(stdin);
    //Manipulação Pilha 03
    do{
        printf("\nPilha 03 - %d elemento(s) restante(s)\n\n", cont[1]);
        printf("Digite um elemento float a ser empilhado: ");
        scanf("%f", &info_01);
        printf("\n\nEmpilhando o elemento. Aguarde...\n");
        Sleep(3000);
        //info_01 = (float)info_01;
        Empilha_01(&pilha03, &info_01);
        //printf("\n%.1f\n\n", info_01);
        printf("\nElemento empilhado com sucesso!\n\n");
        system("pause");
        system("cls");
        /*printf("\nDeseja empilhar mais um elemento?(S/N)\n");
        do
        {
            opc = toupper(getch());
        } while (opc != 'S' && opc != 'N');
        system("cls");*/
    }while(--cont[1]);

    //Visualizando as Pilhas
    printf("\nPilhas Atuais\n\n");
    Imprime_01(pilha01, '1');
    //printf("\n");
    Imprime_02(pilha02);
    //printf("\n");
    Imprime_01(pilha03, '3');
    printf("\n");
    system("pause");
    system("cls");

    //Realizando as operações entre as Pilhas
    printf("\nRealizando as operacoes entre as pilhas. Aguarde...\n");
    Sleep(3000);
    def_pilha01 pilha_final = NULL;
    OperacaoPilhas(&pilha01, &pilha02, &pilha03, &pilha_final);
    printf("\nOperacoes realizadas com sucesso!\n\n");
    system("pause");
    system("cls");

    //Visualizando a Pilha Final
    Imprime_01(pilha_final, '4');
    printf("\n");
    
    return 0;

}