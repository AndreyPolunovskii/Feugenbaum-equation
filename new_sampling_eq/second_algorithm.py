import numpy as np
from scipy.fft import fft, ifft
from decimal import Decimal

def convolution(f1,f2,m):
    """расчитываем свертку"""
    res = 0
    for k in range(m+1):
        res += f1[k] * f2[m-k]
    return res


N = 14

N_iter = 100

#определяем начальные условия
a = np.full(N,Decimal('0'))
new_a = np.full(N,Decimal('0'))
new_a[0] = Decimal('1')
a[0] = Decimal('1.00000000000000')
a[1] = Decimal('-1.5')
a[2] = Decimal('0.1')
a[3] = Decimal('0.026')

alfa = Decimal('2.50290787509588')

betta = np.full((N, N), Decimal('0'))


for _ in range(N_iter):
    print('############################')

    betta = np.full((N, N), Decimal('0'))

    for m in range(N):
        betta[0][m] = convolution(a, a, m)

    for p in range(N - 1):
        for m in range(N):
            betta[p+1][m] = convolution(betta[p], betta[0], m)


    betta = np.transpose(betta)

    for i in range(2, N):
        sum = 0
        for j in range(1, N):
            sum += a[j] * betta[i][j-1]
        new_a[i] =  - alfa  * sum / ((- alfa)**(2*i))


    a = new_a

    a[1] = -1/alfa - np.sum(a[2:]) - a[0]

    alfa = Decimal('0')
    for i in range(1, N):
        alfa -= (2*i) * a[i]

    print("alfa = ", alfa)
    print('\n')
