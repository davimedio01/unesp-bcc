/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define ESC 27

//Estrutura da Fila LLSE
typedef struct no *def_fila;
struct no{
    int info;
    def_fila prox;
};
//Enfileirar = Início
void EnfileirarInicio(def_fila *inicio, def_fila *fim, int info)
{
    //Alocando elemento
    def_fila q = (def_fila)malloc(sizeof(struct no));
    q->info = info;
    q->prox = NULL;

    //Primeiro elemento
    if ((*inicio) == NULL)
        (*fim) = q;
    else //Mais de um elemento
        q->prox = (*inicio);
    (*inicio) = q;
}
//Enfileirar = Final
void EnfileirarFinal(def_fila *inicio, def_fila *fim, int info)
{
    //Alocando elemento
    def_fila q = (def_fila)malloc(sizeof(struct no));
    q->info = info;
    q->prox = NULL;

    //Primeiro elemento
    if((*fim) == NULL)
        (*inicio) = q;
    else //Mais de um elemento
        (*fim)->prox = q;
    (*fim) = q;
}
//Desenfileirar = Início
int DesenfileiraInicio(def_fila *inicio, def_fila *fim, int *info){
    if((*inicio) == NULL)
        return 0;
    
    def_fila q = (*inicio);
    (*info) = q->info;
    //Avançando o Início e Verificando com o Final
    (*inicio) = (*inicio)->prox;
    if((*inicio) == NULL)
        (*fim) = NULL; //Se ficou nulo, acabou a lista
    free(q);
    return 1;
}
//Desenfileirar = Final
int DesenfileiraFinal(def_fila *inicio, def_fila *fim, int *info)
{
    if ((*fim) == NULL)
        return 0;

    def_fila q = (*fim);
    (*info) = q->info;
    //Percorrendo a lista até o penultimo elemento
    def_fila r = (*inicio);
    if(r == (*fim)){ //Um elemento
        free(r);
        (*inicio) = (*fim) = NULL;
    }
    else{ //Mais de um elemento
        while (r->prox != q){
            r = r->prox;
        }
        //Eliminando o final
        r->prox = NULL;
        (*fim) = r;
        free(q);
    }
    return 1;
}
//Visualizar
void Visualizar(def_fila inicio, def_fila fim){
    if(inicio == NULL){
        printf("\nFila Vazia\n\n");
        return;
    }
    printf("\nFila Atual\n\n");
    def_fila q = inicio;
    while(q){
        printf("%d\t", q->info);
        q = q->prox;
    }
    printf("\n\n");
}

int main(){

    //Declaração do Início e Fim da Fila LLSE
    def_fila inicio = NULL, fim = NULL;

    //Auxiliar para manipulação das opções
    char opc_menu, opc_func;
    //Variável para pegar o elemento
    int elemento;

    while (opc_menu != ESC)
    {
        printf("\nFila Dupla (Deque)\n\n");
        printf("1 - Enfileirar Elemento - Inicio\n");
        printf("2 - Enfileirar Elemento - Final\n");
        printf("3 - Desenfileirar Elemento - Inicio\n");
        printf("4 - Desenfileirar Elemento - Final\n");
        printf("5 - Visualizar a Fila\n");
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
                printf("\nEnfileirando - Inicio\n\n");
                printf("Digite o elemento inteiro a ser enfileirado no inicio: ");
                scanf("%d", &elemento);
                printf("\n\nEnfileirando. Aguarde...\n\n");
                Sleep(3000);
                EnfileirarInicio(&inicio, &fim, elemento);
                printf("\nElemento enfileirado com sucesso!\n\n");
                system("pause");
                system("cls");
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
                printf("\nEnfileirando - Final\n\n");
                printf("Digite o elemento inteiro a ser enfileirado no final: ");
                scanf("%d", &elemento);
                printf("\n\nEnfileirando. Aguarde...\n\n");
                Sleep(3000);
                EnfileirarFinal(&inicio, &fim, elemento);
                printf("\nElemento enfileirado com sucesso!\n\n");
                system("pause");
                system("cls");
                printf("\nDeseja enfileirar mais um elemento?(S/N)\n");
                do
                {
                    opc_func = toupper(getch());
                } while (opc_func != 'S' && opc_func != 'N');
                system("cls");
            } while (opc_func == 'S');
            break;
        case '3':
            do
            {
                printf("\nDesenfileirando - Inicio\n\n");
                printf("\nDeseja realmente desenfileirar o primeiro elemento? (S/N)\n");
                do
                {
                    opc_func = toupper(getch());
                } while (opc_func != 'S' && opc_func != 'N');
                if (opc_func == 'S')
                {
                    printf("\n\nDesenfileirando. Aguarde...\n\n");
                    Sleep(3000);
                    if (DesenfileiraInicio(&inicio, &fim, &elemento))
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
                }
                system("cls");
            } while (opc_func == 'S');
            break;
        case '4':
            do
            {
                printf("\nDesenfileirando - Final\n\n");
                printf("\nDeseja realmente desenfileirar o ultimo elemento? (S/N)\n");
                do
                {
                    opc_func = toupper(getch());
                } while (opc_func != 'S' && opc_func != 'N');
                if (opc_func == 'S')
                {
                    printf("\n\nDesenfileirando. Aguarde...\n\n");
                    Sleep(3000);
                    if (DesenfileiraFinal(&inicio, &fim, &elemento))
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
                }
                system("cls");
            } while (opc_func == 'S');
            break;
        case '5':
            Visualizar(inicio, fim);
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