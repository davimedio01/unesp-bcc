/*Trabalho de Sistemas Lineares
Métodos Numéricos Computacionais (MNC)

Integrantes                RA
Davi Augusto Neves Leite   191027383
Giovani Candido            191021601
Luis Henrique Morelli      181027097
Luiz Fernando Sementille   191021032*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX 10


// =================== Funções Auxiliares =================== //
void readVector(int order, double vector[MAX]){
    int i;
    
    for(i = 0; i < order; i++){   
        scanf("%lf", &vector[i]);
    }
}

void printVector(int order, double solution[MAX]){
    int i;

    for(i = 0; i < order; i++){
        printf("%.4lf ", solution[i]);
    }

    printf("\n");
}

void readMatrix(int order, double matrix[MAX][MAX]){
    int i, j;

    printf("Elementos da matriz:\n");
    
    for(i = 0; i < order; i++){   
        for(j = 0; j < order; j++){
            scanf("%lf", &matrix[i][j]);
        }
    }
}

void printMatrix(int order, double matrix[MAX][MAX]){
    int i, j;

    for(i = 0; i < order; i++){
        for(j = 0; j < order; j++){
            printf("%.4lf ", matrix[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

void copyMatrix(int order, double A[MAX][MAX], double aux[MAX][MAX]){
    int i, j;

    for (i = 0; i < order; i++){
        for (j = 0; j < order; j++){
            aux[i][j] = A[i][j];
        }
    }
}

void swap(double *x, double *y){
    double temp = *x;

    *x = *y;
    *y = temp;
}

void swapRow(int order, double rowX[MAX], double rowY[MAX]){   
    int i;

    for(i = 0; i < order; i++){        
        swap(&rowX[i], &rowY[i]);   
    }
}
// =================== Fim Funções Auxiliares =================== //


// =================== Determinante =================== //
double determinant(int order, double matrix[MAX][MAX]){
    //Matriz Auxiliar
    double submatrix[MAX][MAX];
    double det = 0.;

    if(order == 1){
        return (matrix[0][0]);
    }
    
    if(order == 2){
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    }
    
    int i, j, k;
    int subRow, subCol;
    
    for(i = 0; i < order; i++){
        subRow = 0;

        for(j = 1; j < order; j++){
            subCol = 0;
        
            for(k = 0; k < order; k++){
                if(i == k){
                    continue;
                }
                
                submatrix[subRow][subCol++] = matrix[j][k];
            }

            subRow++;
        }

        //Uso do cofator
        det += (pow(-1, i) * matrix[0][i] * determinant(order - 1, submatrix));
    }
    
    return det;
}
// =================== Fim Determinante =================== //


// =================== Sistema Triangular Inferior =================== //
int isLowerTriangularMatrix(int order, double matrix[MAX][MAX]){
    int i, j;

    for(i = 0; i < order; i++){
        for(j = 0; j < order; j++){
            if(j > i){
                if(matrix[i][j] != 0){
                    return 0;
                }
            }
        }
    }

    return 1;
}

int solveLowerTriangularSystem(int order, double A[MAX][MAX], double b[MAX], double solution[MAX]){
    if(!isLowerTriangularMatrix(order, A)){
        return 0;
    }

    int i, j;
    double sum;

    for(i = 0; i < order; i++){
        sum = 0;
		
        for(j = 0; j < i; j++){
            sum += A[i][j]*solution[j];
        }
		
    	solution[i] = (b[i]-sum)/A[i][i];
	}

    return 1;
}
// =================== Fim Sistema Triangular Inferior =================== //


// =================== Sistema Triangular Superior =================== //
int isUpperTriangularMatrix(int order, double matrix[MAX][MAX]){
    int i, j;

    for(i = 0; i < order; i++){
        for(j = 0; j < order; j++){
            if(j < i){
                if(matrix[i][j] != 0){
                    return 0;
                }
            }
        }
    }

    return 1;
}

int solveUpperTriangularSystem(int order, double A[MAX][MAX], double b[MAX], double solution[MAX]){
    if(!isUpperTriangularMatrix(order, A)){
        return 0;
    }
    
    int i, j;
    double sum;

    for(i = order-1; i >= 0; i--){
        sum = 0;
		
 		for(j = i+1; j < order; j++){
            sum += A[i][j]*solution[j];
        }
		
	    solution[i] = (b[i]-sum)/A[i][i];	
    }
    
    return 1;
}
// =================== Fim Sistema Triangular Superior =================== //


// =================== Eliminação de Gauss =================== //
int gaussianElimination(int order, double A[MAX][MAX], double b[MAX], double solution[MAX]){
    if(fabs(determinant(order, A)) <= 10e-7){
        return 0;
    }

    int i, k, j, pivotRow;
    double multiplier;

    for(i = 0; i < order; i++){
        pivotRow = i;

        for(k = i+1; k < order && A[pivotRow][i] == 0; k++){
            if(A[k][i] != 0){
                pivotRow = k;
            }
        }

        if(pivotRow != i){
            swapRow(order, &A[i][i], &A[pivotRow][i]);
            swap(&b[i], &b[pivotRow]);
        }
        else if(A[pivotRow][i] == 0){
            return 0;
        }

        for(k = i+1; k < order; k++){
            multiplier = -A[k][i]/A[i][i];

            for(j = i; j < order; j++){
                A[k][j] += multiplier*A[i][j];
            }

            b[k] += multiplier*b[i];
        }
    }

    return solveUpperTriangularSystem(order, A, b, solution);
}
// =================== Fim Eliminação de Gauss =================== //


// =================== Gauss com Pivoteamento Parcial =================== //
int gaussianEliminationPartialPivoting(int order, double A[MAX][MAX], double b[MAX], double solution[MAX]){
    
    if(fabs(determinant(order, A)) <= 10e-7){
        return 0;
    }

    int i, k, j, maxPivotRow;
    double multiplier;

    for(i = 0; i < order; i++){
        maxPivotRow = i;

        for(k = i+1; k < order; k++){   
            if(fabs(A[k][i]) > fabs(A[maxPivotRow][i])){
                maxPivotRow = k;
            }
        }

        if(A[maxPivotRow][i] == 0){  
            return 0;
        }

        if(maxPivotRow != i){
            swapRow(order, &A[i][i], &A[maxPivotRow][i]);
            swap(&b[i], &b[maxPivotRow]);
        }

        for(k = i+1; k < order; k++){
            multiplier = -A[k][i]/A[i][i];

            for(j = i; j < order; j++){
                A[k][j] += multiplier*A[i][j];
            }

            b[k] += multiplier*b[i];
        }
    }

    return solveUpperTriangularSystem(order, A, b, solution);
}
// =================== Fim Gauss com Pivoteamento Parcial =================== //


// =================== Matriz Inversa =================== //
int inverseMatrix(int order, double A[MAX][MAX], double inverse[MAX][MAX]){
    //Não existe se det == 0
    if(fabs(determinant(order, A)) <= 10e-7){
        return 0;
    }
    
    int i, j, k;
    double I[MAX][MAX], b[MAX], aux[MAX][MAX];
    
    for(i = 0; i < order; i++){
        for(j = 0; j < order; j++){
            if(i == j){
                I[i][j] = 1;
            }
            else{
                I[i][j] = 0;
            }
        }
    }

    for(i = 0; i < order; i++){

        double solution[MAX];

        for(j = 0; j < order; j++){
            b[j] = I[i][j]; //Linhas da matriz identidade
        }

        copyMatrix(order, A, aux);

        //Método de Gauss
        gaussianElimination(order, aux, b, solution);
        
        for(j = 0; j < order; j++){
            inverse[j][i] = solution[j]; //Transpõe as linhas
        }
    }
}
// =================== Fim Matriz Inversa =================== //


// =================== Decomposição LU =================== //
int luDecomposition(int order, double A[MAX][MAX], double b[MAX], double solution[MAX]){
    int i;
    
    for(i = 1; i <= order; i++){
        if(fabs(determinant(i, A)) <= 10e-7){
            return 0;
        }
    }

    int j, k;
    double L[MAX][MAX], U[MAX][MAX];

    for(i = 0; i < order; i++){
        for(j = 0; j < order; j++){
            L[i][j] = 0;
            U[i][j] = 0;
        }
    }

    for(i = 0; i < order; i++){
        for(j = 0; j < order; j++){    
            if(i <= j){
                U[i][j] = A[i][j];

                for(k = 0; k < i; k++){
                    U[i][j] -= L[i][k] * U[k][j];
                }
            }
            else{
                L[i][j] = A[i][j];

                for(k = 0; k < j && i > j; k++){
                    L[i][j] -= L[i][k] * U[k][j];
                }

                L[i][j] /= U[j][j];
            } 
        }

        L[i][i] = 1;   
    }

    double y[MAX];

    solveLowerTriangularSystem(order, L, b, y);

    return solveUpperTriangularSystem(order, U, y, solution);
}
// =================== Fim Decomposição LU =================== //


// =================== Cholesky =================== //
int isSimetric(double A[MAX][MAX], int order){
    int i, j;

    for(i = 0; i < order; i++){
        for(j = 0; j < order; j++){
            if(A[i][j] != A[j][i]){
                return 0;
            }
        }
    }

    return 1;
}

int isPositiveDefined(double A[MAX][MAX], int order){
    int i, j, cont;
    double aux[MAX][MAX];
        
    cont = 1;

    while(cont <= order){
        //Submatrizes para saber se é definida positiva.
        for(i = 0; i < cont; i++){
            for(j = 0; j < cont; j++){
                aux[i][j] = A[i][j];
            }
        }

        if(fabs(determinant(cont, aux)) <= 10e-7){
            return 0;
        }

        cont++;
    }
    
    return 1;
}

int cholesky(int order, double A[MAX][MAX], double b[MAX], double solution[MAX]){
    if(!isSimetric(A, order) || !isPositiveDefined(A, order)){
        return 0;
    }

    int i, j, k;
    double g[MAX][MAX], gT[MAX][MAX], result;

    for(i = 0; i < order; i++){
        for(j = 0; j < order; j++){
            g[i][j] = 0;
        }
    }

    for(i = 0; i < order; i++){
        for(j = 0; j < order; j++){

            result = A[i][j];

            //Tratamento de elementos diagonais
            if(i == j){
                
                if(i != 0){
                    for(k = 0; k < i; k++){
                        result -= pow(g[i][k], 2);
                    }
                }
                
                g[i][j] = sqrt(result);
            }
            else{
                //Tratamento de elementos não diagonais
                //Se for a primeira coluna e não for a primeira linha
                if(j == 0 && i > 0){
                    g[i][j] = result / g[j][j];
                }   
                else if(i > 1 && i > j){
                    for(k = 0; k < j; k++){
                        result -= (g[i][k] * g[j][k]);
                    }

                    g[i][j] = result / g[j][j];
                }
            }
        }
    }

    double y[MAX];

    //G * y = b
    solveLowerTriangularSystem(order, g, b, y);

    //Transpondo G
    for(i = 0; i < order; i++){
        for(j = 0; j < order; j++){
            gT[i][j] = g[j][i];
        }
    }
    
    //Gt * x = y
    return solveUpperTriangularSystem(order, gT, y, solution);
}
// =================== Fim Cholesky =================== //


// =================== Funções Auxiliares Métodos Iterativos =================== //
int columnCriteria(int order, double B[MAX][MAX]){
    int i, j, aux;
    double max;

    max = -1;
    
    for(i = 0; i < order; i++){
        aux = 0;
        
        for(j = 0; j < order; j++){
            if(i != j){
                aux += fabs(B[j][i]);
            }
        }

        if(aux > max){
            max = aux;
        }
    }    

    return max < 1;
}

int rowCriteria(int order, double B[MAX][MAX]){
    int i, j, aux;
    double max;

    max = -1;
    
    for(i = 0; i < order; i++){
        aux = 0;
        
        for(j = 0; j < order; j++){
            if(i != j){
                aux += fabs(B[j][i]);
            }
        }

        if(aux > max){
            max = aux;
        }
    }    

    return max < 1;    
}

int sassenfeldCriteria(int order, double B[MAX][MAX]){
    double auxB[order];
    int i, j;
    
    for(i = 0; i < order; i++){
        auxB[i] = 0;
    }
    
    for(i = 0; i < order; i++){
        for(j = 0; j < order; j++){ 
            if(j < i){
                auxB[i] += B[i][j] * auxB[j];
            }
            else{
                auxB[i] += B[i][j];
            }
        }
    }

    double maior = auxB[0];

    for(i = 1; i < order; i++){
        if(auxB[i] > maior){
            maior = auxB[i];
        }
    }

    return maior < 1;
}

double calculateError(int order, double initialX[MAX], double solution[MAX]){
    double error, max;
    int i;

    error = fabs(solution[0] - initialX[0]);
    max = fabs(solution[0]);
    
    for(i = 1; i < order; i++){
        if(fabs(solution[i] - initialX[i]) > error){
            error = fabs(solution[i] - initialX[i]);
        }
        
        if(fabs(solution[i]) > max){
            max = fabs(solution[i]);
        }
    }
    
    return error / max;
}
// =================== Fim Funções Auxiliares Métodos Iterativos =================== //


// =================== Jacobi-Richardson =================== //
int jacobi(int order, double A[MAX][MAX], double b[MAX], double initialX[MAX], double precision, int maxIt, double solution[MAX], int *numIt){
    if(fabs(determinant(order, A)) <= 10e-7){
        return 0;
    }

    int i, j;
    double B[MAX][MAX], g[MAX];

    for(i = 0; i < order; i++){
        for(j = 0; j < order; j++){
            B[i][j] = -A[i][j] / A[i][i];
        }

        g[i] = b[i] / A[i][i];
    }
    
    if(!rowCriteria(order, B) && !columnCriteria(order, B)){
        printf("\nANALISE DE CONVERGENCIA: falhou!\n");
    }
    else{
        printf("\nANALISE DE CONVERGENCIA: sucesso!\n");
    }

    double aux[MAX];

    do{
        (*numIt)++;

        for(i = 0; i < order; i++){
            aux[i] = initialX[i];
        }
        
        for(i = 0; i < order; i++){
            
            solution[i] = g[i];
                     
            for(j = 0; j < order; j++){
                if(i != j){
                    solution[i] += (B[i][j] * aux[j]);
                }
            }

            initialX[i] = solution[i];
        }
    }while(calculateError(order, aux, initialX) >= precision && (*numIt) < maxIt);

    return 1;
}
// =================== Fim Jacobi-Richardson =================== //


// =================== Gauss-Seidel =================== //
int gaussSeidel(int order, double A[MAX][MAX], double b[MAX], double initialX[MAX], double precision, int maxIt, double solution[MAX], int *numIt){
    int i, j;
    double B[MAX][MAX], g[MAX];

    for(i = 0; i < order; i++){
        for(j = 0; j < order; j++){
            B[i][j] = (-A[i][j] / A[i][i]);
        }
        
        g[i] = b[i] / A[i][i]; 
    }
    
    if(!sassenfeldCriteria(order, B) && !rowCriteria(order, B)){
        printf("\nANALISE DE CONVERGENCIA: falhou!\n");
    }
    else{
        printf("\nANALISE DE CONVERGENCIA: sucesso!\n");
    }
    
    double aux[MAX];
    
    do{
        (*numIt)++;

        for(int i = 0; i < order; i++){
            aux[i] = initialX[i];
        }
        
        for(i = 0; i < order; i++){         
            solution[i] = g[i];
        
            for(j = 0; j < order; j++){
                if(i != j){
                    solution[i] += (B[i][j] * initialX[j]);
                }   
            }
            
            initialX[i] = solution[i]; 
        }
    }while(calculateError(order, aux, solution) >= precision && (*numIt) < maxIt);

    return 1;
}
// =================== Fim Gauss-Seidel =================== //


// =================== Função Principal =================== //
int main(){
    char reprocess;
    int option, order, maxIt, numIt, outValue;
    double initialSolution[MAX], vectorB[MAX], solution[MAX];
    double matrixA[MAX][MAX], inverseA[MAX][MAX], precision;

    do{
        system("cls||clear");
        
        do{
            printf("\nEscolha entre as opcoes de calculo abaixo:\n");
            printf("[01] Determinante\n");
            printf("[02] Matriz Inversa\n");
            printf("[03] Sistema Triangular Inferior\n");
            printf("[04] Sistema Triangular Superior\n");
            printf("[05] Decomposicao LU\n");
            printf("[06] Fatoracao de Cholesky\n");
            printf("[07] Eliminacao de Gauss\n");
            printf("[08] Gauss com Pivoteamento Parcial\n");
            printf("[09] Jacobi-Richardson\n");
            printf("[10] Gauss-Seidel\n");

            printf("Opcao escolhida: ");
            scanf("%d", &option);
        }while(option < 1 || option > 10);

        printf("\nOrdem da matriz/sistema: ");
        scanf("%d", &order);

        readMatrix(order, matrixA);

        if(option >= 3){
            printf("Elementos do vetor dos termos independentes (b): ");
            readVector(order, vectorB);

            if(option >= 9){
                printf("Elementos do vetor da solucao inicial (x0): ");
                readVector(order, initialSolution);

                printf("Precisao: ");
                scanf("%lf", &precision);

                printf("Numero maximo de iteracoes: ");
                scanf("%d", &maxIt);
            }
        }

        numIt = 0;

        switch(option){
            case 1:
                printf("O determinante eh: %.4lf\n", determinant(order, matrixA));
                break;
            case 2:
                if(inverseMatrix(order, matrixA, inverseA)){
                    printf("\nA matriz inversa eh:\n");
                    printMatrix(order, inverseA);
                }
                else{
                    printf("\nNao foi possivel calcular a inversa!\n");
                }
                break;
            case 3:
                outValue = solveLowerTriangularSystem(order, matrixA, vectorB, solution);
                break;
            case 4:
                outValue = solveUpperTriangularSystem(order, matrixA, vectorB, solution);               
                break;
            case 5:
                outValue = luDecomposition(order, matrixA, vectorB, solution);
                break;
            case 6:
                outValue = cholesky(order, matrixA, vectorB, solution);
                break;
            case 7:
                outValue = gaussianElimination(order, matrixA, vectorB, solution);
                break;
            case 8:
                outValue = gaussianEliminationPartialPivoting(order, matrixA, vectorB, solution);
                break;
            case 9:
                outValue = jacobi(order, matrixA, vectorB, initialSolution, precision, maxIt, solution, &numIt);
                break;
            case 10:
                outValue = gaussSeidel(order, matrixA, vectorB, initialSolution, precision, maxIt, solution, &numIt);
                break;
        }

        if(option >= 3 && option <= 8){
            if(outValue){
                printf("A solucao do sistema eh: ");
                printVector(order, solution);
            }
            else{
                printf("\nNao foi possivel calcular o sistema!\n");
            }
        }
        else if(option >= 9){
            if(outValue){
                printf("A solucao do sistema eh: ");
                printVector(order, solution);

                printf("O numero de iteracoes eh: %d", numIt);

                if(numIt > maxIt){
                    printf("\nNão foi possível alcançar o resultado com a precisão desejada dentro do número de iterações dado.");
                }
  
            }   
            else{
                printf("\nNao foi possivel calcular o sistema!");
            }                
        }

        getchar();

        printf("\nDeseja resolver novamente? (S/N) ");

        do{
            reprocess = toupper(getchar());
        }while(reprocess != 'S' && reprocess != 'N');
    }while(reprocess == 'S');

    return 0;
}
// =================== Fim Função Principal =================== //