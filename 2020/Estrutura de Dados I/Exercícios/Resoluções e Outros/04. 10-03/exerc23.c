/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define MAX 100 //Tamanho total de veículos permitidos por pista

/*11 pistas de arrecadação: 5 sentido Jaú-Bauru
6 sentido Bauru-Jaú; cobrado nas duas direções

TABELA DE CATEGORIAS E PREÇOS (JÁU-BAURU/BAURU-JAÚ):
Categoria     Multip.   Preço Total
Categoria 1	    1	    R$ 11,40
Categoria 2	    2	    R$ 22,80
Categoria 3	    3	    R$ 34,20
Categoria 4	    4	    R$ 45,60
Categoria 5	    5	    R$ 57,00
Categoria 6	    6	    R$ 68,40
Categoria 7	    1.5	    R$ 17,10
Categoria 8	    2	    R$ 22,80
Categoria E7	7	    R$ 79,80
Categoria E8	8	    R$ 91,20
Categoria E9	9	    R$ 102,60
Categoria E10	10	    R$ 114,00
*/
void MostraCategorias(){
    printf("\n\nCATEGORIAS\t\tPRECO TOTAL\n");
    printf("\nCategoria '1'\t\tR$ 11,40\n");
    printf("\nCategoria '2'\t\tR$ 22,80\n");
    printf("\nCategoria '3'\t\tR$ 34,20\n");
    printf("\nCategoria '4'\t\tR$ 45,60\n");
    printf("\nCategoria '5'\t\tR$ 57,00\n");
    printf("\nCategoria '6'\t\tR$ 67,40\n");
    printf("\nCategoria '7'\t\tR$ 17,10\n");
    printf("\nCategoria '8'\t\tR$ 22,80\n");
    printf("\nCategoria 'E7'\t\tR$ 79,80\n");
    printf("\nCategoria 'E8'\t\tR$ 91,20\n");
    printf("\nCategoria 'E9'\t\tR$ 102,60\n");
    printf("\nCategoria 'E10'\t\tR$ 114,00\n");
    printf("\n\n");
}
//Letra A
typedef struct{
    //Variáveis específicas dos veículos
    char categoria[MAX][4];
    //Variáveis para Fila (como um todo)
    int inicio, fim;
}fila_pedagio;

//Funções Básicas da Fila
int VerificaCheia(fila_pedagio fila){
    return(fila.fim == MAX-1);
}
int VerificaVazia(fila_pedagio fila){
    return ((fila.inicio == -1) || (fila.inicio > fila.fim));
}
int Enfileira(fila_pedagio *fila, char info[]){
    if(VerificaCheia((*fila)))
        return 0;
    
    //Incrementar o Final da Fila
    (*fila).fim++;

    //Acrescentar o Elemento a essa Posição da Fila
    strcpy((*fila).categoria[(*fila).fim], info);

    //Caso seja o primeiro elemento
    if((*fila).inicio == -1)
        (*fila).inicio = 0;
        
    return 1;
}
int Desenfileira(fila_pedagio *fila, char info[]){
    if(VerificaVazia((*fila)))
        return 0;

    //Auxiliar recebendo a informação atual
    strcpy(info, (*fila).categoria[(*fila).inicio]);

    //Aumentando o início
    (*fila).inicio++;

    return 1;
}
void VisualizaFila(fila_pedagio fila){ //Função Bônus para Auxiliar
    int i;
    for(i=fila.inicio; i<=fila.fim; i++){
        printf("%s\t", fila.categoria[i]);
    }
    printf("\n\n");
}

//Função de Verificação de Categorias Válidas
int VerificaCategoria(char categoria[]){
    return ((strcmp(categoria, "1") == 0) ||
            (strcmp(categoria, "2") == 0) ||
            (strcmp(categoria, "3") == 0) ||
            (strcmp(categoria, "4") == 0) ||
            (strcmp(categoria, "5") == 0) ||
            (strcmp(categoria, "6") == 0) ||
            (strcmp(categoria, "7") == 0) ||
            (strcmp(categoria, "8") == 0) ||
            (strcmp(categoria, "E7") == 0) ||
            (strcmp(categoria, "E8") == 0) ||
            (strcmp(categoria, "E9") == 0) ||
            (strcmp(categoria, "E10") == 0));
}
//Função de Verificação e Retornar o Valor da Categoria
float PrecoCategoria(char categoria[]){
    if ((strcmp(categoria, "1") == 0)){
        return 11.40;
    }
    else if ((strcmp(categoria, "2") == 0)){
        return 22.80;
    }
    else if ((strcmp(categoria, "3") == 0)){
        return 34.20;
    }
    else if ((strcmp(categoria, "4") == 0)){
        return 45.60;
    }
    else if ((strcmp(categoria, "5") == 0)){
        return 57.00;
    }
    else if ((strcmp(categoria, "6") == 0)){
        return 68.40;
    }
    else if ((strcmp(categoria, "7") == 0)){
        return 17.10;
    }
    else if ((strcmp(categoria, "8") == 0)){
        return 22.80;
    }
    else if ((strcmp(categoria, "E7") == 0)){
        return 79.80;
    }
    else if ((strcmp(categoria, "E8") == 0)){
        return 91.20;
    }
    else if ((strcmp(categoria, "E9") == 0)){
        return 102.60;
    }
    else if ((strcmp(categoria, "E10") == 0)){
        return 114.00;
    }
}
//LETRA B - FUNÇÃO II
void CalculaPedagioAcumulado(fila_pedagio *fila, float *cont_separado)
{
    //Auxiliar para Texto e outras
    char categoriaux[4];

    //Retirando todos as categorias e calculando
    while (Desenfileira(&(*fila), categoriaux))
    {
        (*cont_separado) += PrecoCategoria(categoriaux);
    }
    
}

int main(){
    //No exercício, usarei cada posição dos vetores abaixo para cada pista
    //Declaração da Fila: Jaú-Bauru (5 pistas)
    fila_pedagio jau_bauru[5];
    //Declaração da Fila: Bauru-Jaú (6 pistas)
    fila_pedagio bauru_jau[6];

    //Iniciando o Início/Fim de cada vetor
    int i;
    for(i=0; i<6; i++){
        if(i==5){
            bauru_jau[i].inicio = bauru_jau[i].fim = -1;
        }
        else{
            jau_bauru[i].inicio = jau_bauru[i].fim = -1;
            bauru_jau[i].inicio = bauru_jau[i].fim = -1;
        }
    }
    
    //Auxiliar para Captação da Categoria
    char categoria[4];
    //Outras Auxiliares
    int opc_pedagio[2]; char opc_remove, opc_func;


    //Acrescentando elementos as filas
    do{
        printf("\nPEDAGIO CENTROVIAS - INSERCAO\n\n");
        printf("\nSENTIDOS DAS PISTAS:\n\n");
        printf("\t1 - JAU-BAURU\n\n\t2 - BAURU-JAU\n\n");
        printf("\nDigite qual sentido deseja INSERIR veiculos (digite '0' para encerrar a operacao): ");
        scanf("%d", &opc_pedagio[0]);
        system("cls");
        if(opc_pedagio[0] == 0)
            break;
        
        //Verificando se a opção é válida e entrando em outro menu
        switch(opc_pedagio[0]){
        //1: Jau-Bauru
        case 1:
            do{
                printf("\nPEDAGIO CENTROVIAS - INSERCAO\n\n");
                printf("\nPISTAS DE 'JAU-BAURU':\n\n");
                printf("\t1 - PISTA 1\n");
                printf("\t2 - PISTA 2\n");
                printf("\t3 - PISTA 3\n");
                printf("\t4 - PISTA 4\n");
                printf("\t5 - PISTA 5\n");
                printf("\nDigite qual pista deseja INSERIR veiculos (digite '0' para voltar): ");
                scanf("%d", &opc_pedagio[1]);
                system("cls");
                if (opc_pedagio[1] == 0)
                    break;
                //Verificando se a opção é válida e entrando no menu de inserção
                switch(opc_pedagio[1]){
                //Pista 1
                case 1:
                    do{
                        printf("\nPEDAGIO CENTROVIAS - INSERCAO\n\n");
                        printf("\nPISTAS DE 'JAU-BAURU' - 'PISTA 1'\n");
                        MostraCategorias();
                        printf("Digite a categoria desejada: ");
                        do{
                            fflush(stdin);
                            scanf("%s", &categoria);
                        }while(!VerificaCategoria(categoria));
                        //Enfileirando a categoria
                        if(Enfileira(&jau_bauru[0], categoria)){
                            printf("\nCategoria enfileirada com sucesso!\n\n");
                        }
                        else{
                            printf("\nErro ao enfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja inserir outra categoria para 'PISTA 1'? (S/N)\n");
                        do{
                            opc_func = toupper(getch());
                        }while(opc_func!='S' && opc_func!='N');
                        system("cls");
                    }while(opc_func!='N');
                    break;
                //Pista 2
                case 2:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - INSERCAO\n\n");
                        printf("\nPISTAS DE 'JAU-BAURU' - 'PISTA 2'\n");
                        MostraCategorias();
                        printf("Digite a categoria desejada: ");
                        do
                        {
                            fflush(stdin);
                            scanf("%s", &categoria);
                        } while (!VerificaCategoria(categoria));
                        //Enfileirando a categoria
                        if (Enfileira(&jau_bauru[1], categoria))
                        {
                            printf("\nCategoria enfileirada com sucesso!\n\n");
                        }
                        else
                        {
                            printf("\nErro ao enfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja inserir outra categoria para 'PISTA 2'? (S/N)\n");
                        do
                        {
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 3
                case 3:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - INSERCAO\n\n");
                        printf("\nPISTAS DE 'JAU-BAURU' - 'PISTA 3'\n");
                        MostraCategorias();
                        printf("Digite a categoria desejada: ");
                        do
                        {
                            fflush(stdin);
                            scanf("%s", &categoria);
                        } while (!VerificaCategoria(categoria));
                        //Enfileirando a categoria
                        if (Enfileira(&jau_bauru[2], categoria))
                        {
                            printf("\nCategoria enfileirada com sucesso!\n\n");
                        }
                        else
                        {
                            printf("\nErro ao enfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja inserir outra categoria para 'PISTA 3'? (S/N)\n");
                        do
                        {
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 4
                case 4:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - INSERCAO\n\n");
                        printf("\nPISTAS DE 'JAU-BAURU' - 'PISTA 4'\n");
                        MostraCategorias();
                        printf("Digite a categoria desejada: ");
                        do
                        {
                            fflush(stdin);
                            scanf("%s", &categoria);
                        } while (!VerificaCategoria(categoria));
                        //Enfileirando a categoria
                        if (Enfileira(&jau_bauru[3], categoria))
                        {
                            printf("\nCategoria enfileirada com sucesso!\n\n");
                        }
                        else
                        {
                            printf("\nErro ao enfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja inserir outra categoria para 'PISTA 4'? (S/N)\n");
                        do
                        {
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 5
                case 5:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - INSERCAO\n\n");
                        printf("\nPISTAS DE 'JAU-BAURU' - 'PISTA 5'\n");
                        MostraCategorias();
                        printf("Digite a categoria desejada: ");
                        do
                        {
                            fflush(stdin);
                            scanf("%s", &categoria);
                        } while (!VerificaCategoria(categoria));
                        //Enfileirando a categoria
                        if (Enfileira(&jau_bauru[4], categoria))
                        {
                            printf("\nCategoria enfileirada com sucesso!\n\n");
                        }
                        else
                        {
                            printf("\nErro ao enfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja inserir outra categoria para 'PISTA 5'? (S/N)\n");
                        do
                        {
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                default:
                    printf("\nOpcao invalida. Tente novamente.\n\n");
                    printf("Retornando ao menu anterior...\n");
                    Sleep(3000);
                    break;
                }
                system("cls");
            }while(opc_pedagio[1]>0);
            break;
        //2: Bauru-Jau
        case 2:
            do
            {
                printf("\nPEDAGIO CENTROVIAS - INSERCAO\n\n");
                printf("\nPISTAS DE 'BAURU-JAU':\n\n");
                printf("\t1 - PISTA 1\n");
                printf("\t2 - PISTA 2\n");
                printf("\t3 - PISTA 3\n");
                printf("\t4 - PISTA 4\n");
                printf("\t5 - PISTA 5\n");
                printf("\t6 - PISTA 6\n");
                printf("\nDigite qual pista deseja INSERIR veiculos (digite '0' para voltar): ");
                scanf("%d", &opc_pedagio[1]);
                system("cls");
                if (opc_pedagio[1] == 0)
                    break;

                //Verificando se a opção é válida e entrando no menu de
                switch (opc_pedagio[1])
                {
                //Pista 1
                case 1:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - INSERCAO\n\n");
                        printf("\nPISTAS DE 'BAURU-JAU' - 'PISTA 1'\n");
                        MostraCategorias();
                        printf("Digite a categoria desejada: ");
                        do
                        {
                            fflush(stdin);
                            scanf("%s", &categoria);
                        } while (!VerificaCategoria(categoria));
                        //Enfileirando a categoria
                        if (Enfileira(&bauru_jau[0], categoria))
                        {
                            printf("\nCategoria enfileirada com sucesso!\n\n");
                        }
                        else
                        {
                            printf("\nErro ao enfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja inserir outra categoria para 'PISTA 1'? (S/N)\n");
                        do
                        {
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 2
                case 2:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - INSERCAO\n\n");
                        printf("\nPISTAS DE 'BAURU-JAU' - 'PISTA 2'\n");
                        MostraCategorias();
                        printf("Digite a categoria desejada: ");
                        do
                        {
                            fflush(stdin);
                            scanf("%s", &categoria);
                        } while (!VerificaCategoria(categoria));
                        //Enfileirando a categoria
                        if (Enfileira(&bauru_jau[1], categoria))
                        {
                            printf("\nCategoria enfileirada com sucesso!\n\n");
                        }
                        else
                        {
                            printf("\nErro ao enfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja inserir outra categoria para 'PISTA 2'? (S/N)\n");
                        do
                        {
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 3
                case 3:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - INSERCAO\n\n");
                        printf("\nPISTAS DE 'BAURU-JAU' - 'PISTA 3'\n");
                        MostraCategorias();
                        printf("Digite a categoria desejada: ");
                        do
                        {
                            fflush(stdin);
                            scanf("%s", &categoria);
                        } while (!VerificaCategoria(categoria));
                        //Enfileirando a categoria
                        if (Enfileira(&bauru_jau[2], categoria))
                        {
                            printf("\nCategoria enfileirada com sucesso!\n\n");
                        }
                        else
                        {
                            printf("\nErro ao enfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja inserir outra categoria para 'PISTA 3'? (S/N)\n");
                        do
                        {
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 4
                case 4:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - INSERCAO\n\n");
                        printf("\nPISTAS DE 'BAURU-JAU' - 'PISTA 4'\n");
                        MostraCategorias();
                        printf("Digite a categoria desejada: ");
                        do
                        {
                            fflush(stdin);
                            scanf("%s", &categoria);
                        } while (!VerificaCategoria(categoria));
                        //Enfileirando a categoria
                        if (Enfileira(&bauru_jau[3], categoria))
                        {
                            printf("\nCategoria enfileirada com sucesso!\n\n");
                        }
                        else
                        {
                            printf("\nErro ao enfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja inserir outra categoria para 'PISTA 4'? (S/N)\n");
                        do
                        {
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 5
                case 5:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - INSERCAO\n\n");
                        printf("\nPISTAS DE 'BAURU-JAU' - 'PISTA 5'\n");
                        MostraCategorias();
                        printf("Digite a categoria desejada: ");
                        do
                        {
                            fflush(stdin);
                            scanf("%s", &categoria);
                        } while (!VerificaCategoria(categoria));
                        //Enfileirando a categoria
                        if (Enfileira(&bauru_jau[4], categoria))
                        {
                            printf("\nCategoria enfileirada com sucesso!\n\n");
                        }
                        else
                        {
                            printf("\nErro ao enfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja inserir outra categoria para 'PISTA 5'? (S/N)\n");
                        do
                        {
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 6
                case 6:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - INSERCAO\n\n");
                        printf("\nPISTAS DE 'BAURU-JAU' - 'PISTA 6'\n");
                        MostraCategorias();
                        printf("Digite a categoria desejada: ");
                        do
                        {
                            fflush(stdin);
                            scanf("%s", &categoria);
                        } while (!VerificaCategoria(categoria));
                        //Enfileirando a categoria
                        if (Enfileira(&bauru_jau[5], categoria))
                        {
                            printf("\nCategoria enfileirada com sucesso!\n\n");
                        }
                        else
                        {
                            printf("\nErro ao enfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja inserir outra categoria para 'PISTA 6'? (S/N)\n");
                        do
                        {
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                default:
                    printf("\nOpcao invalida. Tente novamente.\n\n");
                    printf("Retornando ao menu anterior...\n");
                    Sleep(3000);
                    break;
                }
                system("cls");
            } while (opc_pedagio[1] > 0);
            break;
        default:
            printf("\nOpcao invalida. Tente novamente.\n\n");
            printf("Retornando ao menu anterior...\n");
            Sleep(3000);
            break;
        }
        system("cls");
    }while(opc_pedagio[0]>0);
    

    //Transição
    printf("\nEntrando na funcao de REMOVER. Aguarde...\n");
    Sleep(3000);
    system("cls");


    //Mostrando e Removendo elementos das filas (caso desejado)
    do
    {
        printf("\nPEDAGIO CENTROVIAS - REMOCAO\n\n");
        printf("\nSENTIDOS DAS PISTAS:\n\n");
        printf("\t1 - JAU-BAURU\n\n\t2 - BAURU-JAU\n\n");
        printf("\nDigite qual sentido deseja REMOVER veiculos (digite '0' para encerrar a operacao): ");
        scanf("%d", &opc_pedagio[0]);
        system("cls");
        if (opc_pedagio[0] == 0)
            break;

        //Verificando se a opção é válida e entrando em outro menu
        switch (opc_pedagio[0])
        {
        //1: Jau-Bauru
        case 1:
            do
            {
                printf("\nPEDAGIO CENTROVIAS - REMOCAO\n\n");
                printf("\nPISTAS DE 'JAU-BAURU':\n\n");
                printf("\t1 - PISTA 1\n");
                printf("\t2 - PISTA 2\n");
                printf("\t3 - PISTA 3\n");
                printf("\t4 - PISTA 4\n");
                printf("\t5 - PISTA 5\n");
                printf("\nDigite qual pista deseja REMOVER veiculos (digite '0' para voltar): ");
                scanf("%d", &opc_pedagio[1]);
                system("cls");
                if (opc_pedagio[1] == 0)
                    break;

                //Verificando se a opção é válida e entrando no menu de inserção
                switch (opc_pedagio[1])
                {
                //Pista 1
                case 1:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - REMOCAO\n\n");
                        printf("\nPISTAS DE 'JAU-BAURU' - 'PISTA 1' ATUAL\n\n");
                        VisualizaFila(jau_bauru[0]);
                        printf("Deseja realmente REMOVER o primeiro elemento?(S/N)\n");
                        do
                        {
                            opc_remove = toupper(getch());
                        } while (opc_remove!='S' && opc_remove!='N');
                        //Desenfileirando a categoria e printando resultado na tela
                        if (Desenfileira(&jau_bauru[0], categoria))
                        {
                            printf("\nCategoria desenfileirada com sucesso!\n\n");
                            system("pause");
                            system("cls");

                            //LETRA B: MOSTRANDO VEÍCULO REMOVIDO E VALOR ASSOCIADO
                            printf("\nCategoria REMOVIDA: %s\n", categoria);
                            printf("\nValor Pago Pelo Motorista: R$ %.2f\n\n\n", PrecoCategoria(categoria));
                        }
                        else
                        {
                            printf("\nErro ao desenfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja REMOVER outra categoria da 'PISTA 1'? (S/N)\n");
                        do
                        {
                            fflush(stdin);
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 2
                case 2:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - REMOCAO\n\n");
                        printf("\nPISTAS DE 'JAU-BAURU' - 'PISTA 2' ATUAL\n\n");
                        VisualizaFila(jau_bauru[1]);
                        printf("Deseja realmente REMOVER o primeiro elemento?(S/N)\n");
                        do
                        {
                            opc_remove = toupper(getch());
                        } while (opc_remove != 'S' && opc_remove != 'N');
                        //Desenfileirando a categoria e printando resultado na tela
                        if (Desenfileira(&jau_bauru[1], categoria))
                        {
                            printf("\nCategoria desenfileirada com sucesso!\n\n");
                            system("pause");
                            system("cls");

                            //LETRA B: MOSTRANDO VEÍCULO REMOVIDO E VALOR ASSOCIADO
                            printf("\nCategoria REMOVIDA: %s\n", categoria);
                            printf("\nValor Pago Pelo Motorista: R$ %.2f\n\n\n", PrecoCategoria(categoria));
                        }
                        else
                        {
                            printf("\nErro ao desenfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja REMOVER outra categoria da 'PISTA 2'? (S/N)\n");
                        do
                        {
                            fflush(stdin);
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 3
                case 3:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - REMOCAO\n\n");
                        printf("\nPISTAS DE 'JAU-BAURU' - 'PISTA 3' ATUAL\n\n");
                        VisualizaFila(jau_bauru[2]);
                        printf("Deseja realmente REMOVER o primeiro elemento?(S/N)\n");
                        do
                        {
                            opc_remove = toupper(getch());
                        } while (opc_remove != 'S' && opc_remove != 'N');
                        //Desenfileirando a categoria e printando resultado na tela
                        if (Desenfileira(&jau_bauru[2], categoria))
                        {
                            printf("\nCategoria desenfileirada com sucesso!\n\n");
                            system("pause");
                            system("cls");

                            //LETRA B: MOSTRANDO VEÍCULO REMOVIDO E VALOR ASSOCIADO
                            printf("\nCategoria REMOVIDA: %s\n", categoria);
                            printf("\nValor Pago Pelo Motorista: R$ %.2f\n\n\n", PrecoCategoria(categoria));
                        }
                        else
                        {
                            printf("\nErro ao desenfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja REMOVER outra categoria da 'PISTA 3'? (S/N)\n");
                        do
                        {
                            fflush(stdin);
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 4
                case 4:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - REMOCAO\n\n");
                        printf("\nPISTAS DE 'JAU-BAURU' - 'PISTA 4' ATUAL\n\n");
                        VisualizaFila(jau_bauru[3]);
                        printf("Deseja realmente REMOVER o primeiro elemento?(S/N)\n");
                        do
                        {
                            opc_remove = toupper(getch());
                        } while (opc_remove != 'S' && opc_remove != 'N');
                        //Desenfileirando a categoria e printando resultado na tela
                        if (Desenfileira(&jau_bauru[3], categoria))
                        {
                            printf("\nCategoria desenfileirada com sucesso!\n\n");
                            system("pause");
                            system("cls");

                            //LETRA B: MOSTRANDO VEÍCULO REMOVIDO E VALOR ASSOCIADO
                            printf("\nCategoria REMOVIDA: %s\n", categoria);
                            printf("\nValor Pago Pelo Motorista: R$ %.2f\n\n\n", PrecoCategoria(categoria));
                        }
                        else
                        {
                            printf("\nErro ao desenfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja REMOVER outra categoria da 'PISTA 4'? (S/N)\n");
                        do
                        {
                            fflush(stdin);
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 5
                case 5:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - REMOCAO\n\n");
                        printf("\nPISTAS DE 'JAU-BAURU' - 'PISTA 5' ATUAL\n\n");
                        VisualizaFila(jau_bauru[4]);
                        printf("Deseja realmente REMOVER o primeiro elemento?(S/N)\n");
                        do
                        {
                            opc_remove = toupper(getch());
                        } while (opc_remove != 'S' && opc_remove != 'N');
                        //Desenfileirando a categoria e printando resultado na tela
                        if (Desenfileira(&jau_bauru[4], categoria))
                        {
                            printf("\nCategoria desenfileirada com sucesso!\n\n");
                            system("pause");
                            system("cls");

                            //LETRA B: MOSTRANDO VEÍCULO REMOVIDO E VALOR ASSOCIADO
                            printf("\nCategoria REMOVIDA: %s\n", categoria);
                            printf("\nValor Pago Pelo Motorista: R$ %.2f\n\n\n", PrecoCategoria(categoria));
                        }
                        else
                        {
                            printf("\nErro ao desenfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja REMOVER outra categoria da 'PISTA 5'? (S/N)\n");
                        do
                        {
                            fflush(stdin);
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                default:
                    printf("\nOpcao invalida. Tente novamente.\n\n");
                    printf("Retornando ao menu anterior...\n");
                    Sleep(3000);
                    break;
                }
                system("cls");
            } while (opc_pedagio[1] > 0);
            break;
        //2: Bauru-Jau
        case 2:
            do
            {
                printf("\nPEDAGIO CENTROVIAS\n\n");
                printf("\nPISTAS DE 'BAURU-JAU':\n\n");
                printf("\t1 - PISTA 1\n");
                printf("\t2 - PISTA 2\n");
                printf("\t3 - PISTA 3\n");
                printf("\t4 - PISTA 4\n");
                printf("\t5 - PISTA 5\n");
                printf("\t6 - PISTA 6\n");
                printf("\nDigite qual pista deseja inserir veiculos (digite '0' para voltar): ");
                scanf("%d", &opc_pedagio[1]);
                system("cls");
                if (opc_pedagio[1] == 0)
                    break;

                //Verificando se a opção é válida e entrando no menu de
                switch (opc_pedagio[1])
                {
                //Pista 1
                case 1:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - REMOCAO\n\n");
                        printf("\nPISTAS DE 'BAURU-JAU' - 'PISTA 1' ATUAL\n\n");
                        VisualizaFila(bauru_jau[0]);
                        printf("Deseja realmente REMOVER o primeiro elemento?(S/N)\n");
                        do
                        {
                            opc_remove = toupper(getch());
                        } while (opc_remove!='S' && opc_remove!='N');
                        //Desenfileirando a categoria e printando resultado na tela
                        if (Desenfileira(&bauru_jau[0], categoria))
                        {
                            printf("\nCategoria desenfileirada com sucesso!\n\n");
                            system("pause");
                            system("cls");

                            //LETRA B: MOSTRANDO VEÍCULO REMOVIDO E VALOR ASSOCIADO
                            printf("\nCategoria REMOVIDA: %s\n", categoria);
                            printf("\nValor Pago Pelo Motorista: R$ %.2f\n\n\n", PrecoCategoria(categoria));
                        }
                        else
                        {
                            printf("\nErro ao desenfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja REMOVER outra categoria da 'PISTA 1'? (S/N)\n");
                        do
                        {
                            fflush(stdin);
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 2
                case 2:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - REMOCAO\n\n");
                        printf("\nPISTAS DE 'BAURU-JAU' - 'PISTA 2' ATUAL\n\n");
                        VisualizaFila(bauru_jau[1]);
                        printf("Deseja realmente REMOVER o primeiro elemento?(S/N)\n");
                        do
                        {
                            opc_remove = toupper(getch());
                        } while (opc_remove != 'S' && opc_remove != 'N');
                        //Desenfileirando a categoria e printando resultado na tela
                        if (Desenfileira(&bauru_jau[1], categoria))
                        {
                            printf("\nCategoria desenfileirada com sucesso!\n\n");
                            system("pause");
                            system("cls");

                            //LETRA B: MOSTRANDO VEÍCULO REMOVIDO E VALOR ASSOCIADO
                            printf("\nCategoria REMOVIDA: %s\n", categoria);
                            printf("\nValor Pago Pelo Motorista: R$ %.2f\n\n\n", PrecoCategoria(categoria));
                        }
                        else
                        {
                            printf("\nErro ao desenfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja REMOVER outra categoria da 'PISTA 2'? (S/N)\n");
                        do
                        {
                            fflush(stdin);
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 3
                case 3:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - REMOCAO\n\n");
                        printf("\nPISTAS DE 'BAURU-JAU' - 'PISTA 3' ATUAL\n\n");
                        VisualizaFila(bauru_jau[2]);
                        printf("Deseja realmente REMOVER o primeiro elemento?(S/N)\n");
                        do
                        {
                            opc_remove = toupper(getch());
                        } while (opc_remove != 'S' && opc_remove != 'N');
                        //Desenfileirando a categoria e printando resultado na tela
                        if (Desenfileira(&bauru_jau[2], categoria))
                        {
                            printf("\nCategoria desenfileirada com sucesso!\n\n");
                            system("pause");
                            system("cls");

                            //LETRA B: MOSTRANDO VEÍCULO REMOVIDO E VALOR ASSOCIADO
                            printf("\nCategoria REMOVIDA: %s\n", categoria);
                            printf("\nValor Pago Pelo Motorista: R$ %.2f\n\n\n", PrecoCategoria(categoria));
                        }
                        else
                        {
                            printf("\nErro ao desenfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja REMOVER outra categoria da 'PISTA 3'? (S/N)\n");
                        do
                        {
                            fflush(stdin);
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 4
                case 4:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - REMOCAO\n\n");
                        printf("\nPISTAS DE 'BAURU-JAU' - 'PISTA 4' ATUAL\n\n");
                        VisualizaFila(bauru_jau[3]);
                        printf("Deseja realmente REMOVER o primeiro elemento?(S/N)\n");
                        do
                        {
                            opc_remove = toupper(getch());
                        } while (opc_remove != 'S' && opc_remove != 'N');
                        //Desenfileirando a categoria e printando resultado na tela
                        if (Desenfileira(&bauru_jau[3], categoria))
                        {
                            printf("\nCategoria desenfileirada com sucesso!\n\n");
                            system("pause");
                            system("cls");

                            //LETRA B: MOSTRANDO VEÍCULO REMOVIDO E VALOR ASSOCIADO
                            printf("\nCategoria REMOVIDA: %s\n", categoria);
                            printf("\nValor Pago Pelo Motorista: R$ %.2f\n\n\n", PrecoCategoria(categoria));
                        }
                        else
                        {
                            printf("\nErro ao desenfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja REMOVER outra categoria da 'PISTA 4'? (S/N)\n");
                        do
                        {
                            fflush(stdin);
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 5
                case 5:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - REMOCAO\n\n");
                        printf("\nPISTAS DE 'BAURU-JAU' - 'PISTA 5' ATUAL\n\n");
                        VisualizaFila(bauru_jau[4]);
                        printf("Deseja realmente REMOVER o primeiro elemento?(S/N)\n");
                        do
                        {
                            opc_remove = toupper(getch());
                        } while (opc_remove != 'S' && opc_remove != 'N');
                        //Desenfileirando a categoria e printando resultado na tela
                        if (Desenfileira(&bauru_jau[4], categoria))
                        {
                            printf("\nCategoria desenfileirada com sucesso!\n\n");
                            system("pause");
                            system("cls");

                            //LETRA B: MOSTRANDO VEÍCULO REMOVIDO E VALOR ASSOCIADO
                            printf("\nCategoria REMOVIDA: %s\n", categoria);
                            printf("\nValor Pago Pelo Motorista: R$ %.2f\n\n\n", PrecoCategoria(categoria));
                        }
                        else
                        {
                            printf("\nErro ao desenfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja REMOVER outra categoria da 'PISTA 5'? (S/N)\n");
                        do
                        {
                            fflush(stdin);
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                //Pista 5
                case 6:
                    do
                    {
                        printf("\nPEDAGIO CENTROVIAS - REMOCAO\n\n");
                        printf("\nPISTAS DE 'BAURU-JAU' - 'PISTA 6' ATUAL\n\n");
                        VisualizaFila(bauru_jau[5]);
                        printf("Deseja realmente REMOVER o primeiro elemento?(S/N)\n");
                        do
                        {
                            opc_remove = toupper(getch());
                        } while (opc_remove != 'S' && opc_remove != 'N');
                        //Desenfileirando a categoria e printando resultado na tela
                        if (Desenfileira(&bauru_jau[5], categoria))
                        {
                            printf("\nCategoria desenfileirada com sucesso!\n\n");
                            system("pause");
                            system("cls");

                            //LETRA B: MOSTRANDO VEÍCULO REMOVIDO E VALOR ASSOCIADO
                            printf("\nCategoria REMOVIDA: %s\n", categoria);
                            printf("\nValor Pago Pelo Motorista: R$ %.2f\n\n\n", PrecoCategoria(categoria));
                        }
                        else
                        {
                            printf("\nErro ao desenfileirar categoria. Tente novamente.\n\n");
                            system("pause");
                            break;
                        }
                        system("pause");
                        system("cls");
                        printf("\nDeseja REMOVER outra categoria da 'PISTA 6'? (S/N)\n");
                        do
                        {
                            fflush(stdin);
                            opc_func = toupper(getch());
                        } while (opc_func != 'S' && opc_func != 'N');
                        system("cls");
                    } while (opc_func != 'N');
                    break;
                default:
                    printf("\nOpcao invalida. Tente novamente.\n\n");
                    printf("Retornando ao menu anterior...\n");
                    Sleep(3000);
                    break;
                }
                system("cls");
            } while (opc_pedagio[1] > 0);
            break;
        default:
            printf("\nOpcao invalida. Tente novamente.\n\n");
            printf("Retornando ao menu anterior...\n");
            Sleep(3000);
            break;
        }
        system("cls");
    } while (opc_pedagio[0] > 0);

    //Transição II
    printf("\nCalculando pedagio acumulado. Aguarde...\n");
    Sleep(3000);
    system("cls");


    //Função Final - Pedágio Acumulado
    printf("\nPEDAGIO CENTROVIAS - TOTAL\n\n");
    //Contador de Pedágios Separados e do Acumulado
    float cont_separado = 0.0, cont_total = 0.0;
    //Jaú-Bauru
    printf("\nPISTAS DE 'JAU-BAURU'\n\n");
    for (i = 0; i < 5; i++)
    {
        CalculaPedagioAcumulado(&jau_bauru[i], &cont_separado);
        cont_total += cont_separado;
        printf("\nPista %d: R$ %.2f\n", i + 1, cont_separado);
        cont_separado = 0.0;
    }
    //Bauru-Jaú
    printf("\n\nPISTAS DE 'BAURU-JAU'\n\n");
    for (i = 0; i < 6; i++)
    {
        CalculaPedagioAcumulado(&bauru_jau[i], &cont_separado);
        cont_total += cont_separado;
        printf("\nPista %d: R$ %.2f\n", i + 1, cont_separado);
        cont_separado = 0.0;
    }
    printf("\n\nTotal Acumulado: R$ %.2f\n\n", cont_total);

    return 0;

}