/*
Author: Davi Augusto Neves Leite
Date: 08/12/2020

Identificação no URI: 344952
URI 2731 - Programação de Viagem
Disponível em: https://www.urionlinejudge.com.br/judge/pt/problems/view/2731

Explicação:

A ideia do exercício é simples: dado um número de cidades (vértices do grafo) com
pelo menos um caminho que leva a cada cidade (arestas do grafo),
basta encontrar o menor custo para atravessar todas as cidades e verificar
se esse custo (em minutos) está dentro da faixa para Valentina chegar na faculdade.

O horário de término das aulas, ou seja, dela atravessar todas as cidades é 17h30min;
já o horário de início das aulas da faculdade é 19h30min. Dessa forma, há um intervalo
permitido de 2 horas para ela chegar até sua cidade para as aulas da faculdade, sendo
essa cidade indicada sempre com o vértice 1.

Em outras palavras, basta aplicar um algoritmo de caminho mínimo como Dijkstra haja
visto que também é dado a informação do vértice que ela está no momento (origem).
Esse algoritmo considera, inicialmente, o custo 0 da aresta inicial e todas as outras como
infinito para assim percorrer o grafo (por largura) e verificar o menor custo possível a partir
do que ele já tem (inicialmente com 0).

E, além disso, durante a aplicação do algoritmo é necessário salvar os vértices visitados
do menor caminho em uma Fila auxiliar para mostrar posteriormente e verificar se o tempo
mínimo encontrado ultrapassa (em quantos minutos) ou não o intervalo permitido de 2 horas.

Notas: 2 horas em minutos => 120 minutos
*/

#include <bits/stdc++.h>

#define MAX 280
typedef long long ll;

using namespace std;

//Algoritmo de Dijkstra para encontrar o menor caminho do vértice D até o vértice 1, neste exercício.
//E salvar os vértices visitados para posterior visualização.
vector<int> Dijkstra(vector<pair<int, int>> graph[], int sourceNode, int destNode, int maxNode, ll *shortPath)
{
    //Vetor auxiliar para marcar como infinito as distância a partir do vértice inicial
    vector<long long> distance(maxNode + 1, LONG_LONG_MAX);
    distance[sourceNode] = 0; //Vértice inicial com distância 0

    //Uso de fila de prioridade para armazenar os vértices visitados e na ordem de peso
    priority_queue<pair<int, int>> saveNodes;
    saveNodes.push({0, sourceNode}); //Inserção do vértice inical com custo 0

    //Vetor auxiliar de pais vértices visitados no Caminho Mínimo
    vector<int> parentNodes(MAX, -1);

    while(!saveNodes.empty()){
        //Processar o vértice atual presente no início da Fila (menor custo total)
        int actualNode = saveNodes.top().second;
        saveNodes.pop();

        //Verificar as distâncias para cada vértice adjacente ao atual
        for (int i = 0; i < graph[actualNode].size(); i++)
        {
            int adjNode = graph[actualNode][i].first;
            int adjCost = graph[actualNode][i].second;

            //Verificação da distância mínima (relaxamento da aresta): se a distância do nó adjacente for maior do que o custo da aresta dela mais a distância até o nó atual
            if (distance[adjNode] > distance[actualNode] + adjCost)
            {
                //Salvar o custo total da distância até o vértice adjacente
                distance[adjNode] = distance[actualNode] + adjCost;

                //Salvando os pais dos vértices visitados
                parentNodes[adjNode] = actualNode;

                //Salvar o vértice adjacente e o custo atual total até ele na Fila de Prioridade para processamento
                //A distância negativa implica em salvá-lo no início da Fila de Prioridade (por sua estrutura de Heap Máxima, precisa-se de uma Heap Mínima aqui)
                saveNodes.push({-distance[adjNode], adjNode});
            }
        }
    }

    //Armazenando o valor do menor caminho
    (*shortPath) = distance[destNode];

    //Retornando o vetor de pais vértices visitados
    return parentNodes;
}

void printShortestPath(vector<int> parentNodes, int node){
    //Caso não tenha passado pelo vértice, o valor é -1 como construído na função Dijkstra
    if(parentNodes[node] == -1){
        return;
    }

    //Avançando no Grafo a partir do pai
    printShortestPath(parentNodes, parentNodes[node]);

    //Mostrando o valor
    printf(" %d", node);
}

int main(){

    //Quantidade de Cidades (C) e de Estradas (E)
    int C, E;
    while(cin >> C >> E){
        if(C == 0 && E == 0){
            break;
        }

        //Representação em Lista de Adjacência
        vector<pair<int, int>> graph[C + 1];
        for(int i = 0; i < E; i++){
            int C1, C2, T;
            cin >> C1 >> C2 >> T;

            //Adicionando no grafo, bidirecionalmente
            graph[C1].push_back({C2, T});   //Cidade 1 para Cidade 2, com custo T
            graph[C2].push_back({C1, T});   //Cidade 2 para Cidade 1, com custo T
        }

        //Vértice de origem do grafo  
        int D;
        cin >> D;

        //Valor do menor caminho encontrado no Dijkstra
        ll shortPath = 0LL;

        //Fila auxiliar para salvar os pais dos vértices visitados do caminho mínimo
        vector<int> parentNodes = Dijkstra(graph, D, 1, C, &shortPath);

        //Verificando se o menor caminho (tempo) é menor ou igual a 120 minutos, tempo máximo para chegar as aulas da faculdade
        if(shortPath <= 120){
            printf("Will not be late. Travel time - %lld - best way -", shortPath);
        }
        else{
            printf("It will be %lld minutes late. Travel time - %lld - best way -", (shortPath - 120), shortPath);
        }

        //Mostrando os vértices visitados
        printf(" %d", D);                   //Vértice inicial
        printShortestPath(parentNodes, 1);  //Menor caminho até o vértice 1
        
        cout << endl;
    }
    
    return 0;
}