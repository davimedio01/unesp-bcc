/*Criado por Davi Augusto - BCC - UNESP Bauru*/

//Exercício: verificar se os escopos de uma expressão matemática estão corretos
    //Empilhar: escopos de abertura {[(
    //Desempilhar (e Verificar): escopos de fechamento )]}

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define MAX 100

//Utilização e Declaração da Pilha (Dinâmica)
typedef struct no_pilha *def_pilha;
struct no_pilha{
    char escopo;
    struct no_pilha *prox;
};
//Iniciação da Pilha
void criaPilha(def_pilha *pilha){
    (*pilha) = NULL;
}

int VerificaSimbolos(char escopo)
{
    if ((escopo == '(') || (escopo == '[') || (escopo == '{'))
        return 1;
    else if ((escopo == ')') || (escopo == ']') || (escopo == '}'))
        return 0;
    return -1;
}

//Função principal de verificação dos Escopos
int VerificaEscopo(char *aux){

   //Declaração da pilha dinâmica para análise dos escopos 
   def_pilha pilha;
   //Iniciação da Pilha Dinâmica
   criaPilha(&pilha);

   //Análise dos Escopos
    //A cada escopo de abertura: empilhar
    //A cada escopo de fechamento: desempilhar (e verificar)
   int i;
   for(i = 0; i<strlen(aux); i++){
       //Verificando os simbolos digitados
       //Símbolos de Abertura (Empilhar)
       if(VerificaSimbolos(aux[i]) == 1){
           Empilhar(&pilha, aux[i]);
       }
       else if (VerificaSimbolos(aux[i]) == 0){ //Símbolos de Fechamento (Fechar)
            if(Desempilhar(&pilha, aux[i]) == 0){
                return 0;
            }
       }
   }

   //Verificação se a Pilha não estiver vazia após as operações acima
   if(VerificaVazia(pilha)){
       return 1;
   }

    return 0;
}

int VerificaVazia(def_pilha pilha){
    if(pilha == NULL)
        return 1;
    return 0;
}
void Empilhar(def_pilha *pilha, char info){
    //Inserir no Início (Lista)
    def_pilha q;
    CriarNo(&q, info);
    q->prox = (*pilha);
    (*pilha) = q;
}
int Desempilhar(def_pilha *pilha, char *info){
    if(VerificaVazia((*pilha)))
        return 0;
    
    def_pilha q;
    q = (*pilha);
    //Verificando se o escopo está correto
    if((q->escopo == '(' && info == ')') || 
    (q->escopo == '[' && info == ']') || 
    (q->escopo == '{' && info == '}')){
        //info = q->escopo;
        (*pilha) = (*pilha)->prox;
        free(q);
        return 1;
    }
    return 0;
}
void CriarNo(def_pilha *pilha, char info){
    def_pilha q = (def_pilha)malloc(sizeof(struct no_pilha));
    q->escopo = info;
    q->prox = NULL;
    (*pilha) = q;
}

int main(){

    //Declaração do Char Auxiliar para Salvar os Escopos
    char aux[MAX];
    printf("\nDigite a Expressao Matematica (MAX. 100): ");
    do{
        scanf("%s", &aux);
        //gets(aux);
    }while(strlen(aux) == 0);
    
    printf("\n\nVerificando... Por favor, aguarde.");
    Sleep(3000);
    system("cls");

    //Função para Verificar se os Escopos estão corretos.
    if(VerificaEscopo(&aux)){
        printf("\n\nEscopos posicionados corretamente!\n\n");
    }
    else{
        printf("\n\nEscopos posicionados incorretamente.\n\n");
    }


    return 0;

}