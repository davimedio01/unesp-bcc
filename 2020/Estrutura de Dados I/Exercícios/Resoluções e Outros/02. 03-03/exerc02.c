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
int verificaVazia(int pilha[], int topo1, int topo2, int opc)
{
    //Pilha 1
    if(opc == 1){
        if(topo1 == -1)
            return 1;
        return 0;
    } //Pilha 2
    else if(opc == 2){
        if(topo2 == MAX)
            return 1;
        return 0;
    }
}
//Letra C
int verificaCheia(int pilha[], int topo1, int topo2)
{
    if(topo1 == (topo2-1)){
        return 1;
    }
    return 0;
}
//Letra D
int Empilhar(int *pilha, int *topo1, int *topo2, int opc, int elemento)
{
    if(verificaCheia(pilha, (*topo1), (*topo2))){
        return 0;
    }

    //Pilha 1
    if(opc == 1){
        pilha[++(*topo1)] = elemento;
    } //Pilha 2
    else if (opc == 2){
        pilha[--(*topo2)] = elemento;
    }
    return 1;
}
//Letra E
int Desempilhar(int *pilha, int *topo1, int *topo2, int opc, int *elemento)
{
    if(verificaVazia(pilha, (*topo1), (*topo2), opc)){
        return 0;
    }

    //Pilha 1
    if(opc == 1){
        (*elemento) = pilha[(*topo1)--];
    } //Pilha 2
    else if(opc == 2){
        (*elemento) = pilha[(*topo2)++];
    }
}
//Letra F
void Visualizar(int pilha[], int topo1, int topo2, int opc)
{
    if(verificaVazia(pilha, topo1, topo2, opc)){
        printf("\nPilha vazia\n\n");
    }
    else{
        int i;
        //Pilha 1
        if(opc == 1){
            printf("\nPilha 1 - Atual\n\n");
            for (i = topo1; i >= 0; i--){
                printf("%d\n", pilha[i]);
            }
            printf("\n");
        } //Pilha 2
        else if(opc == 2){
            printf("\nPilha 2 - Atual\n\n");
            for (i = topo2; i < MAX; i++){
                printf("%d\n", pilha[i]);
            }
            printf("\n");
        }
    }
    
}

int main()
{

    //Letra A
    //Declaração das pilhas (usarei o tipo inteiro neste exercício, pela simplicidade)
    int pilha[MAX];

    //Variaveis que armazenam o topo das pilhas 1 e 2, respectivamente
    int topo1 = -1, topo2 = MAX;

    //Auxiliar para manipulação das opções
    char opc_menu, opc_func;
    //Auxiliar para seleção da pilha
    int opc_pilha;
    //Variável para pegar o elemento
    int elemento;

    while (opc_menu != ESC)
    {
        printf("\nPilha Dupla\n\n");
        printf("1 - Empilhar um Elemento na Pilha 1\n");
        printf("2 - Empilhar um Elemento na Pilha 2\n");
        printf("3 - Desempilhar um Elemento da Pilha 1\n");
        printf("4 - Desempilhar um Elemento da Pilha 2\n");
        printf("5 - Visualizar a Pilha 1\n");
        printf("6 - Visualizar a Pilha 2\n");
        printf("\nESC - Sair\n\n");
        printf("Sua opcao: ");
        opc_menu = toupper(getch());
        system("cls");
        if (opc_menu == ESC)
            break;
        switch (opc_menu)
        {
        case '1':
            opc_pilha = 1;
            do
            {
                printf("\nEmpilhamento - Pilha 1\n\n");
                printf("Digite o elemento inteiro a ser empilhado: ");
                scanf("%d", &elemento);
                printf("\n\nEmpilhando. Aguarde...\n\n");
                Sleep(3000);
                if (Empilhar(pilha, &topo1, &topo2, opc_pilha, elemento))
                {
                    printf("\nElemento empilhado com sucesso!\n\n");
                    system("pause");
                    system("cls");
                }
                else
                {
                    printf("\nErro ao empilhar elemento. Tente novamente.\n\n");
                    system("pause");
                    break;
                }
                printf("\nDeseja empilhar mais um elemento?(S/N)\n");
                do
                {
                    opc_func = toupper(getch());
                } while (opc_func != 'S' && opc_func != 'N');
                system("cls");
            } while (opc_func == 'S');
            break;
        case '2':
            opc_pilha = 2;
            do
            {
                printf("\nEmpilhamento - Pilha 2\n\n");
                printf("Digite o elemento inteiro a ser empilhado: ");
                scanf("%d", &elemento);
                printf("\n\nEmpilhando. Aguarde...\n\n");
                Sleep(3000);
                if (Empilhar(pilha, &topo1, &topo2, opc_pilha, elemento))
                {
                    printf("\nElemento empilhado com sucesso!\n\n");
                    system("pause");
                    system("cls");
                }
                else
                {
                    printf("\nErro ao empilhar elemento. Tente novamente.\n\n");
                    system("pause");
                    break;
                }
                printf("\nDeseja empilhar mais um elemento?(S/N)\n");
                do
                {
                    opc_func = toupper(getch());
                } while (opc_func != 'S' && opc_func != 'N');
                system("cls");
            } while (opc_func == 'S');
            break;
        case '3':
            opc_pilha = 1;
            do
            {
                printf("\nDesempilhamento - Pilha 1\n\n");
                printf("\nDeseja realmente desempilhar o ultimo elemento? (S/N)\n");
                do
                {
                    opc_func = toupper(getch());
                } while (opc_func != 'S' && opc_func != 'N');
                if (opc_func == 'S')
                {
                    printf("\n\nDesempilhando. Aguarde...\n\n");
                    Sleep(3000);
                    if (Desempilhar(pilha, &topo1, &topo2, opc_pilha, &elemento))
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
        case '4':
            opc_pilha = 2;
            do
            {
                printf("\nDesempilhamento - Pilha 2\n\n");
                printf("\nDeseja realmente desempilhar o ultimo elemento? (S/N)\n");
                do
                {
                    opc_func = toupper(getch());
                } while (opc_func != 'S' && opc_func != 'N');
                if (opc_func == 'S')
                {
                    printf("\n\nDesempilhando. Aguarde...\n\n");
                    Sleep(3000);
                    if (Desempilhar(pilha, &topo1, &topo2, opc_pilha, &elemento))
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
        case '5':
            opc_pilha = 1;
            Visualizar(pilha, topo1, topo2, opc_pilha);
            system("pause");
            break;
        case '6':
            opc_pilha = 2;
            Visualizar(pilha, topo1, topo2, opc_pilha);
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