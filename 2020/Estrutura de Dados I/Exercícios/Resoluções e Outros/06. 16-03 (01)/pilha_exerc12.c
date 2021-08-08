/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define ESC 27

//Estrutura da Pilha LCSE
typedef struct no *def_pilha;
struct no{
    int info;
    def_pilha prox;
};
//Letra B
int VerificaVazia(def_pilha pilha){
    return (pilha == NULL);
}
//Letra C: Inserindo no início
void Empilha(def_pilha *pilha, int info){
    def_pilha q;
    CriarNo(&q, info);

    //Se for o primeiro elemento
    if(VerificaVazia((*pilha))){
        q->prox = q;
        (*pilha) = q;
    }
    else{ //Do contrário: ir até o ultimo elemento
        def_pilha r = (*pilha);
        while (r->prox != (*pilha)){
            r = r->prox;
        }
        q->prox = (*pilha);
        (*pilha) = q;
        r->prox = (*pilha);
    }
}
//Auxiliar
void CriarNo (def_pilha *pilha, int info){
    def_pilha q = (def_pilha)malloc(sizeof(struct no));
    q->info = info;
    q->prox = NULL;
    (*pilha) = q;
}
//Letra D
int Desempilha(def_pilha *pilha, int *info){
    if(VerificaVazia((*pilha)))
        return 0;

    //Um elemento
    if((*pilha)->prox == (*pilha)){
        (*info) = (*pilha)->info;
        free((*pilha));
        (*pilha) = NULL;
    }
    else{ //Mais de um elemento
        //Ir até ultimo elemento
        def_pilha r = (*pilha);
        while (r->prox != (*pilha))
            r = r->prox;
        //Eliminando primeiro elemento
        def_pilha q = (*pilha);
        (*info) = q->info;
        (*pilha) = (*pilha)->prox;
        r->prox = (*pilha);
        free(q);
    }
    
    return 1;
}
//Letra E
void Visualizar(def_pilha pilha){
    if(VerificaVazia(pilha)){
        printf("\nPilha Vazia\n\n");
        return;
    }
    printf("\nPilha Atual\n\n");
    def_pilha q = pilha;
    do{
        printf("%d\n", q->info);
        q = q->prox;
    }while(q != pilha);
    printf("\n");
}

int main(){

    //Letra A
    def_pilha pilha = NULL;

    //Auxiliar para manipulação das opções
    char opc_menu, opc_func;
    //Variável para pegar o elemento
    int elemento;

    while (opc_menu != ESC)
    {
        printf("\nPilha - LCSE\n\n");
        printf("1 - Empilhar um Elemento\n");
        printf("2 - Desempilhar um Elemento\n");
        printf("3 - Visualizar a Pilha\n");
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
                printf("\nEmpilhamento\n\n");
                printf("Digite o elemento inteiro a ser empilhado: ");
                scanf("%d", &elemento);
                printf("\n\nEmpilhando. Aguarde...\n\n");
                Sleep(3000);
                Empilha(&pilha, elemento);
                printf("\nElemento empilhado com sucesso!\n\n");
                system("pause");
                system("cls");
                printf("\nDeseja empilhar mais um elemento?(S/N)\n");
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
                printf("\nDesempilhamento\n\n");
                printf("\nDeseja realmente desempilhar o ultimo elemento? (S/N)\n");
                do
                {
                    opc_func = toupper(getch());
                } while (opc_func != 'S' && opc_func != 'N');
                if (opc_func == 'S')
                {
                    printf("\n\nDesempilhando. Aguarde...\n\n");
                    Sleep(3000);
                    if (Desempilha(&pilha, &elemento))
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