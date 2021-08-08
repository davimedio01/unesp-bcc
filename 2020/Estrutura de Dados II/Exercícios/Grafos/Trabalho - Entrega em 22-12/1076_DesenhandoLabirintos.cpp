/*
Author: Davi Augusto Neves Leite
Date: 06/12/2020
1076 - Desenhando Labirintos - URI Online Judge
*/

#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Utilização da BFS para percorrer o Grafo por largura e adicionar o custo de "visitado" das arestas
ll BFS(vector<int> graph[], int sourceNode, int maxNode){
    //Uso de Fila para salvar os vértices a serem visitados
    queue<int> saveNodes;
    //Salvar o vértice inicial na Fila
    saveNodes.push(sourceNode);

    //Vetor auxiliar para marcar os vértices já visitados
    bool visited[maxNode + 1];
    memset(visited, false, sizeof(visited));
    visited[sourceNode] = true; //Marcar o vértice inicial como visitado

    //Custo total das linhas desenhadas
    ll totalCost = 0;

    while(!saveNodes.empty()){
        //Processar o vértice da frente da Fila
        int actualNode = saveNodes.front();
        saveNodes.pop();

        //Salvar todos os vértices adjacentes para futuro processamento
        for(int i = 0; i < graph[actualNode].size(); i++){
            int adjNode = graph[actualNode][i];

            if(visited[adjNode] == false){
                //Adicionar o custo de 2 para cada vértice visitado (ida e volta)
                totalCost += 2;

                //Marcar o vértice como visitado e adicionar na Fila
                visited[adjNode] = true;
                saveNodes.push(adjNode);
            }
        }
    }

    return totalCost;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin >> T;

    while(T--){
        //Vértice Inicial
        int N;
        cin >> N;

        int V, A;
        cin >> V >> A;

        //Utilização da Lista de Adjacência
        vector<int> graph[V + 1];
        for(int i = 0; i < A; i++){
            int V1, V2;
            cin >> V1 >> V2;

            graph[V1].push_back(V2);
            graph[V2].push_back(V1);
        }

        cout << BFS(graph, N, V) << endl;
    }


    return 0;
}