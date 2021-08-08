/*
Author: Davi Augusto Neves Leite
Date: 06/12/2020
1774 - Roteadores - URI Online Judge
*/

#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Utilização do Algoritmo de Prim (semelhante ao Dijkstra) para Árvore Geradora Mínima do Grafo, iniciando no vértice 1
ll PrimAlgorithm(vector<pair<int, int>> graph[], int sourceNode, int maxNode){
    
    //Utilização de uma fila de prioridade para salvar os vértices já "salvos" na Árvore Geradora Mínima
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> saveNodes;
    //Adicionar a aresta inicial com custo 0
    saveNodes.push({0, sourceNode});

    //Vetor auxiliar para marcar os vértices já visitados
    bool visited[maxNode + 1];
    memset(visited, false, sizeof(visited));

    //Armazenamento do custo total da Árvore Geradora Mínima
    ll totalMSTCost = 0;
    
    while(!saveNodes.empty()){
        //Processar o vértice do início da Fila para visitar as arestas ligadas de menor custo
        pair<int, int> auxNode;
        auxNode = saveNodes.top();
        saveNodes.pop(); //Limpar o vértice da Fila

        //Caso o vértice não tenha sido visitado
        if(!visited[auxNode.second]){
            totalMSTCost += auxNode.first; //Adicionar o custo total
            visited[auxNode.second] = true;  //Marcar o vértice como visitado
        
            //Adicionar todos os vértices adjacentes não visitados (e, consequentemente, não presentes na Árvore) à Fila
            for(int i = 0; i < graph[auxNode.second].size(); i++){
                int adjNode = graph[auxNode.second][i].first;  //Vértice adjacente
                int adjCost = graph[auxNode.second][i].second; //Custo da Aresta
                
                if(visited[adjNode] == false){
                    saveNodes.push({adjCost, adjNode});
                }
            }
        }
    }

    return totalMSTCost;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int R, C;
    cin >> R >> C;

    //Grafo Não Direcionado em Lista de Adjacência
    vector<pair<int, int>> graph[R + 1];

    for(int i = 0; i < C; i++){
        int V, W, P;
        cin >> V >> W >> P;

        //Realizando a conexão entre os vértices (não direcionado -> realizar em ambos os lados)
        graph[V].push_back({W, P});
        graph[W].push_back({V, P});
    }

    cout << PrimAlgorithm(graph, 1, R) << endl;

    return 0;
}