/*Criado por Davi Augusto - BCC - UNESP Bauru*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>

//Fila - Estática
#define MAX 100
typedef struct
{
    int idade[MAX];
    int inicio, fim;
} def_fila;

//Enfileirar
void Enfileirar(def_fila *fila, int info)
{
    if (VerificaCheia((*fila).fim))
        return;

    (*fila).fim++;
    (*fila).idade[(*fila).fim] = info;
    if ((*fila).inicio == -1)
        (*fila).inicio++;
}
//Desenfileirar
int Desenfileirar(def_fila *fila, int *info)
{
    if (VerificaVazia((*fila).inicio, (*fila).fim))
        return 0;
    (*info) = (*fila).idade[(*fila).inicio];
    (*fila).inicio++;
    return 1;
}
//VerificaVazia
int VerificaVazia(int inicio, int fim)
{
    return ((inicio == -1) || (inicio > fim));
}
//VerificaCheia
int VerificaCheia(int fim)
{
    return (fim == MAX - 1);
}

int main()
{

    //Declaração das Filas
    def_fila normal, preferencial;
    //Iniciando as Filas
    normal.inicio = normal.fim = -1;
    preferencial.inicio = preferencial.fim = -1;
    //Auxiliares
    int idade, cont[4];
    cont[0] = cont[1] = 0;
    cont[3] = 5; //Qtd mínima de atendimentos

    //Iniciando Menu
    do
    {
        printf("\nFILAVI DE ATENDIMENTO\n\n");
        if (cont[3] > 0)
            printf("CONTAGEM ATE SEPARACAO DE FILAS (MINIMO ATENDIMENTO): %d\n\n", cont[3]);
        printf("\tQUANTIDADE NA FILA NORMAL: %d\n\n", cont[0]);
        printf("\tQUANTIDADE NA FILA PREFERENCIAL (> 60 ANOS): %d\n\n", cont[1]);
        printf("Digite a idade para inserir na fila (0 para sair): ");
        do
        {
            scanf("%d", &idade);
        } while (idade < 0);
        system("cls");
        if (idade > 0)
        {
            if (idade <= 60)
            { //Acrescentar na Fila normal
                printf("\nAcrescentando pessoa na FILA NORMAL. Aguarde...\n\n");
                //Sleep(3000);
                Enfileirar(&normal, idade);
                printf("Enfileirado com sucesso!\n\n");
                cont[0]++;
            }
            else
            {
                printf("\nAcrescentando pessoa na FILA PREFERENCIAL. Aguarde...\n\n");
                //Sleep(3000);
                Enfileirar(&preferencial, idade);
                printf("Enfileirado com sucesso!\n\n");
                cont[1]++;
            }
            cont[3]--;
            system("pause");
            system("cls");
        }
    } while (idade != 0 || cont[3] > 0);

    //Realizando operações do caixa
    cont[2] = 1; //contador de processos de atendimento
    int i;
    while (!VerificaVazia(normal.inicio, normal.fim) || !VerificaVazia(preferencial.inicio, preferencial.fim))
    {
        printf("\nFILAVI DE ATENDIMENTO\n\n");
        printf("ATENDIMENTO %d\n\n\n", cont[2]++);
        printf("FILA NORMAL:\n\n");
        if (VerificaVazia(preferencial.inicio, preferencial.fim))
        {
            //Se acabou o preferencial, 5 caixas para o normal
            //Atendimento Normal: 5 caixas
            for (i = 1; i <= 5; i++)
            {
                if (Desenfileirar(&normal, &idade))
                    printf("%d ", idade);
            }
            printf("\n\n");
        }
        else
        {
            //Atendimento Normal: 3 caixas
            for (i = 1; i <= 3; i++)
            {
                if (Desenfileirar(&normal, &idade))
                    printf("%d ", idade);
            }
            printf("\n\n");
            printf("FILA PREFERENCIAL:\n\n");
            //Atendimento Preferencial: 2 caixas
            for (i = 1; i <= 2; i++)
            {
                if (Desenfileirar(&preferencial, &idade))
                    printf("%d ", idade);
            }
            printf("\n\n");
        }
        system("pause");
        system("cls");
    }

    return 0;
}