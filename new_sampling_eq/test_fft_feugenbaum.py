import numpy as np
from scipy.fft import fft, ifft
import matplotlib.pyplot as plt
import cmath
import math
#
N=55

fig, ax = plt.subplots()

def f1(x):
    return 1-1.5*x**2

def f2(x):
    return 1-1.5*x**2 + 0.1*x**4 + 0.026*x**6 - 0.00338*x**8


I = complex(real=0,imag=1)

z0 = np.full(N,complex(real=0,imag=0))
z1 = np.full(N,complex(real=0,imag=0))
z2 = np.full(N,complex(real=0,imag=0))

x0 = np.full(N,float)
y0 = np.full(N,float)

x1 = np.full(N,float)
y1 = np.full(N,float)

x2 = np.full(N,float)
y2 = np.full(N,float)

for i in range(N):
    z0[i] = cmath.exp(-2*i*I*math.pi/N)
    z1[i] = f1(cmath.exp(-2*I*i*math.pi/N))
    z2[i] = f2(cmath.exp(-2*I*i*math.pi/N))


for i in range(N):
    x0[i] = z0[i].real
    y0[i] = z0[i].imag

    x1[i] = z1[i].real
    y1[i] = z1[i].imag

    x2[i] = z2[i].real
    y2[i] = z2[i].imag


ax.scatter(x0, y0, c = 'green')
ax.scatter(x1, y1, c = 'red')
ax.scatter(x2, y2, c = 'black')

# C = 0.7
# ax.scatter(C*x2, C*y2, c = 'orange')
# B = 0.8
# ax.scatter(B*x2, B*y2, c = 'orange')
# A = 0.9
# ax.scatter(A*x2, A*y2, c = '#fc8d62')
ax.grid()
plt.xlabel('X')
plt.ylabel('Y')
plt.show()

#
# z0 = 1.1
# kx = 1.50
# ky = 1.57
#
# I = complex(real=0,imag=1)
#
# #определяем начальные условия
# a = np.full(N, complex(real=0,imag=0))
#
# Fa = np.full(N, complex(real=0,imag=0))
#
#
# #заполняем Fa
# for i in range(N):
#     Fa[i] = z0 + kx*math.cos(2*math.pi*i/N) -I*ky*math.sin(2*math.pi*i/N)
#
# print(Fa)
