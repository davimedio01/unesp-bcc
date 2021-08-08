#include <stdio.h>

typedef struct llse *no;
struct llse{
    int info;
    no prox;
};

void InsereFinal (no *lista, int info){

    no p = (no)malloc(sizeof(struct llse));
    p->info = info;
    p->prox = NULL;

    if(!(*lista)){
        (*lista) = p;
    }
    else{
        no q = (*lista);
        while(q->prox)
            q = q->prox;
        q->prox = p;
    }
}
void MostraLista(no lista){
    if(!lista){
        printf("\nNao ha elementos na lista.\n");
        return;
    }

    printf("Elementos da Lista\n");
    no p = lista;
    while(p){
        printf("%d ", p->info);
        p = p->prox;
    }
    printf("\n\n");
}

//Letra A
int ContaElementos(no lista);
//Letra B
int SomaElementos(no lista);
//Letra C
int RemoveNEsimo(no *lista, int nesimo, int qtdelemento);
//Letra D
void TrocaOcorrencia(no *lista, int info, int info_trocado, int *contqt);
//Letra E
void CopiaLista(no lista, no *listacopia, int nesimo_inicio, int K);
//Letra F
int TrocaOcorrenciaSoma(no *lista, int info, int info_soma);

int main(){

    no lista = NULL;
    char opcao;
    int info;

    do{
        scanf("%d", &info);
        InsereFinal(&lista, info);
        do{
            printf("Deseja inserir outro elemento? (S/N)");
            opcao = toupper(getch());
        }while(opcao!='S' && opcao!='N');
        printf("\n");
    }while(opcao == 'S');
    system("cls");
    MostraLista(lista);

    //Letra A
    int qtdelemento = ContaElementos(lista);
    printf("LETRA A:\n");
    printf("Quantidade de Elemento(s) da Lista: %d elemento(s)\n", qtdelemento);

    //Letra B
    printf("\nLETRA B:\n");
    printf("Soma dos Elemento(s) da Lista: %d\n", SomaElementos(lista));
    printf("\n");
    system("pause");

    //Letra C
    int nesimo;
    system("cls");
    printf("LETRA C:\n");
    printf("\nDigite o n-esimo elemento a ser removido da lista: ");
    scanf("%d", &nesimo);
    if(RemoveNEsimo(&lista, nesimo, qtdelemento)){
        printf("\nElemento removido com sucesso!\n\n");
    }
    else{
        printf("\nErro ao remover elemento. Tente novamente.\n\n");
    }
    system("pause");
    system("cls");
    MostraLista(lista);
    printf("\n");
    system("pause");

    //Letra D
    int info_troca, contqt = 0;
    system("cls");
    printf("LETRA D:\n");
    printf("\nDigite o numero da lista a ser trocado: ");
    scanf("%d", &info);
    printf("\n\nAgora, digite o numero desejado para realizar a troca: ");
    scanf("%d", &info_troca);
    system("cls");
    
    TrocaOcorrencia(&lista, info, info_troca, &contqt);
    MostraLista(lista);
    printf("Elemento com suas ocorrencias trocadas com sucesso!\n");
    printf("Numero de trocas realizadas: %d\n", contqt);
   
    printf("\n");
    system("pause");

    //Letra E
    no listacopia = NULL;
    int nesimo_inicio, K;
    system("cls");
    printf("LETRA E:\n");
    printf("\nDigite o n-esimo elemento (inicio) para copia: ");
    scanf("%d", &nesimo_inicio);
    printf("\nAgora, digite o outro nesimo termo (final) para a copia: ");
    scanf("%d", &K);
    system("cls");

    CopiaLista(lista, &listacopia, nesimo_inicio, K);
    printf("Lista Copia:\n\n");
    MostraLista(listacopia);

    printf("\n");
    system("pause");

    //Letra F
    system("cls");
    printf("LETRA F:\n");
    printf("\nDigite o numero da lista para somar com outro: ");
    scanf("%d", &info);
    printf("\n\nAgora, digite o numero desejado para realizar a soma: ");
    scanf("%d", &info_troca);
    system("cls");
    if (TrocaOcorrenciaSoma(&lista, info, info_troca)){
        MostraLista(lista);
        printf("\nElemento com suas ocorrencias trocadas e somadas com sucesso!");
    }
    else{
        printf("\nErro ao trocar e somar elemento(s). Tente novamente.\n");
    }
    printf("\n");

    return 0;
}

//Letra A
int ContaElementos(no lista){
    if(!lista)
        return 0;
    
    if(!(lista->prox)){
        return 1;
    }
    return 1 + ContaElementos(lista->prox);
}

//Letra B
int SomaElementos(no lista){
    if(!lista)
        return 0;
    
    if(!(lista->prox)){
        return lista->info;
    }
    return lista->info + SomaElementos(lista->prox);
}

//Letra C
int RemoveNEsimo(no *lista, int nesimo, int qtdelemento)
{
    if(!(*lista) || (qtdelemento < nesimo) || nesimo <= 0)
        return 0;

    //Nesimo == 1
    if(nesimo == 1){
        no p = (*lista);
        (*lista) = (*lista)->prox;
        free(p);
    }
    else{
        no p = (*lista), q;
        int cont = 1; //Pelo menos dois elementos
        while(p->prox && cont != nesimo){
            q = p;
            p = p->prox;
            cont++;
        }
        q->prox = p->prox;
        free(p);
    }
    return 1; 
}

//Letra D
void TrocaOcorrencia(no *lista, int info, int info_trocado, int *contqt){
    
    if((*lista)){
        if ((*lista)->info == info){
            (*lista)->info = info_trocado;
            (*contqt)++;
        }
        TrocaOcorrencia(&(*lista)->prox, info, info_trocado, &(*contqt));
    }
    
}

//Letra E
void CopiaLista(no lista, no *listacopia, int nesimo_inicio, int K){
    if(lista && K > 0){
        if(nesimo_inicio <= 1){
            InsereFinal(&(*listacopia), lista->info);
        }
        CopiaLista(lista->prox, &(*listacopia), nesimo_inicio-1, K-1);
    }
    
}


//Letra F
int TrocaOcorrenciaSoma(no *lista, int info, int info_soma){
    if(!(*lista))
        return 0;

    no p = (*lista);
    int verifica = 0;
    do{
        if(p->info == info){
            p->info += info_soma;
            verifica = 1;
        }
        p = p->prox;
    }while(p);
    return verifica;
}