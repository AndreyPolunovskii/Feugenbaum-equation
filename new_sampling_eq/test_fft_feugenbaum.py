import numpy as np
from scipy.fft import fft, ifft
import matplotlib.pyplot as plt
import cmath
import math
#
N=55


alfa = 2.502929173074250806859646146

I = complex(real=0,imag=1)

# fig, ax = plt.subplots()

def f1(x):
    return 1-1.5*x**2

def f2(x):
    return 1-1.5*np.power(x,2) + 0.1*np.power(x,4) + 0.026*np.power(x,6) - 0.00338*np.power(x,8)

def ff(x):
    return -alfa*f2(f2(x/alfa))

def make_data():
    x = np.arange(-1,1,0.05)
    y = np.arange(-0.3,0.3,0.005)
    xgrid, ygrid = np.meshgrid(x,y)
    zgrid = abs((ff(ff(ff(ff(xgrid+I*ygrid))))))
    print(np.max(zgrid))
    return xgrid, ygrid, zgrid

x, y, z = make_data()

fig, ax = plt.subplots(nrows=1,ncols=2,figsize=(18,5))
ax[0].plot(x[int(len(x)/2)],z[int(len(z)/2)])
ax[1].contourf(x, y, z)
plt.show()


#########
# z0 = np.full(N,complex(real=0,imag=0))
# z1 = np.full(N,complex(real=0,imag=0))
# z2 = np.full(N,complex(real=0,imag=0))

# x0 = np.full(N,float)
# y0 = np.full(N,float)

# x1 = np.full(N,float)
# y1 = np.full(N,float)

# x2 = np.full(N,float)
# y2 = np.full(N,float)

# for i in range(N):
#     z0[i] = cmath.exp(-2*i*I*math.pi/N)
#     z1[i] = f1(cmath.exp(-2*I*i*math.pi/N))
#     z2[i] = f2(cmath.exp(-2*I*i*math.pi/N))


# for i in range(N):
#     x0[i] = z0[i].real
#     y0[i] = z0[i].imag

#     x1[i] = z1[i].real
#     y1[i] = z1[i].imag

#     x2[i] = z2[i].real
#     y2[i] = z2[i].imag


# ax.scatter(x0, y0, c = 'green')
# ax.scatter(x1, y1, c = 'red')
# ax.scatter(x2, y2, c = 'black')

# C = 0.7
# ax.scatter(C*x2, C*y2, c = 'orange')
# B = 0.8
# ax.scatter(B*x2, B*y2, c = 'orange')
# A = 0.9
# ax.scatter(A*x2, A*y2, c = '#fc8d62')
# ax.grid()
# plt.xlabel('X')
# plt.ylabel('Y')
# plt.show()
#############
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
