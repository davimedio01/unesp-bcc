#include <stdio.h>
#include <stdlib.h>

/*Uso da combin��o na f�rmula de Euler (V+F=A+2)
    Arestas s�o dadas pela combina��o de N tomados 2 a 2 (N 2) (por conta de cada par de ponto), mais 2 vezes a combina��o (N 4) (por conta das intersec��es), mais o N para o segmento do circulo;
    Vertices s�o dados pela combina��o de N tomados 4 a 4 (N 4) (por conta da quadr�pla de pontos), mais o N (por conta das intersec��es)
    O 2 � transformado em 1 porque nao importa a regi�o externa do plano
*/

int main()
{
    long long int n,faces;
    scanf("%lld",&n);
    faces=(((n*(n-1)/2) + (n*(n-1)*(n-2)*(n-3))/24) + 1);
    printf("%lld\n",faces);
    return 0;
}
