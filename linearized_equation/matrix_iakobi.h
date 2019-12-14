#ifndef MATRIX_IAKOBI_H
#define MATRIX_IAKOBI_H
#include "basic_include.h"

template <class T>
matrix<T> createIakobi(Feug_function<T> & G,own_funct<T> & H,int N)
{

    matrix<T> Mat(N,N);
    vector<T> X(N+1);

    for (int i = 0; i<= N ; i++)
    {
          X[i] = (T)i/N ;

          Mat.matr2[i][0] = G.g(G.alfa * X[i]) / G.alfa ;
    }

    for (int i = 0; i<= N ; i++)
        for (int j = 1; j<= N ; j++)
        {
            Mat.matr2[i][j] = H.delta * pow(G.alfa * X[i],2*j) / G.alfa - G.diff_g(G.g(X[i])) *pow(X[i],2*j) - pow(G.g(X[i]),2*j);
        }

    return Mat;

}






#endif // MATRIX_IAKOBI_H
