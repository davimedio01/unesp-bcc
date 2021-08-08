/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define MAX 100

//Pilha - LSSE
typedef struct no *def_pilha;
struct no{
    char info;
    def_pilha prox;
};
//Empilhar
void Empillhar(def_pilha *pilha, char *info){
    def_pilha q = (def_pilha)malloc(sizeof(struct no));
    q->info = info;
    q->prox = (*pilha);
    (*pilha) = q;
}
//Desempilhar
int Desempilhar(def_pilha *pilha, char *info){
    if(VerificaVazia((*pilha)))
        return 0;
    
    def_pilha q = (*pilha);
    info = q->info;
    (*pilha) = (*pilha)->prox;
    free(q);
    return 1;
}
//VerificaVazia
int VerificaVazia(def_pilha pilha){
    return (pilha == NULL);
}

//Calcula: Pré-Fixa
int KalcPreFixa(def_pilha *pilha, char expressao[], int *resultado)
{
    /*
        Pré-Fixa: Sinais vem antes dos números.
    */
}
//Calcula: Infixa
int KalcInFixa(def_pilha *pilha, char expressao[], int *resultado)
{
    /*
        In-Fixa: Usual no Ocidente

        Passos para Cálculo:
        1°) Pegar os caracteres de um número e jogar em uma auxiliar
        2°) Verificar o Sinal e armazenar em uma auxiliar para conferência
        3°) Pegar os caracteres do outro número e jogar em uma auxiliar
        4°) Realizar a operação e salvar em uma auxiliar
        5°) Repetir os processos acima até o fim da expressão
        *6°) Caso haja parênteses, realizar a operação primeiro
    */
}
//Calcula: Pré-Fixa/Pos-Fixa
int KalcPosFixa(def_pilha *pilha, char expressao[], int *resultado)
{
    /*
        Pós-Fixa: Sinais vem depois dos números
    */
}

//Auxiliares
int VerificaNumero(char info){
    return ((info == '0') ||
            (info == '1') ||
            (info == '2') ||
            (info == '3') ||
            (info == '4') ||
            (info == '5') ||
            (info == '6') ||
            (info == '7') ||
            (info == '8') ||
            (info == '9'));
}

int main(){

    //Início das Pilhas
    def_pilha calculadora = NULL;
    //Auxiliares
    char expressao[MAX], opc;
    int forma, resultado = 0;

    //Realizando operações
    do
    {
        fflush(stdin);
        printf("\nCALCULADORAVI\n\n");
        printf("FORMAS PERMITIDAS:\n\n");
        printf("\t1 - PRE-FIXA\n\n");
        printf("\t2 - INFIXA\n\n");
        printf("\t3 - POS-FIXA\n\n");
        printf("Digite a forma desejada: ");
        do{
            scanf("%d", &forma);
        }while(forma < 1 || forma > 3);
        system("cls");
        fflush(stdin);
        //Verificando opção
        switch(forma){
            //Pré-Fixo
            case 1:
                printf("\nCALCULADORAVI\n\n");
                printf("FORMA DESEJADA: PRE-FIXA\n\n");
                printf("Digite a expressao desejada (com espacos): ");
                do{
                    gets(expressao);
                }while(strlen(expressao) == 0);
                system("cls");
                //Calculando Expressão...
                printf("\nCalculando expressao. Aguarde...\n\n");
                if (KalcPreFixa(&calculadora, expressao, &resultado)){
                    printf("Calculo realizado com sucesso!\n\n");
                    system("pause");
                    system("cls");
                    printf("\nCALCULADORAVI\n\n");
                    printf("RESULTADO FINAL DA EXPRESSAO: %d\n\n", resultado);
                }
                else{
                    printf("\nErro ao calcular expressao. Tente novamente.\n\n");
                }
                break;
            //Infixo
            case 2:
                printf("\nCALCULADORAVI\n\n");
                printf("FORMA DESEJADA: INFIXA\n\n");
                printf("Digite a expressao desejada (com espacos): ");
                do
                {
                    gets(expressao);
                } while (strlen(expressao) == 0);
                system("cls");
                //Calculando Expressão...
                printf("\nCalculando expressao. Aguarde...\n\n");
                if (KalcInFixa(&calculadora, expressao, &resultado))
                {
                    printf("Calculo realizado com sucesso!\n\n");
                    system("pause");
                    system("cls");
                    printf("\nCALCULADORAVI\n\n");
                    printf("RESULTADO FINAL DA EXPRESSAO: %d\n\n", resultado);
                }
                else
                {
                    printf("\nErro ao calcular expressao. Tente novamente.\n\n");
                }
                break;
            //Pós-Fixo
            case 3:
                printf("\nCALCULADORAVI\n\n");
                printf("FORMA DESEJADA: POS-FIXA\n\n");
                printf("Digite a expressao desejada (com espacos): ");
                do
                {
                    gets(expressao);
                } while (strlen(expressao) == 0);
                system("cls");
                //Calculando Expressão...
                printf("\nCalculando expressao. Aguarde...\n\n");
                if (KalcPosFixa(&calculadora, expressao, &resultado))
                {
                    printf("Calculo realizado com sucesso!\n\n");
                    system("pause");
                    system("cls");
                    printf("\nCALCULADORAVI\n\n");
                    printf("RESULTADO FINAL DA EXPRESSAO: %d\n\n", resultado);
                }
                else
                {
                    printf("\nErro ao calcular expressao. Tente novamente.\n\n");
                }
                break;
        }
        system("pause");
        system("cls");
        printf("\nDeseja realizar outra operacao? (S/N)\n");
        do
        {
            opc = toupper(getch());
        } while (opc != 'S' && opc != 'N');
        system("cls");
    } while (opc != 'N');

    return 0;

}