from decimal import Decimal
import math
import numpy as np

alfa_1 = Decimal('2.5029078730676846721')

alfa_2 = Decimal('2.5029078750958892708')

alfa_3 = Decimal('2.5029078750958928222')


alfa_Eutken = (alfa_3*alfa_1 - alfa_2**2)/(alfa_1 - 2 * alfa_2 + alfa_3)

#print(alfa_Eutken)


###############################
a = Decimal('2')

def iterat(x_n):
    return (x_n+a/x_n)/Decimal('2')

x0 = Decimal('1')

x1 = iterat(x0)

x2 = iterat(x1)
x3 = iterat(x2)
x4 = iterat(x3)
###############################



def eutken(X):
    return Decimal(X[-1:][0] * X[-3:-2][0] - X[-2:-1][0] ** 2)/(X[-1:][0] - 2 * X[-2:-1][0] + X[-3:-2][0])

def funct(x):
    return Decimal(math.cos(x))
'''
X = []
x0 = Decimal('3')
X.append(x0)
X.append(funct(x0))
X.append(funct(X[1]))
print(eutken(X))
N = 30
for i in range(3,N):
    X.append(funct(X[i-1]))
    print("Еткен : %.20f и без : %.20f" % (eutken(X),X[-1:][0]) )

print(X[-1:])
'''
###########################
#алгоритм подсчета коэффициентов функции Фейгенбаума

N = 5
N_iter = 3

def sum(X,a,b):
    summ = 0
    for i in range(a,b):
        summ += X[i]
    return summ

def scalarmulty(X,Y):
    summ = 0
    for i,x in enumerate(X):
        summ += x*Y[i]
    return summ

#определяем начальные условия
a = np.zeros(N)
a[0] = 1
a[1] = -1.5
a[2] = 0.1
a[3] = 0.026

conv = np.zeros(N)
b = np.zeros((N,N))
b[:,0] = 1
b[0,:] = 1



print('##########################')

# глобальный цикл
for p in range(1,N_iter):
    print('итерация номер %d:\n' % p)
####################
#алгоритм подсчета b - коэффициентов

    for n in range(1,N):
        for r in range(0,N-1):
            for k in range(1,r+1):
                conv[k] = (2*n) * b[n,k] * a[r-k+1] - b[n,r-k+1] * a[k]
#                print(b[n,k],r)
#                print(conv[k],k)
            b[n,r+1] = sum(conv,1,r) + (2*n)*a[r+1]

    print('коэффициенты b:\n')
    print(b)

####################
#алгоритм подсчета a - коэффициентов

    for r in range(1,N):
        a[r] = - scalarmulty(a,b[:,r])/((-(1+sum(a,1,N)))**(2*r-1))

    print('\nкоэффициенты a:\n')
    print(a)
    print('\n##########################\n')


#расходится... так что пользуемся тем что есть)
