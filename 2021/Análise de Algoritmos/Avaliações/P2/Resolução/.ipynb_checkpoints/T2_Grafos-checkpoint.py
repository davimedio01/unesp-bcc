# Para a utilização da "Heapify" (construir uma Árvore Heap a partir de uma lista) no HeapSort
import heapq


class Ordenacao():
    """
        Classe para algoritmos de ordenação de vetores by Davi & Luiz
    """
    # def __init__(self):
    # print("Classe ''Ordenação'' iniciada com sucesso!\n")

    def bubbleSort(self, lista):
        """
            Versão otimizada do BubbleSort: contém uma variável booleana que 
            verifica se a lista já está ordenada.
            Complexidade do Algoritmo: O(n²)
        """
        trocas = True
        tamanhoVetor = len(lista) - 1
        while tamanhoVetor > 0 and trocas:
            trocas = False
            for i in range(tamanhoVetor):
                if lista[i] > lista[i + 1]:
                    trocas = True
                    # Variável Temporária de Troca -> Gasto Espacial
                    lista[i], lista[i + 1] = lista[i + 1], lista[i]
            tamanhoVetor -= 1

    def insertionSort(self, lista):
        """Algoritmo de ordenação InsertionSort
        Complexidade do algoritmo: O(n²)

        Args:
            lista (Lista): lista a ser ordenada
        """
        for i in range(1, len(lista)):
            valor = lista[i]
            j = i - 1

            while j >= 0 and valor < lista[j]:
                lista[j + 1] = lista[j]
                j -= 1

            lista[j + 1] = valor

    def mergeSort(self, lista):
        """Algoritmo de ordenação MergeSort.
        Complexidade do Algoritmo: O(n*log(n))

        Args:
            lista (List): Lista a ser ordenada
        """
        # Caso-base: vetor com um elemento não é processado
        if len(lista) > 1:
            # Divisão inteira para pegar a posição do meio
            meio = len(lista) // 2
            # Salva a lista do início até o meio (esquerda)
            esquerda = lista[:meio]
            direita = lista[meio:]  # Salva a lista do meio até o fim (direita)

            # Aplica o algoritmo novamente a fim de se obter a menor: Divisão e Conquista
            self.mergeSort(esquerda)
            self.mergeSort(direita)

            # Auxiliares para percorrer as sub-listas
            i, j, k = 0, 0, 0

            # Percorrendo as sub-listas e ordenando...
            while i < len(esquerda) and j < len(direita):
                if esquerda[i] < direita[j]:
                    # Salva o elemento ordenado na lista
                    lista[k] = esquerda[i]
                    i += 1
                else:
                    lista[k] = direita[j]
                    j += 1
                k += 1

            # Percorrendo o restante da esquerda
            while i < len(esquerda):
                lista[k] = esquerda[i]
                i += 1
                k += 1

            # Percorrendo o restante da direita
            while j < len(direita):
                lista[k] = direita[j]
                j += 1
                k += 1

    def _quickSortAuxiliar(self, lista, prim, ult):

        i = prim
        j = ult

        pivo = lista[(i + j) // 2]

        while i < j:
            while lista[i] < pivo:
                i += 1

            while lista[j] > pivo:
                j -= 1

            if i <= j:
                lista[i], lista[j] = lista[j], lista[i]

                i += 1
                j -= 1

        if j > prim:
            self._quickSortAuxiliar(lista, prim, j)

        if i < ult:
            self._quickSortAuxiliar(lista, i, ult)

    def quickSort(self, lista):
        """Algoritmo de ordenação QuickSort que utiliza a recursão.
        Complexidade do algoritmo: O(n²)

        Args:
            lista (List): lista a ser ordenada
        """

        self._quickSortAuxiliar(lista, 0, len(lista) - 1)

    def heapSort(self, lista):
        """Algoritmo de ordenação HeapSort.
        Complexidade do algoritmo: O(n*log(n))

        Args:
            lista (List): Lista a ser ordenada
        """
        tamanho = len(lista)

        # Construindo uma HEAP-MÁXIMA a partir da lista
        heapMaxima = list(lista)    # Gasto espacial
        # Construção da HEAP-MAXIMA e é devolvida na variável
        heapq.heapify(heapMaxima)

        for i in range(0, tamanho):
            # Remove o elemento da raiz da heap ordenada e coloca na lista
            lista[i] = heapq.heappop(heapMaxima)
