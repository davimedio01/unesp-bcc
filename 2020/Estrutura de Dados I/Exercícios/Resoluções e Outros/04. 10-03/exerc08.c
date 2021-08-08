/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define MAX 100

typedef struct {
    int info[MAX];
    int inicio, fim;
}def_fila;

//Funções Comuns das Filas
int VerificaVazia(def_fila fila){
    //return (fila.inicio == fila.fim); //Pelo menos 2 elementos
    return (fila.inicio == MAX);
}
int VerificaCheia(def_fila fila){
    return (fila.fim == MAX-1);
}
void Enfileirar(def_fila *fila, int elemento){
    if(VerificaCheia((*fila)))
        return;
    
    //Incrementar o Fim
    (*fila).fim++;
    //Adicionar Elemento
    (*fila).info[(*fila).fim] = elemento;
    //Verificar o Início (Primeiro Elemento)
    if((*fila).inicio == -1)
        (*fila).inicio = 0;
    //return 1;
}
void Desenfileirar(def_fila *fila, int *elemento){
    if(VerificaVazia((*fila)))
        return;
    
    //Recuperando elemento a ser ELIMINADO
    (*elemento) = (*fila).info[(*fila).inicio];
    //Aumentando contador do Início
    (*fila).inicio++;
}
void Visualizar(def_fila fila){
    int i;
    for(i=fila.inicio; i<=fila.fim; i++){
        printf("%d\t", fila.info[i]);
    }
    printf("\n\n");
}

//Função de Separar Par e Ímpar
int SeparaParImpar(def_fila *filatop, def_fila *par, def_fila *impar){
    /*Percorrer a fila com elementos e, ao decorrer disso, 
    ir desenfileirando, verificando e enfileirando nas outras separadamente*/
    int i, aux;
    for(i=(*filatop).inicio; i<=(*filatop).fim; i++){
        aux = 0;
        //Vai desenfileirando e jogando o elemento na aux
        Desenfileirar(&(*filatop), &aux);
        if (aux == 0) //Significa que pode ter dado erro
            return 0;

        //Pares
        if(aux % 2 == 0){
            Enfileirar(&(*par), aux);
        }
        else{ //Ímpares
            Enfileirar(&(*impar), aux);
        }
    }
    return 1;
}


int main(){

    //Declaração da Fila Principal
    def_fila filatop;
    //Declaração das Filas Par/Impar
    def_fila par, impar;
    //Declaração da Auxiliar para Valor
    int info;
    //Outras Auxiliares
    char opc;
    int cont = MAX;
    
    //Início das Filas
    filatop.inicio = filatop.fim = -1;
    par.inicio = par.fim = -1;
    impar.inicio = impar.fim = -1;

    //Manipulação da Fila Principal
    do
    {
        printf("\nFila Principal - MAX. ELEMENTO(S) RESTANTE(S): %d\n\n", cont);
        printf("Digite um elemento inteiro a ser enfileirado: ");
        scanf("%d", &info);
        printf("\n\nEnfileirando o elemento. Aguarde...\n");
        Sleep(3000);
        Enfileirar(&filatop, info);
        printf("\nElemento enfileirado com sucesso!\n\n");
        system("pause");
        system("cls");
        printf("\nDeseja enfileirar mais um elemento?(S/N)\n");
        do
        {
            opc = toupper(getch());
        } while (opc != 'S' && opc != 'N');
        cont--;
        /*}
        else{
            printf("\nErro ao enfileirar elemento.\n\n");
            system("pause");
            system("cls");
            break;
        }*/
        system("cls");
    } while (opc == 'S');

    //Mostrando a Fila Atual
    printf("\nFila Atual\n\n");
    Visualizar(filatop);
    system("pause");
    system("cls");

    printf("\nSeparando pares e impares. Aguarde...\n\n");
    Sleep(3000);
    if(SeparaParImpar(&filatop, &par, &impar)){
        printf("\nElementos separados com sucesso!\n\n");
        system("pause");
        system("cls");

        //Mostrando elementos
        printf("\nPares\n\n");
        Visualizar(par);
        printf("Impares\n\n");
        Visualizar(impar);
        system("pause");
        system("cls");
    }


    return 0;

}