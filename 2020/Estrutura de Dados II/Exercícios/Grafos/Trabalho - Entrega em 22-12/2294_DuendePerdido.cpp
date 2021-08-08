/*
Author: Davi Augusto Neves Leite
Date: 30/11/2020
2294 - Duende Perdido - URI Online Judge
*/

#include <bits/stdc++.h>

#define MAX 10

typedef long long ll;

using namespace std;

bool visited[MAX][MAX];
int cave[MAX][MAX];
int totalHall;
int N, M, initialX, initialY;

//Essa função nada mais é do que uma DFS que percorre o labirinho em todas as posições
void DFS(int posX, int posY, int countHall){
    if (posX < 0 || posY < 0 || posX >= N || posY >= M || cave[posX][posY] == 2 || visited[posX][posY] || totalHall < countHall){
        return;
    }
    if(cave[posX][posY] == 0){
        totalHall = min(totalHall, countHall);
        return;
    }

    //Marcando o lugar visitado para não contar duas vezes
    visited[posX][posY] = true;

    DFS(posX + 1, posY, countHall + 1);
    DFS(posX - 1, posY, countHall + 1);
    DFS(posX, posY + 1, countHall + 1);
    DFS(posX, posY - 1, countHall + 1);

    //Caso não tenha dado certo, ele retorna o passo (conta como não visitado)
    visited[posX][posY] = false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    totalHall = INT_MAX;
    memset(cave, 0, sizeof(cave));
    memset(visited, false, sizeof(visited));

    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> cave[i][j];

            //Salvando as posições iniciais do Duende
            if(cave[i][j] == 3){
                initialX = i;
                initialY = j;
            }
        }
    }

    //DFS que percorre o labirinho, verificando as posições
    DFS(initialX, initialY, 0);

    cout << totalHall << endl;

    return 0;
}