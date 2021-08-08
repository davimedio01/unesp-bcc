/*Trabalho de Interpolação e Ajustes de Curva
Métodos Numéricos Computacionais (MNC)

Integrantes                RA
Davi Augusto Neves Leite   191027383
Giovani Candido            191021601
Luis Henrique Morelli      181027097
Luiz Fernando Sementille   191021032*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXROW 2
#define MAXCOL 10

// =================== Funções Auxiliares =================== //
void readTable(int numPoints, double table[][MAXCOL]){
    int i, j;
    
    printf("\nElementos da Tabela\n\n");

    for (i = 0; i < MAXROW; i++){
        if(!i){
            printf("Valores de X: ");
        }
        else{
            printf("Valores de F(x): ");
        }
        for(j = 0; j < numPoints; j++){
            scanf("%lf", &table[i][j]);
        }
    }
}

void printTable(int numPoints, double table[MAXROW][MAXCOL]){
    int i, j;
    for(i = 0; i < MAXROW; i++){
        for(j = 0; j < numPoints; j++){
            printf("%.4lf ", table[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

void printVector(int numPoints, double Y[MAXCOL]){
    int i;
    
    for(i = 0; i < numPoints; i++){
        printf("%.4lf ", Y[i]);
    }
    
    printf("\n");
}

void printPolinomial(int degree, double coef[MAXCOL]){
    int i;

    for (i = 0; i < degree + 1; i++){
        if(i == 0){
            printf("(%.4lf)", coef[i], i);
        }
        else{
            printf(" + (%.4lf)*X^%d", coef[i], i);
        }
    }

    printf("\n");
    
}

int isLowerTriangularMatrix(int order, double matrix[MAXCOL][MAXCOL]){
    int i, j;

    for(i = 0; i < order; i++){
        for(j = i+1; j < order; j++){
            if(fabs(matrix[i][j]) > 10e-7){
                return 0;
            }
        }
    }

    return 1;
}

int isUpperTriangularMatrix(int order, double matrix[MAXCOL][MAXCOL]){
    int i, j;

    for(i = 1; i < order; i++){
        for(j = 0; j < i; j++){
            if(fabs(matrix[i][j]) > 10e-7){
                return 0;
            }
        }
    }

    return 1;
}

int solveLowerTriangularSystem(int order, double A[][MAXCOL], double b[MAXCOL], double solution[MAXCOL]){
    if (!isLowerTriangularMatrix(order, A))
    {
        return 0;
    }

    int i, j;
    double sum;
    
    for (i = 0; i < order; i++)
    {
        sum = 0;

        for (j = 0; j < i; j++)
        {
            sum += A[i][j] * solution[j];
        }

        solution[i] = (b[i] - sum) / A[i][i];
    }

    return 1;
}

int solveUpperTriangularSystem(int order, double A[][MAXCOL], double b[MAXCOL], double solution[MAXCOL])
{
    if (!isUpperTriangularMatrix(order, A))
    {
        return 0;
    }

    int i, j;
    double sum;

    for (i = order - 1; i >= 0; i--)
    {
        sum = 0;

        for (j = i + 1; j < order; j++)
        {
            sum += A[i][j] * solution[j];
        }
        
        solution[i] = (b[i] - sum) / A[i][i];
    }

    return 1;
}

double determinant(int order, double matrix[][MAXCOL])
{
    //Matriz Auxiliar
    double submatrix[MAXCOL][MAXCOL];
    double det = 0.;

    if (order == 1){
        return (matrix[0][0]);
    }

    if (order == 2){
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    }

    int i, j, k;
    int subRow, subCol;

    for (i = 0; i < order; i++)
    {
        subRow = 0;

        for (j = 1; j < order; j++)
        {
            subCol = 0;

            for (k = 0; k < order; k++)
            {
                if (i == k)
                {
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

void luDecomposition(int order, double A[][MAXCOL], double b[MAXCOL], double solution[MAXCOL])
{
    int i;

    for (i = 1; i <= order; i++)
    {
        if (fabs(determinant(i, A)) <= 10e-7)
        {
            return;
        }
    }

    int j, k;
    double L[MAXCOL][MAXCOL], U[MAXCOL][MAXCOL];

    for (i = 0; i < order; i++)
    {
        for (j = 0; j < order; j++)
        {
            L[i][j] = 0;
            U[i][j] = 0;
        }
    }

    for (i = 0; i < order; i++)
    {
        for (j = 0; j < order; j++)
        {
            if (i <= j)
            {
                U[i][j] = A[i][j];

                for (k = 0; k < i; k++)
                {
                    U[i][j] -= L[i][k] * U[k][j];
                }
            }
            else
            {
                L[i][j] = A[i][j];

                for (k = 0; k < j && i > j; k++)
                {
                    L[i][j] -= L[i][k] * U[k][j];
                }

                L[i][j] /= U[j][j];
            }
        }

        L[i][i] = 1;
    }

    double y[MAXCOL];

    solveLowerTriangularSystem(order, L, b, y);

    solveUpperTriangularSystem(order, U, y, solution);
}

long fatorial(int x){
    long i;
    long fat = 1;
    for(i = 1; i <= x; i++){
        fat *= i;
    }
    return fat;
}

// =================== Fim Funções Auxiliares =================== //

double lagrangeInterpolation(int numPoints, double table[][MAXCOL], double x){
    double px, lx;
    int i, j;

    px = 0;

    for(i = 0; i < numPoints; i++){
        lx = 1;
        
        for(j = 0; j < numPoints; j++){
            if(j != i){
                lx *= (x-table[0][j])/(table[0][i]-table[0][j]);
            }
        }

        px += table[1][i]*lx;
    }

    return px;
}

double newtonInterpolation(int numPoints, double table[][MAXCOL], double x){
    int i, j, k;
    double dividedDifference[MAXCOL][MAXCOL];

    for(i = 0; i < numPoints; i++){
        dividedDifference[i][0] = table[1][i];
    }

    for(i = 1; i < numPoints; i++){
        for(j = 0; j < numPoints - 1; j++){
            dividedDifference[j][i] = (dividedDifference[j][i - 1] - dividedDifference[j + 1][i - 1]); 
            dividedDifference[j][i] /= (table[0][j] - table[0][i + j]);
        }
    }

    double answer;

    answer = dividedDifference[0][0];

    for(i = 1; i < numPoints; i++){
        double aux;

        aux = 1.;

        for (j = 0; j < i; j++) { 
            aux *= (x - table[0][j]); 
        }

        answer += aux * dividedDifference[0][i];
    }

    return answer;
}

double newtonGregoryInterpolation(int numPoints, double table[][MAXCOL], double x){
    
    int i, j, aux;
    double diferencasOrdinarias[MAXCOL][MAXCOL], result = table[1][0], mult = 1, h, den;

    for (i = 0; i < MAXCOL; i++){
        for (j = 0; j < MAXCOL; j++){
            diferencasOrdinarias[i][j] = 0.0;
        }
    }

    h = fabs(table[0][1] - table[0][0]);

    for(i = 0; i < numPoints; i++){
        diferencasOrdinarias[0][i] = table[1][i];
    }

    aux = numPoints;

    for(i = 0; i < numPoints - 1; i++){
        for(j = 0; j < aux - 1; j++){
            diferencasOrdinarias[i + 1][j] = diferencasOrdinarias[i][j + 1] - diferencasOrdinarias[i][j]; 
        }
        aux--;
    }
    
    aux = 1;

    for(i = 0; i < numPoints; i++){
        
        mult = 1;
        
        for(j = 0; j < i + 1; j++){
            mult *= (x - table[0][j]);
        }
        
        den = pow(h, i + 1) * (double) fatorial(i+1);
        mult *= (diferencasOrdinarias[i+1][0] / den); 
        
        result += mult;
    }

    return result;
}

void solveFittingSystem(int numPoints, double table[][MAXCOL], int degree, double solution[MAXCOL], int type){  
    int i;
    
    for(i = 0; i < MAXCOL; i++){
        solution[i] = 0.0;
    }
    
    int j, k; 
    double A[MAXCOL][MAXCOL];
    double B[MAXCOL];

    double sum;
    
    for(i = 0; i < degree + 1; i++){
        if(i == 0){
            A[0][i] = numPoints;
        }
        else{
            sum = 0.0;
        
            for(j = 0; j < numPoints; j++){
                sum += pow(table[0][j], i);
            }

            A[0][i] = sum;
        }
    }

    sum = 0.0;

    for(i = 0; i < numPoints; i++){ 
        if(type == 0){
                sum += table[1][i];
            }
            else{
                sum += log(table[1][i]);
            }
    }

    B[0] = sum;

    for(i = 1; i < degree + 1; i++){
        for(j = 0; j < degree ; j++){
            A[i][j] = A[i - 1][j + 1];
        }

        sum = 0.0;

        for(k = 0; k < numPoints; k++){
            sum += pow(table[0][k], j + i);
        }

        A[i][degree] = sum;

        sum = 0.0;
        
        for(j = 0; j < numPoints; j++){
            if(type == 0){
                sum += table[1][j] * pow(table[0][j], i);
            }
            else{
                sum += log(table[1][j]) * pow(table[0][j], i);
            }
        }

        B[i] = sum;
    }

    luDecomposition(degree + 1, A, B, solution);
}

void linearFitting(int numPoints, double table[][MAXCOL], double *a, double *b, double Y[MAXCOL]){
    int i;
    double solution[MAXCOL];
    solveFittingSystem(numPoints, table, 1, solution, 0);

    (*a) = solution[1];
    (*b) = solution[0];

    //Aplicando X da tabela com o ajuste encontrado
    for(i = 0; i < numPoints; i++){
        Y[i] = (*a) * table[0][i] + (*b);
    }

}

void polinomialFitting(int numPoints, double table[][MAXCOL], int degree, double coef[MAXCOL], double Y[MAXCOL]){
    solveFittingSystem(numPoints, table, degree, coef, 0);

    //Aplicando X da tabela com o ajuste encontrado
    int i, j;
    double sum;
    
    for(i = 0; i < numPoints; i++){

        sum = 0.0;

        for(j = 0; j < numPoints; j++){

            if (fabs(coef[j]) > 10e-7){
                sum += coef[j] * pow(table[0][i], j);
            }
        }

        Y[i] = sum;
    }
}

void exponencialFitting(int numPoints, double table[][MAXCOL], double *a, double *b, double Y[MAXCOL]){
    int i;
    double solution[MAXCOL];
    solveFittingSystem(numPoints, table, 1, solution, 1);

    (*a) = exp(solution[0]);
    (*b) = exp(solution[1]);

    //Aplicando X da tabela com o ajuste encontrado
    for (i = 0; i < numPoints; i++){
        Y[i] = (*a) * pow((*b), table[0][i]);
    }
}

int main(){

    char reprocess;
    int option, numPoints, polynomialDegree;
    double table[MAXROW][MAXCOL], x, a, b, coef[MAXCOL], Y[MAXCOL], result;

    do{
        system("cls||clear");
        
        do{
            printf("\nEscolha entre as opcoes de Interpolacao/Ajuste abaixo:\n");
            printf("[01] Polinomio de Lagrange\n");
            printf("[02] Polinomio de Newton\n");
            printf("[03] Polinomio de Newton-Gregory\n");
            printf("[04] Ajuste Linear\n");
            printf("[05] Ajuste Polinomial\n");
            printf("[06] Ajuste Exponencial\n");
            printf("Opcao escolhida: ");

            scanf("%d", &option);
        }while(option < 1 || option > 6);
      
        printf("\nNumero de pontos da tabela (max. 10): ");
        do{
            scanf("%d", &numPoints);
        }while(numPoints >= MAXCOL);
        

        readTable(numPoints, table);

        if(option <= 3){
            printf("\nO valor de X na qual se deseja saber F(X): ");
            scanf("%lf", &x);
        }
        else if (option == 5){
            printf("\nO grau do polinomio interpolador na qual deseja-se aproximar: ");
            scanf("%d", &polynomialDegree);
        }

        switch(option){
            case 1:
                result = lagrangeInterpolation(numPoints, table, x);

                printf("\nO valor de F(%.4lf) utilizando o polinomio de Lagrange eh %.4lf\n", x, result);
                
                break;
            case 2:
                result = newtonInterpolation(numPoints, table, x);
                
                printf("\nO valor de F(%.4lf) utilizando o polinomio de Newton eh %.4lf\n", x, result);
                
                break;
            case 3:
                result = newtonGregoryInterpolation(numPoints, table, x);
                
                printf("\nO valor de F(%.4lf) utilizando o polinomio de Newton-Gregory eh %.4lf\n", x, result);
                
                break;
            case 4:
                linearFitting(numPoints, table, &a, &b, Y);
                
                printf("\nO ajuste linear resultou em: Y = (%.4lf) + (%.4lf)X", b, a);
                printf("\nE os valores de X da tabela, ajustados ao polinomio: ");
                printVector(numPoints, Y);

                break;
            case 5:
                polinomialFitting(numPoints, table, polynomialDegree, coef, Y);
                
                printf("\nO ajuste polinomial resultou em: Y = ");
                printPolinomial(polynomialDegree, coef);
                printf("\nE os valores de X da tabela, ajustados ao polinomio: ");
                printVector(numPoints, Y);
                
                break;
            case 6:
                exponencialFitting(numPoints, table, &a, &b, Y);
                
                printf("\nO ajuste exponencial resultou em: Y = (%.4lf)*(%.4lf)^X", a, b);
                printf("\nE os valores de X da tabela, ajustados ao polinomio: ");
                printVector(numPoints, Y);
                
                break;
        }

        getchar();
        
        printf("\nDeseja resolver novamente? (S/N) ");

        do{
            reprocess = toupper(getchar());
        }while(reprocess != 'S' && reprocess != 'N');
    }while(reprocess == 'S');
    
    return 0;
}