import math

# Fórmula pada Número da Página Virtual
# NPV: Número da Página Virtual
def PageNumber(EV, P):
    return (EV//P)

# Fórmula para Deslocamento dentro da Página
# D: deslocamento dentro da Página Virtual
def Displacement(EV, P):
    return (EV % P)

# EV: Endereço Virtual Atual
EV = 20000

# P: Tamanho TOTAL da página
P = 4096

print("\nCONVERSOR MMU FAKE\n")
print(f'Tamanho Total da Página: {P}');
print(f'Numero da Página: {PageNumber(EV, P)}')
print(f'Deslocamento: {Displacement(EV, P)}')
