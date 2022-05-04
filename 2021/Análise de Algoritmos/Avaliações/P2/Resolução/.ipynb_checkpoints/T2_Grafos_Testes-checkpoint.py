# Importação da Classe "Ordenacao" para uso das funções estabelecidas no outro arquivo
from T1_Ordenacao import Ordenacao

import random
import time


def geraLista(limiteSuperior, ordenado=True):
    """
        Função para gerar uma lista, ordenada ou aleatória, de tamanho especificado e
        contendo elementos de 0 a um limite superior
    """
    lista = list(range(0, limiteSuperior))  # Geração da lista ordenada

    # Caso seja pra lista ser aleatória
    if ordenado == False:
        random.shuffle(lista)

    return lista


def printaLista(lista, tempoProcesso=0.0, tipo=True):
    """
        Função simples para printar uma lista,
        limitando-se nos primeiros cinco e nos últimos cinco elementos

        Além disso, mostra também o tempo de processamento do algoritmo...
    """

    tamanho = len(lista)  # Tamanho da lista

    # Manipular a lista no caso do tamanho ser maior que 10
    if tamanho > 10:
        esquerda = [i for i in lista[0:5]]
        direita = [i for i in lista[-5:]]

        lista = esquerda + ['...'] + direita

    # O tipo define se a lista é ordenada ou não: True - Antes da Ordenação; False - Depois da Ordenação
    if tipo == True:
        print(f'Lista antes da ordenação: {lista}')
    else:
        print(f'Lista depois da ordenação: {lista}\n')
        print(f'Tempo de Processamento: {tempoProcesso:0.4f} milissegundos (ms)\n')


def executaOrdenacao(algOrd, lista):

    printaLista(lista)

    t0 = time.perf_counter()

    algOrd(lista)

    t1 = time.perf_counter()

    tempoTotal = (t1 - t0) * 1000

    printaLista(lista, tempoTotal, False)


"""
-----------------------------------------------------
"""

"""
    TAMANHO: N = 10
"""
tamanho = 10

"""
    TIPO: NÃO ORDENADO
"""
tipo = False

"""
    ALGORITMO: BUBBLESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().bubbleSort, lista)

"""
    ALGORITMO: INSERTIONSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().insertionSort, lista)

"""
    ALGORITMO: MERGESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().mergeSort, lista)

"""
    ALGORITMO: QUICKSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().quickSort, lista)

"""
    ALGORITMO: HEAPSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().heapSort, lista)

"""
    TIPO: ORDENADO
"""
tipo = True

"""
    ALGORITMO: BUBBLESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().bubbleSort, lista)

"""
    ALGORITMO: INSERTIONSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().insertionSort, lista)

"""
    ALGORITMO: MERGESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().mergeSort, lista)

"""
    ALGORITMO: QUICKSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().quickSort, lista)

"""
    ALGORITMO: HEAPSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().heapSort, lista)

"""
-----------------------------------------------------
"""

"""
    TAMANHO: N = 100
"""
tamanho = 100

"""
    TIPO: NÃO ORDENADO
"""
tipo = False

"""
    ALGORITMO: BUBBLESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().bubbleSort, lista)

"""
    ALGORITMO: INSERTIONSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().insertionSort, lista)

"""
    ALGORITMO: MERGESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().mergeSort, lista)

"""
    ALGORITMO: QUICKSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().quickSort, lista)

"""
    ALGORITMO: HEAPSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().heapSort, lista)

"""
    TIPO: ORDENADO
"""
tipo = True

"""
    ALGORITMO: BUBBLESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().bubbleSort, lista)

"""
    ALGORITMO: INSERTIONSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().insertionSort, lista)

"""
    ALGORITMO: MERGESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().mergeSort, lista)

"""
    ALGORITMO: QUICKSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().quickSort, lista)

"""
    ALGORITMO: HEAPSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().heapSort, lista)

"""
-----------------------------------------------------
"""

"""
    TAMANHO: N = 1000
"""
tamanho = 1000

"""
    TIPO: NÃO ORDENADO
"""
tipo = False

"""
    ALGORITMO: BUBBLESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().bubbleSort, lista)

"""
    ALGORITMO: INSERTIONSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().insertionSort, lista)


"""
    ALGORITMO: MERGESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().mergeSort, lista)

"""
    ALGORITMO: QUICKSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().quickSort, lista)

"""
    ALGORITMO: HEAPSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().heapSort, lista)

"""
    TIPO: ORDENADO
"""
tipo = True

"""
    ALGORITMO: BUBBLESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().bubbleSort, lista)

"""
    ALGORITMO: INSERTIONSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().insertionSort, lista)


"""
    ALGORITMO: MERGESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().mergeSort, lista)


"""
    ALGORITMO: QUICKSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().quickSort, lista)


"""
    ALGORITMO: HEAPSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().heapSort, lista)


"""
-----------------------------------------------------
"""

"""
    TAMANHO: N = 10000
"""
tamanho = 10000

"""
    TIPO: NÃO ORDENADO
"""
tipo = False

"""
    ALGORITMO: BUBBLESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().bubbleSort, lista)

"""
    ALGORITMO: INSERTIONSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().insertionSort, lista)

"""
    ALGORITMO: MERGESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().mergeSort, lista)

"""
    ALGORITMO: QUICKSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().quickSort, lista)

"""
    ALGORITMO: HEAPSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().heapSort, lista)

"""
    TIPO: ORDENADO
"""
tipo = True

"""
    ALGORITMO: BUBBLESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().bubbleSort, lista)

"""
    ALGORITMO: INSERTIONSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().insertionSort, lista)

"""
    ALGORITMO: MERGESORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().mergeSort, lista)

"""
    ALGORITMO: QUICKSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().quickSort, lista)

"""
    ALGORITMO: HEAPSORT
"""
lista = geraLista(tamanho, tipo)
executaOrdenacao(Ordenacao().heapSort, lista)
