/*
Author: Davi Augusto Neves Leite
Date: 06/12/2020
1148 - Países em Guerra - URI Online Judge
*/

#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

ll Dijkstra(vector<pair<int, int>> graph[], int sourceNode, int destNode, int maxNode){

    //Vetor auxiliar para marcar como infinito as distâncias a partir do vértice inicial
    vector<long long> distance(maxNode + 1, LONG_LONG_MAX);
    distance[sourceNode] = 0;  //Vértice inicial com distância 0

    //Uso de um SET (sem repetição de elementos) para armazenamento da distância e do vértice a ser visitado
    //Isso evitará o acesso as arestas infinitas e ordernará crescentemente com base nos menores pesos das arestas
    set<pair<int, int>> saveNodes;
    saveNodes.insert({0, sourceNode});  //Inserção do vértice inical com custo 0

    while(!saveNodes.empty()){
        //Processar o vértice atual presente no início do SET (menor custo total)
        pair<int, int> actualNode = *saveNodes.begin();
        saveNodes.erase(saveNodes.begin());
        
        //Verificar as distâncias para cada vértice adjacente ao atual
        for(int i = 0; i < graph[actualNode.second].size(); i++){
            int adjNode = graph[actualNode.second][i].first;
            int adjCost = graph[actualNode.second][i].second;
            
            //Verificação da distância mínima (relaxamento da aresta): se a distância do nó adjacente for maior do que o custo da aresta dela mais a distância até o nó atual
            if(distance[adjNode] > distance[actualNode.second] + adjCost){
                //Se a distância até o nó adjacente não for infinito, significa que ela está presente no SET, ou seja, deve ser removida
                if (distance[adjNode] != LONG_LONG_MAX){
                    saveNodes.erase(saveNodes.find({distance[adjNode], adjNode}));
                }
                //Salvar o custo total da distância até o vértice adjacente
                distance[adjNode] = distance[actualNode.second] + adjCost;
                //Salvar o vértice adjacente e o custo atual total até ele no SET para processamento        
                saveNodes.insert({distance[adjNode], adjNode});
            }
        }
    }

    return distance[destNode];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, E;
    while(cin >> N >> E){
        if(N == 0 && E == 0){
            break;
        }

        //Utilização de Lista de Adjacência
        vector<pair<int, int>> graph[N + 1];
        for(int i = 0; i < E; i++){
            int X, Y, H;
            cin >> X >> Y >> H;

            graph[X].push_back({Y, H});
            for(int j = 0; j < graph[Y].size(); j++){
                //Condição de Adjacência do Exercício: comunicação instântanea (tempo = 0) para cidades interligadas
                //Ou seja, colocar o custo das arestas com 0 para cidades que tem arestas bidirecionais
                if(graph[Y][j].first == X){
                    graph[Y][j].second = 0;
                    graph[X].back().second = 0; //Última aresta a ser adicionada

                    break;
                }
            }

        }

        //Número de Consultas
        int K;
        cin >> K;
        for(int i = 0; i < K; i++){
            int O, D;
            cin >> O >> D;

            ll answer = Dijkstra(graph, O, D, N);

            if(answer != LONG_LONG_MAX){
                cout << answer << endl;
            }
            else{
                cout << "Nao e possivel entregar a carta" << endl;
            }
        }

        cout << endl;
    }


    return 0;
}