import gmpy2
import numpy as np
from gmpy2 import mpc
from scipy.fft import fft, ifft
import matplotlib.pyplot as plt
from matplotlib import cm
from functools import reduce, partial
from algorithms import algorithm_v1
from global_funcs import N, N_iter, fft_unique_convolution, invIF, g , diff_g
from scipy import optimize
import cmath
import math



def MethodN(f,diff_f,x0):
    xn=f(x0)
    xn1=xn-f(xn)/diff_f(xn)
    while abs(xn1-xn)>math.pow(10,-5):
        xn=xn1 #вот так надо было
        xn1=xn-f(xn)/diff_f(xn)
    return xn1





fig, ax = plt.subplots()



#определяем начальные условия
a = np.full(N, mpc('0'))
a_alfa = np.full(N, mpc('0'))

a[0] = mpc('1.00000000000000')
a[1] = mpc('-1.5')
a[2] = mpc('0.1')
a[3] = mpc('0.026')

alfa = mpc('2.50290787509588')

Betta = np.full((N, N), mpc("0"))

mass_alfa = np.full(N, mpc("0"))

x = np.full(N,mpc("0"))
y = np.full(N,mpc("0"))

x_buf = np.full(N,mpc("0"))
y_buf = np.full(N,mpc("0"))

x0 = np.full(N,mpc("0"))
y0 = np.full(N,mpc("0"))

Z0 = np.full(N,mpc("0"))

ZN = np.full(N,mpc("0"))

x_fit = np.full(N,mpc("0"))
y_fit = np.full(N,mpc("0"))

x_res = np.full(N,mpc("0"))
y_res = np.full(N,mpc("0"))

x_alfa = np.full(N,mpc("0"))
y_alfa = np.full(N,mpc("0"))

I = mpc("1j")

prec = 200
gmpy2.get_context().precision = prec
gmpy2.get_context().real_prec = prec
gmpy2.get_context().imag_prec = prec


# Пробуем первый быстрый численный алгоритм

for n_iter in range(N_iter):
    print('############################')


    a1, alfa1 = algorithm_v1(a, alfa)

    a2, alfa2 = algorithm_v1(a1, alfa1)

    # for i in range(1, N):
    #     a[i] = (a2[i]*a[i] - a1[i]**2)/(a2[i]-2*a1[i]+a[i])
    # alfa = (alfa2*alfa-alfa1**2)/(alfa2-2*alfa1+alfa)

    a = a2
    alfa = alfa2
    #вроде сразу не расходится
    print('a')
    print(a)
    print("alfa = ", alfa)
    print('\n')

    #
    # z0 = 1
    # A = -0.65
    # B=1.02
    #
    # z0_alfa = 1.001
    # A_alfa = -4.1
    #
    # for i in range(N):
    #     mass_alfa[i] = ((- alfa)**(2*i))
    #     a_alfa[i] = a[i] * mass_alfa[i]
    #
    # if n_iter == N_iter - 1:
    #     Im = fft(a)
    #     Im_alfa = fft(a_alfa)
    #     Im_mass_alfa = fft(mass_alfa)
    #     print('Im')
    #     print(Im)
    #     print('')
    #     print('Im_mass_alfa')
    #     print(Im_mass_alfa)
    #     print('')
    #     print('sum(Im_mass_alfa)')
    #     sum1 = 0
    #     for i in range(N):
    #         sum1 += (Im_mass_alfa[i])**2
    #     print(sum1)
    #     print('sum(Im)')
    #     print(np.sum(Im))
    #     print('Im_alfa_0')
    #     print(Im_alfa[0])
    #     print('')
    #     print('-alfa*g(a, 1/alfa)')
    #     print(-alfa*g(a, 1/alfa))
    #
    #     print('Корни g')
    #     a_float = list(map(float,a))
    #     g_a = partial(g, a_float)
    #     diff_g_a = partial(diff_g, a_float)
    #
    #     for i in range(N):
    #         Z0[i] = cmath.exp(2*i*math.pi*I/N)
    #         ZN[i] = MethodN(g_a, diff_g_a, Z0[i]* 0.8)
    #         # print(Z0[i], ZN[i])
    #         # print('')
    #     # print(ZN)
    #     # x_zero = MPD(g_a, 0, 1)
    #     # print(x_zero)
    #     # print(g(a,x_zero))
    #
    #     # print('inv_IM_alfa')
    #     # print(inv_Im_alfa(Im_alfa))
    #     # print('')
    #     for i, point in enumerate(Im):
    #         # print(point)
    #         x[i] = point.real
    #         y[i] = point.imag
    #
    #         x_alfa[i] = Im_alfa[i].real
    #         y_alfa[i] = Im_alfa[i].imag
    #
    #         x0[i] = math.cos(2*math.pi*i/N)
    #         y0[i] = math.sin(2*math.pi*i/N)
    #
    #         x_res[i] = point.real
    #         y_res[i] = point.imag
    #
    #         x_fit[i] = A*B*(point.real - z0)
    #         y_fit[i] = A*point.imag
    #
    #     coeff = 0.01
    #     for i in range(N):
    #         for j in range(N):
    #             x0[j] = (Z0[1]*i*coeff).real
    #             y0[j] = (Z0[1]*i*coeff).imag
    #
    #             z_it = -float(alfa)*g_a(g_a(Z0[1]*i*coeff/float(alfa)))
    #             for _ in range(6):
    #                 z_it = -float(alfa)*g_a(g_a(z_it/float(alfa)))
    #
    #             x_buf[j] = z_it.real
    #             y_buf[j] = z_it.imag
    #         ax.scatter(x_buf,y_buf, cmap='Reds')
    #
    #         for j in range(N):
    #             x0[j] = (Z0[6]*i*coeff).real
    #             y0[j] = (Z0[6]*i*coeff).imag
    #
    #             z_it = -float(alfa)*g_a(g_a(Z0[6]*i*coeff/float(alfa)))
    #             for _ in range(6):
    #                 z_it = -float(alfa)*g_a(g_a(z_it/float(alfa)))
    #
    #             x_buf[j] = z_it.real
    #             y_buf[j] = z_it.imag
    #             # print(x0[j],y0[j],x_buf[j],y_buf[j])
    #         # ax.scatter(x0,y0, c='green')
    #         ax.scatter(x_buf,y_buf, c='blue')
    #
    #     # ax.scatter(x, y, c = 'deeppink')
    #     # ax.scatter(x0, y0, c = 'green')
    #     # ax.scatter(x_res, y_res, c = 'red')
    #     # ax.scatter(x_alfa*0.1, y_alfa*0.1, c = 'blue')
    #     # ax.scatter(0, 0, c = 'black')
    #     ax.grid()
    #     plt.xlabel('X')
    #     plt.ylabel('Y')
    #     plt.show()
