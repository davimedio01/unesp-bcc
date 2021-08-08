#include <stdio.h>
#include <stdlib.h>

/*Uso da combinção na fórmula de Euler (V+F=A+2)
    Arestas são dadas pela combinação de N tomados 2 a 2 (N 2) (por conta de cada par de ponto), mais 2 vezes a combinação (N 4) (por conta das intersecções), mais o N para o segmento do circulo;
    Vertices são dados pela combinação de N tomados 4 a 4 (N 4) (por conta da quadrúpla de pontos), mais o N (por conta das intersecções)
    O 2 é transformado em 1 porque nao importa a região externa do plano
*/

int main()
{
    long long int n,faces;
    scanf("%lld",&n);
    faces=(((n*(n-1)/2) + (n*(n-1)*(n-2)*(n-3))/24) + 1);
    printf("%lld\n",faces);
    return 0;
}
