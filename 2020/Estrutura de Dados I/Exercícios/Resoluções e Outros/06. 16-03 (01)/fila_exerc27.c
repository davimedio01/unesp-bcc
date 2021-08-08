/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define MAX 100
#define MAX_BUFFER_SIZE 128

//Declaração da Fila LCSE
typedef struct no *def_fila;
struct no{
    //Informação
    int info;
    def_fila prox;  
};
//Enfileirar
void Enfileirar(def_fila *fila, int info){
    //Auxiliar contendo informação
    def_fila q = (def_fila)malloc(sizeof(struct no));
    q->info = info;
    //strcpy(q->info, info);
    //Primeiro elemento
    if(VerificaVazia((*fila)))
        (*fila) = q;
    else
        q->prox = (*fila)->prox;
    (*fila)->prox = q; //Circular
    (*fila) = q;       //Inserção no Final
}
//Desenfileirar
int Desenfileirar(def_fila *fila, int *info){
    if(VerificaVazia((*fila)))
        return 0;
    
    def_fila q = (*fila)->prox;
    //strcpy(info, q->info);
    (*info) = q->info;
    //Um elemento
    if(q == (*fila))
        (*fila) = NULL;
    else //Mais de um elemento
        (*fila)->prox = q->prox;
    free(q);
    return 1;
}
//Verifica Vazia
int VerificaVazia(def_fila fila){
    return (fila == NULL);
}

//FAZER AQUI
int PegaDigito(int valor){ 
    
}

int main(){

    //Declaração do Vetor de Fila LCSE
    def_fila fila[MAX];
    //Iniciando a fila como nulo
    int i;
    for(i=0; i<MAX; i++){
        fila[i] = NULL;
    }
        
    //Vetor auxiliar (guardar elementos)
        //Informação: Binária, Octal, Decimal, Hexadecimal
    //char vet_info[MAX][MAX];
    int vet_info[MAX];
    char opc;
    //Base e Tamanho Dígitos
    int base, tam_digitos = 0, aux = 0;

    //Solicitando a Base e o tamanho máximo de Digitos
    printf("\nORDENACAO POR DISTRIBUICAO\n\n");
    printf("Digite a base desejada (B>1): ");
    do{
        scanf("%d", &base);
    }while(base <= 1);
    system("cls");
    //Inserindo elementos no vetor
    int indice=0; //Tamanho vetor
    do{
        fflush(stdin);
        printf("\nORDENACAO POR DISTRIBUICAO (BASE 10)\n\n");
        printf("BASE DESEJADA: %d\n\n", base);
        printf("Digite o elemento na base: ");
        do{
            scanf("%d", &vet_info[indice]);
        }while(vet_info[indice] <= 0);
        /*do{
            gets(vet_info[indice]);
        }while(strlen(vet_info[indice]) == 0);
        if (tam_digitos < (int)strlen(vet_info[indice]))
            tam_digitos = (int)strlen(vet_info[indice]);*/
        if(aux < vet_info[indice])
            aux = vet_info[indice];
        indice++;
        printf("\n\nElemento inserido com sucesso!\n\n");
        system("pause");
        system("cls");
        printf("\nDeseja inserir outro elemento?(S/N)\n");
        do{
            opc = toupper(getch());
        }while(opc!='S' && opc!='N');
        system("cls");
    }while(opc != 'N');
    
    //Mostrando o Vetor Atual
    printf("\nORDENACAO POR DISTRIBUICAO\n\n");
    printf("CONJUNTO ATUAL:\n\n");
    for (i = 0; i < indice; i++)
    {
        printf("%d ",vet_info[i]);
    }
    printf("\n\n");
    system("pause");
    system("cls");

    //Recuperando tamanho dígito máximo
    while(aux != 0){
        aux /= 10;
        tam_digitos++;
    }

    //Ordenando...
    /*Passos da Ordenação (D iterações): 
    1° - Enfileirar em cada posição do vetor (valor da unidade)
    2° - Desenfileirar cada posição e enfileirar na unidade da dezena/centena...
    3° - Concatenar e mostrar todas as linhas em ordem

    Ou seja: i = D-1; i>=0; i-- (analisar cada posição de unid/dezena/cent... 
                                e enfileirar na posição do vetor de fila correspondente)
    */
    printf("\nOrdenando a(s) fila(s). Aguarde (bastante)...\n\n");
    int j, temp;//, op = 1;
    int info;
    //Realizando D iterações
    for(i=tam_digitos-1; i>=0; i--){
        //Se for a primeira iteração
        if(i == tam_digitos-1){
            //Enfileirar elementos do vetor nas posições respectivas da fila (unidade)
            for(j=0; j<indice; j++){
                //Posição do Vetor de Fila
                temp = 1; //PEGAR DÍGITO AQUI
                printf("%d\n", vet_info[j]);
                printf("%d\n", temp);
                Enfileirar(&(fila[temp]), vet_info[j]);
                printf("%d\n", fila[temp]->info);
                system("pause");
            }
            temp = 0;
        }
        else{ //Segunda+ iterações
            for(j=0; j<base; j++){
                //Desenfileirar cada posição e Enfileirar na correta (dezena/centen..)
                while(Desenfileirar(&(fila[j]), &info)){
                    printf("%d\n", info);
                    temp = 1; //PEGAR DÍGITO AQUI
                    printf("%d\n", temp);
                    Enfileirar(&(fila[temp]), info);
                    printf("%d\n", fila[temp]->info);
                    system("pause");
                }
                temp = 0;
            }
        }
    } 
    //Sleep(3000);
    printf("Fila(s) ordenada(s) com sucesso!\n\n");
    system("pause");
    system("cls");

    //Mostrando as Filas (concatenando)
    printf("\nORDENACAO POR DISTRIBUICAO\n\n");
    printf("CONJUNTO ORDENADO:\n\n");
    for(j = 0; j < base; j++){
        while(Desenfileirar(&(fila[j]), &info)){
            printf("%d ", info);
        }
    }
    printf("\n\n");
    system("pause");
    system("cls");
    
    return 0;

}