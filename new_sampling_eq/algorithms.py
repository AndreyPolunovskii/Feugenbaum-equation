import numpy as np
from decimal import Decimal
from scipy.fft import fft, ifft
from global_funcs import N, fft_unique_convolution, invIF, g, diff_g, fft_unique_convolution_range

new_a = np.full(N, complex(real=0, imag=0))
new_a[0] = 1

def algorithm_v1(a, alfa):
    Betta = np.full((N, N), complex(real=0, imag=0))

    betta0 = invIF(fft_unique_convolution(a))
    # print('betta0')
    # print(betta0)
    betta0[0] = 1 # сделано для повышения точности "не точного расчета fft"
    Betta[0] = fft(betta0)

    # по i 100% распараллеливается
    for p in range(1, N):
        for i in range(N):
            Betta[p][i] = pow(Betta[0][i], p+1)


    Betta = np.transpose(Betta)

    # по i 100% распараллеливается
    for i in range(N):
        sum = complex(real=0, imag=0)
        for j in range(1, N):
            sum += float(a[j]) * Betta[i][j-1]
        new_a[i] = float( - alfa ) * sum

    a = invIF(new_a)

    for i in range(2, N):
        a[i] = a[i] / ((- alfa)**(2*i))

    a[0] = 1

    a[1] = -1/alfa - np.sum(a[2:]) - a[0]

    alfa = Decimal('0')

    # по i 100% распараллеливается
    for i in range(1, N):
        alfa -= (2*i) * a[i]
    return a, alfa




def algorithm_v2(a, alfa):
    Betta = np.full((N, N), complex(real=0, imag=0))

    A = fft(a)
    print('fft(a)')
    print(A)

    for i in range(N):
        new_a[i] = a[i] / (- alfa)**(2*i)

    betta0 = invIF( fft_unique_convolution_range(new_a,5) )

    print('betta0 (1 alg)')
    print(betta0)


    betta0 = invIF( fft_unique_convolution_range(a,5) )

    for i in range(N):
        betta0[i] = betta0[i] / ((- alfa)**(2*i))

    print('betta0 (2 alg)')
    print(betta0)

    a_float = list(map(float,a))
    print(-float(alfa)*g(a_float,A[2])/float(alfa)**4)

    exit(0)
    # print(betta0)
    betta0[0] = 1 # сделано для повышения точности "не точного расчета fft"
    Betta[0] = fft(betta0)

    # по i 100% распараллеливается
    for p in range(1, N):
        for i in range(N):
            Betta[p][i] = pow(Betta[0][i], p+1)

    Betta = np.transpose(Betta)

    # по i 100% распараллеливается
    for i in range(N):
        sum = complex(real=0, imag=0)
        for j in range(1, N):
            sum += float(a[j]) * Betta[i][j-1]
        a[i] = float( - alfa ) * sum


    for i in range(2, N):
        a[i] = a[i]

    a[0] = 1

    a[1] = -1/float(alfa) - np.sum(a[2:]) - a[0]


    alfa = 0
    # по i 100% распараллеливается
    for i in range(1, N):
        alfa -= (2*i) * a[i]

    return a, alfa
