/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define ESC 27

/*Ir desenfileirando, mostrando o elemento,
e salvar esse elemento em uma fila auxiliar
depois "copiar" essa auxiliar pra fila normal*/

typedef struct no *def_fila;
struct no{
    int info;
    def_fila prox;
};

//Funções Básicas da Fila Dinâmica
int VerificaVazia(def_fila final){
    return (final == NULL);
}
void Enfileira(def_fila *final, int info){
    //Auxiliar para Enfileirar
    def_fila q = (def_fila)malloc(sizeof(struct no));
    q->info = info;
    if(VerificaVazia((*final))) //Se a lista estiver vazia
        (*final) = q;
    else
        q->prox = (*final)->prox;
    (*final)->prox = q;
    (*final) = q;
}
int Defenfileira(def_fila *final, int *info){
    if(VerificaVazia((*final)))
        return 0;
    
    def_fila q = (*final)->prox; //Primeiro elemento
    (*info) = q->info;
    if(q == (*final))
        (*final) = NULL; //Se for elemento único
    else
        (*final)->prox = q->prox; //Se houver mais de um elemento
    free(q);
    return 1;
}
//Função Principal de Visualizar a Fila
int Visualizar(def_fila *final){
    if(VerificaVazia((*final)))
        return 0;
    printf("\nFila Atual\n\n");

    //Sem ferir conceito de fila: desenfileirar, mostrar e jogar elemento na outra fila
    def_fila q = (*final), aux = NULL;
    int info_aux;
    if(q == (*final)->prox){ //Um elemento
        if(Defenfileira(&(*final), &info_aux)){
            printf("%d\n", info_aux);
            Enfileira(&aux, info_aux);
        }
    }
    else{ //Mais de um elemento
        while(Defenfileira(&q, &info_aux)){
            printf("%d\t", info_aux);
            Enfileira(&aux, info_aux);
        }
    }

    //Após o final do processo, a Fila Principal recebe a Auxiliar
    (*final) = aux;

    return 1;
}

int main(){

    //Inicialização das Filas
    def_fila fila_principal = NULL;

    //Auxiliar para manipulação das opções
    char opc_menu, opc_func;
    //Variável para pegar o elemento
    int elemento;

    while (opc_menu != ESC)
    {
        printf("\nFila Dinamica\n\n");
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
                Enfileira(&fila_principal, elemento);
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
                    if (Defenfileira(&fila_principal, &elemento))
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
        case '3':
            if(Visualizar(&fila_principal)){
                printf("\n\n");
            }
            else{
                printf("\nFila vazia! Insira elementos na funcao 1 do menu anterior.\n\n");
            }
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