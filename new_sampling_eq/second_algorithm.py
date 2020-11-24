import numpy as np
from decimal import Decimal

def convolution(f1,f2,m):
    """расчитываем свертку"""
    res = 0
    for k in range(m+1):
        # print(f1[k] * f2[m-k],k,m-k)
        res += f1[k] * f2[m-k]
    return res

N = 4

N_iter = 130

#определяем начальные условия
a = np.full(N,Decimal('0'))
new_a = np.full(N,Decimal('0'))
new_a[0] = Decimal('1')
a[0] = Decimal('1.00000000000000')
a[1] = Decimal('-1.5')
a[2] = Decimal('0.1')
a[3] = Decimal('0.026')

alfa = Decimal('2.5029')

betta = np.full((N, N), Decimal('0'))


# Пробуем первый быстрый численный алгоритм

for _ in range(N_iter):
    print('############################')

    betta = np.full((N, N), Decimal('0'))
    for i in range(N):
        betta[i][0] = Decimal('1')


    a[1] = -1/alfa - sum(a[2:]) - a[0]

    for m in range(1, N):
        betta[0][m] = convolution(a, a, m)/ ((- alfa)**(2*m+2))

    print(betta[0])
    print('\n')

    for p in range(N - 1):
        for m in range(1, N):
            betta[p+1][m] = convolution(betta[p], betta[0], m)

    print(betta)
    print('\n')

    betta = np.transpose(betta)


    for i in range(2, N):
        new_a[i] = - alfa * np.dot(a, betta[i])

    a = np.concatenate((np.array([Decimal('1'), a[1]]), new_a[2:]),axis=0)

    alfa = Decimal('0')
    for i in range(1, N):
        alfa -= (2*i) * a[i]


    print(a)
    print(alfa)
    print('\n')
