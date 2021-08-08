/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define MAX 100
#define MAX_BUFFER_SIZE 128

//Declaração da Pilha LLSE
typedef struct no *def_pilha;
struct no{
    char info;
    def_pilha prox;
};
//Empilhar
int Empilhar(def_pilha *pilha, char *info){
    //Alocando elemento
    def_pilha q = (def_pilha)malloc(sizeof(struct no));
    q->info = info;
    q->prox = NULL;

    //Um+ elementos
    q->prox = (*pilha);
    (*pilha) = q;    
}
//Desempilhar
void Desempilhar(def_pilha *pilha, char *info){
    if(VerificaVazia((*pilha)))
        return;
    
    def_pilha q = (*pilha);
    (*info) = q->info;
    //Eliminando primeiro elemento de uma LLSE
    (*pilha) = (*pilha)->prox;
    free(q);
    //return 1;
}
//VerificaVazia
int VerificaVazia(def_pilha pilha){
    return (pilha == NULL);
}
//VerificaNúmeroVálido
int NumeroValido(char info){
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

//Função Principal: Calcular
int Kalcus(def_pilha *pilha, char expressao[], int *resultado){
    /*Primeiramente, percorrer a expressão e
    ir empilhando. (vou aderir: E = 'E')
    Após isso, ao encontrar um operador, ir desempilhando
    cada caractere em uma string até encontrar um 'E' e
    converter essa string para um número inteiro.
    Realizar o processo para duas auxiliares, e colocar a resposta
    em uma terceira, que será convertida em char novamente e empilhada
    Realizar o processo até pilha ficar nula de novo
    */
    
    //Percorrendo a expressão
    fflush(stdin);
    int i, j, num1 = -1, num2 = -1, total = 0;
    char info, aux[MAX];
    for(i=0; i<strlen(expressao); i++){
        if ((expressao[i] == 'E') || (NumeroValido(expressao[i])))
        { //E = empilhar 'E' ou elementos
            Empilhar(&(*pilha), expressao[i]);
        }
        /*else if(expressao[i] >= '0' && expressao <= '9'){ //Empilhar elemento
            Empilhar(&(*pilha), expressao[i]);
        }*/
        else if(expressao[i] == 'C'){ //Clear = limpar tudo e encerrar processo
            while(VerificaVazia((*pilha)) == 0){
                Desempilhar(&(*pilha), &info);
            }
            return 0;
        }
        else{ 
            //Encontrou sinal, então realizar operações
            //1°: Desempilhar elementos até encontrar 'E' e colocar numa string auxiliar
            //2°: Inverter essa string e colocar o valor inteiro numa auxiliar. Repetir para a outra
            //3°: Após encontrar o resultado, converter o valor para a string auxiliar e empilhar
            aux[0] = '\0';
            //Número 1
            while(num1 == -1){
                Desempilhar(&(*pilha), &info);
                if(info == 'E'){
                    strrev(aux);
                    num1 = atoi(aux);
                }
                else{
                    strncat(aux, &info, 1);
                }
            }
            aux[0] = '\0';
            //Número 2
            while (num2 == -1){
                Desempilhar(&(*pilha), &info);
                if (info == 'E')
                {
                    strrev(aux);
                    num2 = atoi(aux);
                }
                else
                {
                    strncat(aux, &info, 1);
                }
            }
            //Empilhando um 'E' que foi retirado
            Empilhar(&(*pilha), 'E');
            
            //Realizar a operação necessária
            if (expressao[i] == '+')
                total = (int)num2 + num1;
            else if (expressao[i] == '-')
                total = (int)num2 - num1;
            else if (expressao[i] == '*')
                total = (int)num2 * num1;
            else if (expressao[i] == '/')
                total = (int)(num2 / num1);

            //Convertendo o total para string, invertendo e empilhando de volta
            aux[0] = '\0';
            snprintf(&aux, MAX_BUFFER_SIZE, "%d", total);
            //itoa(total, &aux, MAX_BUFFER_SIZE);
            //strrev(aux);
            for(j = 0; j < strlen(aux); j++){
                Empilhar(&(*pilha), aux[j]);
            }
            //printf("%d\n", total);
            total = 0;
            num1 = -1;
            num2 = -1;
        }
        
    }

    //Final do processo: Desempilhar resultado, converter e colocar na variável resultado
    aux[0] = '\0';
    while((*pilha)->info != 'E'){
        Desempilhar(&(*pilha), &info);
        strncat(aux, &info, 1);
    }
    if(strlen(aux) > 1)
        strrev(aux);
    
    (*resultado) = atoi(aux);

    return 1;
}

int main(){

    //Início das Pilhas
    def_pilha calculadora = NULL; 
    //Auxiliares
    char expressao[MAX], opc;
    int resultado = 0;

    //Realizando operações
    do{
        fflush(stdin);
        printf("\nCALCULADORAVI\n\n");
        printf("CARACTERES PERMITIDOS:\n\n");
        printf("\t0 1 2 3 4 5 6 7 8 9 + - * / C E\n\n");
        printf("\tC - CLEAR\n\tE - ENTER\n\n");
        printf("NOTACAO PERMITIDA: POLONESA REVERSA\n\n");
        printf("Digite a expressao desejada: ");
        gets(expressao);
        system("cls");
        printf("\nRealizando calculos. Aguarde...\n\n");
        //Sleep(3000);
        if(Kalcus(&calculadora, expressao, &resultado)){
            printf("Calculo realizado com sucesso!\n\n");
            system("pause");
            system("cls");
            printf("\nCALCULADORAVI\n\n");
            printf("RESULTADO FINAL DA EXPRESSAO: %d\n\n", resultado);    
            free(calculadora);
            calculadora = NULL;
        }
        else{
            printf("Expressao apagada durante o processo\n\n");
        }
        system("pause");
        system("cls");
        printf("\nDeseja realizar outra operacao? (S/N)\n");
        do{
            opc = toupper(getch());
        }while(opc != 'S' && opc != 'N');
        system("cls");
    }while(opc != 'N');
    
    
    return 0;

}