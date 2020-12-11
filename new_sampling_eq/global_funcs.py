from scipy.fft import fft, ifft
from decimal import Decimal
import numpy as np

N = 20

N_iter = 10

def g(a,x):
    sum = 0
    for i in range(N):
        sum += a[i] * x**(2*i)
    return sum

def diff_g(a,x):
    sum = 0
    for i in range(1,N):
        sum += (2*i) * a[i] * x**(2*i - 1)
    return sum


def convolution(f1,f2,m):
    """расчитываем свертку"""
    res = 0
    for k in range(m+1):
        res += f1[k] * f2[m-k]
    return res

def fft_convolution(f1,f2):
    """расчитываем свертку с помощью fft"""
    return fft(f1)*fft(f2)

def fft_unique_convolution(f1):
    """расчитываем свертку с помощью fft для кварата функции"""
    return pow(fft(f1), 2)

def fft_unique_convolution_range(f1,k):
    """расчитываем свертку с помощью fft для кварата функции"""
    return pow(fft(f1), k)

def invIF(F):
    return np.array(list(map(Decimal, list(map(float, ifft(F))))))

def inv_Im_alfa(Im_alfa):
    mass = np.array(list(map(float,ifft(Im_alfa))))
    for i in range(N):
        mass[i] = mass[i] /(float(- alfa)**(2*i))
    return mass
