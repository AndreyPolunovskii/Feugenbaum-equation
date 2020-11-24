import numpy as np
from decimal import Decimal

def g(A, x):
    """вычисление фцнкции g"""
    res = 0
    for i, a in enumerate(A[1:]):
        res += a*(x**Decimal(2*i))
    return res


def partial_g(A, x, n):
    """вычисление фцнкции g без слагаемого под номером n"""
    res = 0
    for i, a in enumerate(A[1:]):
        if i != n:
            res += a*(x**Decimal(2*i))
    return res


N = 10

N_iter = 3

#определяем начальные условия
a = np.full(N,Decimal('0'))
a_new = np.full(N,Decimal('0'))
a[0] = Decimal('1')
a[1] = Decimal('-1.5')
a[2] = Decimal('0.1')
a[3] = Decimal('0.026')

alfa = Decimal('2.5029')


x = Decimal('1')

gamma = Decimal('0')


# Пробуем первый быстрый численный алгоритм

for iter in range(N_iter):

    gamma = 0
    for i in range(1,N):
        gamma += a[i] * ( g(a, -x/alfa) ** Decimal(2*i) )

    print('gamma =',gamma)


    for i in range(1,N):
        a_new[i] = - ( alfa + 1 + alfa * gamma +  partial_g(a, x, i) )/ x**Decimal(2*i)

    print('a=',a_new)

    alfa = - Decimal('1')/ ( Decimal('1') + g(a, Decimal('1')) )

    a = a_new 

    print('alfa=',alfa)
    print()
