#include <stdio.h>

#define MAX 100

void LerVetor(int *vet, int *n){

    printf("Digite a quantidade de elementos inteiros: ");
    scanf("%d", &(*n));

    printf("\nAgora, digite os valores do vetor: ");
    int i;
    for(i=0; i<(*n); i++)
        scanf("%d", &vet[i]);
}
void MostraVetor(int vet[], int n){
    printf("\n");
    int i;
    for(i=0; i<n; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
}

//Letra A
void SeparaParImpar(int vet[], int *pares, int *impares, int n);
//Letra B
void SubstituiNegativo(int vet[], int *negsubs, int n);
//Letra C
int SomaVetorRecursivo(int vet[], int n);
//Letra D
int VetorFatorialRecursivo(int num);

int main(){

    int vet[MAX], n;

    //Letra A
    printf("LETRA A:\n");
    LerVetor(&vet, &n);
    system("cls");

    int pares[MAX], impares[MAX];
    SeparaParImpar(vet, &pares, &impares, n);
    printf("\n");
    system("pause");

    //Letra B
    system("cls");
    printf("LETRA B:\n");
    LerVetor(&vet, &n);
    system("cls");

    int negsubs[MAX];
    SubstituiNegativo(vet, &negsubs, n);
    printf("\n");
    system("pause");

    //Letra C
    system("cls");
    printf("LETRA C:\n");
    LerVetor(&vet, &n);
    system("cls");
    printf("Vetor Final:");
    MostraVetor(vet, n);

    printf("\nSomatorio (V. Recursiva): %d\n", SomaVetorRecursivo(vet, n-1));
    printf("\n");
    system("pause");

    //Letra D
    system("cls");
    printf("LETRA D:\n");
    LerVetor(&vet, &n);
    system("cls");

    int fatorial[MAX], i;
    for(i=0; i<n; i++){
        fatorial[i] = VetorFatorialRecursivo(vet[i]);
    }
    printf("Vetor Fatorial:");
    MostraVetor(fatorial, n);
    printf("\n");

    return 0;
}

//Letra A
void SeparaParImpar(int vet[], int *pares, int *impares, int n){

    int i, auxpar = 0, auximpar = 0;
    for(i=0; i<n; i++){

        //Pares
        if(vet[i] % 2 == 0){
            pares[auxpar] = vet[i];
            auxpar++;
        } //Impares
        else{
            impares[auximpar] = vet[i];
            auximpar++;
        }
    }
    printf("Pares");
    MostraVetor(pares, auxpar);
    printf("\nImpares");
    MostraVetor(impares, auximpar);
}

//Letra B
void SubstituiNegativo(int vet[], int *negsubs, int n){

    int i;
    for(i=0; i<n; i++){
        negsubs[i] = vet[i];
        if(vet[i] < 0)
            negsubs[i] = 0;
    }

    printf("Vetor Final");
    MostraVetor(negsubs, n);
}

//Letra C
int SomaVetorRecursivo(int vet[], int n){

    if(n == 0)
        return vet[n];
    return vet[n] + SomaVetorRecursivo(vet, n-1);
}

//Letra D
int VetorFatorialRecursivo(int num){
    if(num == 0)
        return 1;

    return num*VetorFatorialRecursivo(num-1);
}
