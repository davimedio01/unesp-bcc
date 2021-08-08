/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define MAX 100
#define ESC 27

//Funções da Fila (Método 1)
int VerificaCheia(int fila[]){
    return (fila[1] == MAX-1);
}
int VerificaVazia(int fila[]){
    return ((fila[0] == 1) || (fila[0] > fila[1]));
}
int Enfileira(int *fila, int elemento){
    if(VerificaCheia(fila))
        return 0;
    
    //Incrementar o Final
    fila[1]++;

    //Jogando Elemento no Final
    fila[fila[1]] = elemento;

    //Se for o primeiro elemento
    if(fila[0] == 1)
        fila[0] = 2;

    return 1;
}
int Desenfileira(int *fila, int *elemento){
    if(VerificaVazia((fila)))
        return 0;

    //int inicio = fila[0];
    (*elemento) = fila[fila[0]];
    //fila[fila[0]] = -1; //Zerando a posição do elemento retirado
    fila[0]++;
    return 1;
}
void Visualizar(int fila[]){
    if(VerificaVazia(fila)){
        printf("\nFila vazia. Insira elementos na funcao 1 do menu anterior.\n\n");
        return;
    }
    printf("\nFila Atual\n\n");
    int i;
    for (i = fila[0]; i <= fila[1]; i++){
        printf("%d\t", fila[i]);
    }
    printf("\n\n");
}

int main(){

    //Declaração da Fila
    int fila[MAX];
    fila[0] = 1; //Topo
    fila[1] = 1; //Final

    //Auxiliar para manipulação das opções
    char opc_menu, opc_func;
    //Variável para pegar o elemento
    int elemento;

    while (opc_menu != ESC)
    {
        printf("\nFila - Metodo 1\n\n");
        printf("1 - Enfileirar um Elemento\n");
        printf("2 - Desenfileirar um Elemento\n");
        printf("3 - Visualizar a Fila\n");
        printf("\nESC - Sair\n\n");
        printf("Sua opcao: ");
        opc_menu = toupper(getch());
        system("cls");
        if (opc_menu == ESC)
            break;
        switch (opc_menu)
        {
        case '1':
            do
            {
                printf("\nEnfileiramento\n\n");
                printf("Digite o elemento inteiro a ser enfileirado: ");
                scanf("%d", &elemento);
                printf("\n\nEnfileirando. Aguarde...\n\n");
                Sleep(3000);
                if (Enfileira(&fila, elemento))
                {
                    printf("\nElemento enfileirado com sucesso!\n\n");
                    system("pause");
                    system("cls");
                }
                else
                {
                    printf("\nErro ao enfileirar elemento. Tente novamente.\n\n");
                    system("pause");
                    break;
                }
                printf("\nDeseja enfileirar mais um elemento?(S/N)\n");
                do
                {
                    opc_func = toupper(getch());
                } while (opc_func != 'S' && opc_func != 'N');
                system("cls");
            } while (opc_func == 'S');
            break;
        case '2':
            do
            {
                printf("\nDesenfileirar\n\n");
                printf("\nDeseja realmente desenfileirar o primeiro elemento? (S/N)\n");
                do
                {
                    opc_func = toupper(getch());
                } while (opc_func != 'S' && opc_func != 'N');
                if (opc_func == 'S')
                {
                    printf("\n\nDesenfileirando. Aguarde...\n\n");
                    Sleep(3000);
                    if (Desenfileira(fila, &elemento))
                    {
                        printf("\nElemento '%d' desenfileirado com sucesso!\n\n", elemento);
                        system("pause");
                        system("cls");
                    }
                    else
                    {
                        printf("\nErro ao desenfileirar elemento. Tente novamente.\n\n");
                        system("pause");
                        break;
                    }
                    if(VerificaVazia(fila)){
                        fila[0] = fila[1] = 1;
                    }
                }
                system("cls");
            } while (opc_func == 'S');
            break;
        case '3':
            Visualizar(fila);
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