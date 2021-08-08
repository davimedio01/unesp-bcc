/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define MAX 100
//Letra A
typedef struct{
    int topo;
    int info[MAX];
}def_pilha;
//Letra B
void Empilhar(def_pilha *pilha, int info){
    if(VerificaCheia((*pilha).topo))
        return;
    //Se não estiver cheia, incrementar o topo e acrescentar elemento
    (*pilha).topo++;
    (*pilha).info[(*pilha).topo] = info;
    //return 1;
}
//Letra C
int Desempilhar(def_pilha *pilha, int *info){
    if(VerificaVazia((*pilha).topo))
        return 0;
    //Se não estiver vazia, retirar elemento e decrementar o topo
    (*info) = (*pilha).info[(*pilha).topo];
    (*pilha).topo--;
    return 1;
}
//Letra D
void Visualizar(def_pilha *pilha){
    if(VerificaVazia(pilha->topo)){
        printf("\nVagao Vazio.\n\n");
        return;
    }
    int i, aux;
    for(i=pilha->topo; i>=0; i--){
        //printf("%d\n",pilha.info[i]);
        if(Desempilhar(&(*pilha), &aux))
            VerificaVagao(aux);
    }
    printf("\n");
}
//Auxiliares
int VerificaCheia(int topo)
{
    return (topo == MAX - 1);
}
int VerificaVazia(int topo)
{
    return (topo == -1);
}

//Letra E - Principal
void Locomotiva(def_pilha *pilha){
    //Sempre: VP - R - VP - VP... VC - VC...

    //Auxiliares para Vagoes
    def_pilha vp, vc, r;
    vp.topo = vc.topo = r.topo = -1;
    //Auxiliar de Info
    int info;

    //Desempilhar a Pilha Principal
    while(Desempilhar(&(*pilha), &info)){
        if(info == 1){ //VC
            Empilhar(&vc, info);
        }
        else if(info == 2){ //VP
            Empilhar(&vp, info);
        }
        else if(info == 3){ //R
            Empilhar(&r, info);
        }
    }

    //Empilhando na ordem correta
    //1°: VC
    while(Desempilhar(&vc, &info)){
        Empilhar(&(*pilha), info);
    }
    //2°: VP (Deixando uma posição)
    while (vp.topo != 0 && Desempilhar(&vp, &info)){
        Empilhar(&(*pilha), info);
    }
    //3°: R (Uma Unidade)
    if(Desempilhar(&r, &info)){
        Empilhar(&(*pilha), info);
    }
    //4°: VP (Ultima Unidade)
    if(Desempilhar(&vp, &info)){
        Empilhar(&(*pilha), info);
    }
}
//Auxiliar - Letra E
void VerificaVagao(int info){
    if(info == 1){
        printf("VC\n");
    }
    else if(info == 2){
        printf("VP\n");
    }
    else if(info == 3){
        printf("R\n");
    }
}

int main(){

    //Letra A = definindo a pilha e o topo
    def_pilha pilha;
    pilha.topo = -1;

    //Auxiliares
    int info, cont_rest = 1;

    do{
        printf("\nLOCOMOTIVAVI\n\n");
        printf("VAGOES DISPONIVEIS:\n\n");
        printf("\t'1' - VAGOES DE CARGA (VC)\n\n");
        printf("\t'2' - VAGOES DE PASSAGEIROS (VP)\n\n");
        printf("\t'3' - VAGAO DE RESTAURANTE (R)\n\n");
        printf("OBS: APENAS UM VAGAO RESTAURANTE DISPONIVEL\n\n");
        printf("Digite a opcao para empilhar (0 para sair): ");
        do{
            scanf("%d", &info);
        }while(info < 0 || info > 3);
        system("cls");
        //Analisando as opcoes
        switch(info){
            case 1:
                printf("\nEmpilhando o 'VC' na locomotiva. Aguarde...\n\n");
                Sleep(3000);
                Empilhar(&pilha, info);
                printf("'VC' empilhado com sucesso!\n\n");
                /*}
                else{
                    printf("Erro ao empilhar 'VC'. Tente novamente.\n\n");
                }*/
                system("pause");
                break;
            case 2:
                printf("\nEmpilhando o 'VP' na locomotiva. Aguarde...\n\n");
                Sleep(3000);
                Empilhar(&pilha, info);
                printf("'VP' empilhado com sucesso!\n\n");
                /*}
                else
                {
                    printf("Erro ao empilhar 'VP'. Tente novamente.\n\n");
                }*/
                system("pause");
                break;
            case 3:
                if(cont_rest){

                    printf("\nEmpilhando o 'R' na locomotiva. Aguarde...\n\n");
                    Sleep(3000);
                    Empilhar(&pilha, info);
                    printf("'R' empilhado com sucesso!\n\n");
                    /*}
                    else
                    {
                        printf("Erro ao empilhar 'R'. Tente novamente.\n\n");
                    }*/
                    cont_rest--;
                }
                else{
                    printf("\nLimite de 'R' atingido.\n\n");
                }
                system("pause");
                break;
        }
        system("cls");
    }while(info != 0 || cont_rest != 0);
    
    //Mostrando o Vagão Atual (Sem Desempilhar)
    printf("\nLOCOMOTIVAVI\n\n");
    printf("VAGAO ATUAL:\n\n");
    int i;
    for(i=pilha.topo; i>=0; i--){
        VerificaVagao(pilha.info[i]);
    }
    printf("\n");
    system("pause");
    system("cls");

    //Realizando a função principal da locomotiva
    printf("\nRealizando operacoes. Aguarde...\n\n");
    Sleep(3000);
    Locomotiva(&pilha);
    printf("Operacoes realizadas com sucesso!\n\n");
    system("pause");
    system("cls");

    //Mostrando o Vagão Atual (Desempilhando)
    printf("\nLOCOMOTIVAVI\n\n");
    printf("VAGAO FINAL:\n\n");
    Visualizar(&pilha);
    printf("\n");
    system("pause");
    system("cls");

    return 0;

}