/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define MAX 100
#define ESC 27

//Declaração da Estrutura da Pilha Dinâmica
typedef struct reg_pilha *def_pilha;
struct reg_pilha{
    char info;
    def_pilha prox;
};

//Função de Verificação de Pilha Nula
int VerificaVazia(def_pilha pilha){
    return (pilha == NULL);
}
//Função de Verificação de Letras
int VerificaLetras(char *letra){
    if(toupper(letra) >= 'A' && toupper(letra) <= 'C')
        return 1;
    return 0;
}
//Função de Inserção na Pilha (Empilha)
void Empilhar(def_pilha *pilha, char info){
    //Inserir no Início (Lista)
    def_pilha p;
    CriarNo(&p, info);
    p->prox = (*pilha);
    (*pilha) = p;
}
void CriarNo(def_pilha *p, char info){
    def_pilha q = (def_pilha)malloc(sizeof(struct reg_pilha));
    q->info = info;
    q->prox = NULL;
    (*p) = q;
}
//Função de Remover da Pilha (Desempilha)
int Desempilhar(def_pilha *pilha, char *info){
    if(VerificaVazia((*pilha)))
        return 0;

    def_pilha p = (*pilha);
    (*info) = p->info;
    (*pilha) = (*pilha)->prox;
    free(p);
    return 1;
}
//Função de Imprimir a Pilha
void Imprime(def_pilha pilha){
    while(pilha){
        printf("%c\n", pilha->info);
        pilha = pilha->prox;
    }
    printf("\n\n");
}
//Função de Verificação do "Palíndromo" (É Case-Sensitive, ou seja, Maisculas != Minusculas)
int VerificaPalindromo(def_pilha *pilha){
    //Pilha Auxiliar para Verificação
    def_pilha aux_pilha = NULL;
    //Char auxiliar
    char aux_carac;

    //Início das Operações
    //Vai desempilhando a pilha de caracteres até encontrar o caractere 'C'.
        //Empilha os elementos em uma auxiliar (para verificação)
    do{
        if(Desempilhar(&(*pilha), &aux_carac)){
            if(toupper(aux_carac) == 'C')
                break;
            Empilhar(&aux_pilha, aux_carac);
        }
        else{
            return 0;
        }
    }while(toupper(aux_carac) != 'C');

    //Evitando caracteres do tipo: C<y>
    if(VerificaVazia((*pilha)) || VerificaVazia(aux_pilha))
        return 0;

    //Verificando char a char das pilhas
    while (!VerificaVazia((*pilha)) && !VerificaVazia(aux_pilha)){

        if((*pilha)->info != (aux_pilha->info)){
            return 0;
        }
        else{ //Caso uma das duas fiquem vazias antes do processo acabar, então não é palindromo
            if(Desempilhar(&(*pilha), &aux_carac) == 0 ||
            Desempilhar(&aux_pilha, &aux_carac) == 0){
                return 0;
            }
        }
    }

    return 1;
}
//Destruir a Pilha (Final Palindromo)
void DestroiPilha(def_pilha *pilha){
    def_pilha p = (*pilha);
    while(p){
        p = p->prox;
        free((*pilha));
        (*pilha) = p;
    }
    free(p); free(*pilha);
    (*pilha) = NULL;

}

int main(){

    //Declaração da pilha dinâmica
    def_pilha pilha = NULL;

    //Auxiliar para manipulação das opções
    char opc_menu, opc_func;
    int i;
    //Auxiliar para pegar a cadeira de caracteres e outra para informação do desempilha
    char caracteres[MAX], aux;

    while (opc_menu != ESC)
    {
        printf("\nPilha - Palindromo\n\n");
        printf("1 - Empilhar Caracteres\n");
        printf("2 - Desempilhar Caracteres\n");
        printf("3 - Visualizar a Pilha\n");
        printf("4 - Verificacao de Palindromo\n");
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
                printf("\nEmpilhamento de Caracteres\n\n");
                printf("Digite a cadeira de caracteres do tipo '<x>C<y>' (MAX. 100)\n");
                printf("OBS: Apenas 'A', 'B' e 'C' sao validos. O resto sera desconsiderado.\n");
                printf("ATENCAO: Digitar apenas UMA VEZ o caracter 'C'.\n\n");
                printf("Caracteres: ");
                //scanf("%s", &caracteres);
                gets(caracteres);
                printf("\n\nEmpilhando. Aguarde...\n\n");
                Sleep(3000);
                for(i = 0; i<strlen(caracteres); i++){
                    if(VerificaLetras(caracteres[i]))
                        Empilhar(&pilha, caracteres[i]);
                }
                printf("\nCaracteres empilhados com sucesso!\n\n");
                system("pause");
                system("cls");
            
                printf("\nDeseja empilhar mais caracteres?(S/N)\n");
                do
                {
                    opc_func = toupper(getch());
                } while (opc_func != 'S' && opc_func != 'N');
                system("cls");
                fflush(stdin);
            } while (opc_func == 'S');
            break;
        case '2':
            do
            {
                printf("\nDesempilhamento de Caracteres\n\n");
                printf("\nDeseja realmente desempilhar o ultimo caractere? (S/N)\n");
                do
                {
                    opc_func = toupper(getch());
                } while (opc_func != 'S' && opc_func != 'N');
                if (opc_func == 'S')
                {
                    printf("\n\nDesempilhando. Aguarde...\n\n");
                    Sleep(3000);
                    if (Desempilhar(&pilha, &aux))
                    {
                        printf("\nCaractere '%c' desempilhado com sucesso!\n\n", aux);
                        system("pause");
                        system("cls");
                    }
                    else
                    {
                        printf("\nErro ao desempilhar caractere. Tente novamente.\n\n");
                        system("pause");
                        break;
                    }
                }
                system("cls");
            } while (opc_func == 'S');
            break;
        case '3':
            if(VerificaVazia(pilha)){
                printf("\nPilha vazia. Acrescente uma cadeira de caracteres na funcao '1' do menu.\n\n");
            }
            else{
                printf("\nPilha Atual\n\n");
                Imprime(pilha);
            }
            system("pause");
            break;
        case '4':
            printf("\nVerificacao de Palindromo\n\n");
            printf("Deseja realmente verificar se a pilha eh um palindromo?\n");
            printf("OBS: Todos os dados da pilha serao DESTRUIDOS apos a verificacao\n\n");
            printf("Sua opcao (S/N): ");
            do{
                opc_func = toupper(getch());
            }while(opc_func != 'S' && opc_func != 'N');
            if(opc_func == 'S'){
                printf("\n\n\nVerificando se eh palindromo. Aguarde...\n");
                Sleep(3000);
                system("cls");
                if (VerificaVazia(pilha))
                {
                    printf("\nPilha vazia. Acrescente uma cadeia de caracteres na funcao '1' do menu.\n\n");
                    system("pause");
                }
                else
                {
                    if (VerificaPalindromo(&pilha))
                    {
                        printf("\nA cadeira de caracteres eh um palindromo!\n\n");
                    }
                    else
                    {
                        printf("\nA cadeia de caracteres NAO eh um palindromo.\n\n");
                    }
                    DestroiPilha(&pilha);
                    system("pause");
                }
            }
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