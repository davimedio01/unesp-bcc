import heapq as hp  # Utilizado para importar a árvore heap para o algoritmo de Prim

###################################################################################
# Algoritmo de Prim
###################################################################################
def prim(origem, numVertices, adjLista):
    visitado = [False for i in range(numVertices + 1)]
    parent = [-1 for i in range(numVertices + 1)]
    distancia = [float('inf') for i in range(numVertices + 1)]
    
    fila_prioridade = []
    distancia[origem] = 0
    hp.heappush(fila_prioridade, [distancia[origem], origem]) # Inserindo o primeiro vértice com custo 0
    
    mst = []
    custo = 0

    while fila_prioridade:
        # Recuperando valores
        valor_fila = fila_prioridade[0]
        peso, no = valor_fila

        hp.heappop(fila_prioridade) # Eliminando da Fila

        if(not visitado[no]):
            custo += peso
            visitado[no] = True

            for par_peso_no in adjLista[no]:
                no_adj, peso_adj = par_peso_no
                if(visitado[no_adj] == False and distancia[no_adj] > peso_adj):
                    parent[no_adj] = no
                    distancia[no_adj] = peso_adj
                    
                    hp.heappush(fila_prioridade, [peso_adj, no_adj])

    for i in range(1, numVertices + 1):
        if(parent[i] != -1):
            mst.append([parent[i], i, distancia[i]])
    
    return mst, custo

###################################################################################
# Algoritmo de Krukal
###################################################################################
def kruskal(numArestas, arestaLista):
    mst = []
    custo = 0

    # Ordenar por peso
    arestaLista = sorted(arestaLista)

    for i in range(numArestas):
        peso = arestaLista[i][0]
        origem = arestaLista[i][1]
        destino = arestaLista[i][2]

        origemLocalizacao = encontrar(origem)
        destinoLocalizacao = encontrar(destino)

        if(origemLocalizacao != destinoLocalizacao):
            juntar(origemLocalizacao, destinoLocalizacao)
            custo += peso

            mst.append([origem, destino, peso])

    return mst, custo

###################################################################################
# Funções Auxiliares
###################################################################################
# Disjoint Set Union (DSU) para Kruskal
def juntar(a, b):
    if(tamanho[a] < tamanho[b]):
        a, b = b, a

    link[b] = a
    tamanho[a] += tamanho[b]

def encontrar(x):
    if(x == link[x]):
        return x

    return encontrar(link[x])

# Mostrar a MST e o custo mínimo total
def mostraMST(mst, cost):
    print('Árvore Geradora Mínima:\n')

    for aresta in mst:
        print(aresta)

    print('\nCusto:', cost)
    print("##############################")

###################################################################################
# Main
###################################################################################
numVertices, numArestas = input().split()

numVertices = int(numVertices)  # Número de Vértices
numArestas  = int(numArestas)   # Número de Arestas

# Prim com Lista de Adjacência
adjLista = [[] for i in range(numVertices + 1)]

# Kruskal com Lista de Arestas Adjacentes
arestaLista = []
link = [i for i in range(numVertices + 1)]
tamanho = [1 for i in range(numVertices + 1)]

# Leitura do Grafo
for i in range(numArestas):
    origem, destino, peso = input().split()

    origem = int(origem)
    destino = int(destino)
    peso = int(peso)

    # Inserção no Prim
    adjLista[origem].append([destino, peso])
    adjLista[destino].append([origem, peso])

    # Inserção no Kruskal
    arestaLista.append([peso, origem, destino])

# Aplicando Prim para MST
mst, custo = prim(1, numVertices, adjLista)

# Resultado do Prim
print("##############################")
print("Algoritmo de Prim")
mostraMST(mst, custo)

# Aplicando Kruskal para MST
mst, custo = kruskal(numArestas, arestaLista)

# Resultado do Kruskal
print("Algoritmo de Kruskal")
mostraMST(mst, custo)
