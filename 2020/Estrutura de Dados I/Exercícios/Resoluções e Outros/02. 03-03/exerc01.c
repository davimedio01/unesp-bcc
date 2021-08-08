/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <windows.h>

#define MAX 100 //Tamanho máximo da pilha
#define ESC 27


//Funções da Pilha
//Letra B
int verificaVazia(int pilha[]){
    if (pilha[0] == 0)
        return 1;
    return 0;
}
//Letra C
int verificaCheia(int pilha[]){
    if(pilha[0] == (MAX-1))
        return 1;
    return 0;
}
//Letra D
int Empilhar(int *pilha, int elemento){
    if (verificaCheia(pilha)){
        return 0;
    }
    pilha[++pilha[0]] = elemento;
    return 1;
}
//Letra E
int Desempilhar(int *pilha, int *elemento){
    if(verificaVazia(pilha)){
        return 0;
    }
    (*elemento) = pilha[pilha[0]--];
    return 1;
}
//Letra F
void Visualizar(int pilha[]){
    if(verificaVazia(pilha)){
        printf("\nPilha vazia\n\n");
    }
    else{
        printf("\nPilha Atual\n\n");
        int i;
        for(i = pilha[0]; i>=1; i--){
            printf("%d\n", pilha[i]);
        }
        printf("\n");
    }
}

int main(){

    //Letra A
    //Declaração da pilha (usarei o tipo inteiro neste exercício, pela simplicidade)
    int pilha[MAX];
    //Primeira posição do vetor contendo o controle do topo da pilha
    pilha[0] = 0;

    //Auxiliar para manipulação das opções
    char opc_menu, opc_func;
    //Variável para pegar o elemento
    int elemento;
    
    while(opc_menu != ESC){
        printf("\nPilha\n\n");
        printf("1 - Empilhar um Elemento\n");
        printf("2 - Desempilhar um Elemento\n");
        printf("3 - Visualizar a Pilha\n");
        printf("\nESC - Sair\n\n");
        printf("Sua opcao: ");
        opc_menu = toupper(getch());
        system("cls");
        if (opc_menu == ESC)
            break;
        switch(opc_menu){
            case '1':
                do{
                    printf("\nEmpilhamento\n\n");
                    printf("Digite o elemento inteiro a ser empilhado: ");
                    scanf("%d", &elemento);
                    printf("\n\nEmpilhando. Aguarde...\n\n");
                    Sleep(3000);
                    if(Empilhar(&pilha, elemento)){
                        printf("\nElemento empilhado com sucesso!\n\n");
                        system("pause");
                        system("cls");
                    }
                    else{
                        printf("\nErro ao empilhar elemento. Tente novamente.\n\n");
                        system("pause");
                        break;
                    }
                    printf("\nDeseja empilhar mais um elemento?(S/N)\n");
                    do{
                        opc_func = toupper(getch());
                    }while(opc_func != 'S' && opc_func != 'N');
                    system("cls");
                }while(opc_func == 'S');
                break;
            case '2':
                do
                {
                    printf("\nDesempilhamento\n\n");
                    printf("\nDeseja realmente desempilhar o ultimo elemento? (S/N)\n");
                    do
                    {
                        opc_func = toupper(getch());
                    } while (opc_func != 'S' && opc_func != 'N');
                    if(opc_func == 'S'){
                        printf("\n\nDesempilhando. Aguarde...\n\n");
                        Sleep(3000);
                        if (Desempilhar(&pilha, &elemento))
                        {
                            printf("\nElemento '%d' desempilhado com sucesso!\n\n", elemento);
                            system("pause");
                            system("cls");
                        }
                        else
                        {
                            printf("\nErro ao desempilhar elemento. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                    }
                    system("cls");
                } while (opc_func == 'S');
                break;
            case '3':
                Visualizar(pilha);
                system("pause");
                break;
            default:
                printf("\nOpcao incorreta. Tente novamente.\n\n");
                printf("Retornando ao menu...\n");
                Sleep(3000);
                break;
        }
        system("cls");
    }
    
    return 0;
}