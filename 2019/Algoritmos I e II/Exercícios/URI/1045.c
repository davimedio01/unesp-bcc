#include <stdio.h>
#include <stdlib.h>

int main()
{
    float A,B,C,troca;
    scanf("%f %f %f",&A,&B,&C);
    if(A<=B && B<=C)
    {
        troca = A;
        A=C;
        C = troca;
    }
    else if(A<=B && B>=C)
    {
        troca = A;
        A=B;
        B=troca;
    }

    if(A>=(B+C))
        printf("NAO FORMA TRIANGULO\n");
    else if(A*A==(B*B+C*C))
    {
        printf("TRIANGULO RETANGULO\n");
        if((A==B)&&(B==C))
        printf("TRIANGULO EQUILATERO\n");
    else if((A==B)||(B==C)||(A==C))
        printf("TRIANGULO ISOSCELES\n");
    }
    else if(A*A>(B*B+C*C))
    {
        printf("TRIANGULO OBTUSANGULO\n");
        if((A==B)&&(B==C))
        printf("TRIANGULO EQUILATERO\n");
    else if((A==B)||(B==C)||(A==C))
        printf("TRIANGULO ISOSCELES\n");
    }
    else if(A*A<(B*B+C*C))
    {
        printf("TRIANGULO ACUTANGULO\n");
        if((A==B)&&(B==C))
        printf("TRIANGULO EQUILATERO\n");
    else if((A==B)||(B==C)||(A==C))
        printf("TRIANGULO ISOSCELES\n");
    }

    return 0;
}
