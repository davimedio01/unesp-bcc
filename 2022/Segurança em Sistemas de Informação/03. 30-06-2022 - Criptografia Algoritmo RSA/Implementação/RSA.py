import random
from math import sqrt

'''
Calcula o totiente do numero primo
'''
def totient(number):
    if(prime(number)):
        return number - 1
    else:
        return False


'''
Verifica se um numero gerado é primo
'''
def prime(n):
    
    # Corner cases
    if(n <= 1):
        return False
    
    for i in range(2, int(sqrt(n)) + 1):
        if(n % i == 0):
            return False
    
    return True


'''
Gera um numero aleatório E, satisfazendo as condições
'''
def generate_E(num):
    def mdc(n1, n2):
        rest = 1
        while(n2 != 0):
            rest = n1 % n2
            n1 = n2
            n2 = rest
        return n1

    while True:
        e = random.randrange(2, num)
        if(mdc(num, e) == 1):
            return e


'''
Gera um numero primo aleatório
'''
def generate_prime():  # generate the prime number - p e q
    while True:  # 2**2048 is the RSA standart keys
        x = random.randrange(1, 1000)  # define the range of the primes
        if(prime(x) == True):
            return x


'''
Função modular entre dois números
'''
def mod(a, b):  # mod function
    if(a < b):
        return a
    else:
        c = a % b
        return c


'''
Cifra um texto
'''
def cipher(words, e, n):  # get the words and compute the cipher
    tam = len(words)
    i = 0
    lista = []
    while(i < tam):
        letter = words[i]
        k = ord(letter)
        k = k**e
        d = mod(k, n)
        lista.append(d)
        i += 1
    return lista


'''
Descriptografa um texto criptografado
'''
def decipher(cifra, n, d):
    lista = []
    i = 0
    tamanho = len(cifra)
    # texto=cifra ^ d mod n
    while i < tamanho:
        result = cifra[i]**d
        texto = mod(result, n)
        letra = chr(texto)
        lista.append(letra)
        i += 1
    return lista


'''
Calcula a chave privada
'''
def calculate_private_key(toti, e):
    d = 0
    while(mod(d*e, toti) != 1):
        d += 1
    return d


## MAIN
if __name__ == '__main__':

    text = input("Insert message (ASCII): ")

    p = generate_prime()          # generates random P
    q = generate_prime()          # generates random Q
    n = p*q                       # compute N
    y = totient(p)                # compute the totient of P
    x = totient(q)                # compute the totient of Q
    totient_de_N = x*y            # compute the totient of N
    e = generate_E(totient_de_N)  # generate E

    public_key = (n, e)
    print('Your public key:', public_key)

    text_cipher = cipher(text, e, n)
    print('Your encrypted message:', text_cipher)

    d = calculate_private_key(totient_de_N, e)
    print('Your private key is:', d)

    original_text = decipher(text_cipher, n, d)
    print('Your original message:', original_text)
