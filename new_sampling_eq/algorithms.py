import numpy as np
from gmpy2 import mpc
from scipy.fft import fft, ifft
from global_funcs import N, fft_unique_convolution, invIF, g, diff_g, fft_unique_convolution_range, my_fft, my_ifft

new_a = np.full(N, mpc("0"))
new_a[0] = mpc("1")

def algorithm_v1(a, alfa):
    Betta = np.full((N, N), complex(real=0, imag=0))

    betta0 = my_ifft(fft_unique_convolution(a))

    # print('betta0')
    # print(betta0)
    betta0[0] = 1 # сделано для повышения точности "не точного расчета fft"
    Betta[0] = my_fft(betta0)

    # по i 100% распараллеливается
    for p in range(1, N):
        for i in range(N):
            Betta[p][i] = pow(Betta[0][i], p+1)


    Betta = np.transpose(Betta)

    # по i 100% распараллеливается
    for i in range(N):
        sum = mpc("0")
        for j in range(1, N):
            sum += a[j] * Betta[i][j-1]
        new_a[i] =  - alfa  * sum

    a = my_ifft(new_a)

    for i in range(2, N):
        a[i] = a[i] / ((- alfa)**(2*i))

    a[0] = 1

    a[1] = -1/alfa - np.sum(a[2:]) - a[0]

    alfa = mpc("0")

    # по i 100% распараллеливается
    for i in range(1, N):
        alfa -= (2*i) * a[i]
    return a, alfa
