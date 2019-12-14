#ifndef VECTOR_FANCTION_H
#define VECTOR_FANCTION_H
#include "basic_include.h"

template<class T>
vector<T> vect_Funct(Feug_function<T> & G,int N,vector<T> & X,vector<T> & BUF1,vector<T> & BUF2)
{
          vector<T> buf(N+1,0);
          size_t i ;
            
           #pragma omp parallel for private(i)
           for (i = 0; i<= (size_t) N ; i++)
           {
               BUF1[i] =  G.g(X[i]/G.alfa) ;
               BUF2[i] =  G.g( BUF1[i] );
               buf[i] =  BUF2[i]*G.alfa  + G.g(X[i]) ;
           }

     return buf;
}

//----------------------------------------------------------------
template<class T>
void output_vector(vector<T> buf)
{
    cout << endl;

    for (int i=0; i < buf.size(); i++)
    {
        cout << buf[i]<<endl;
    }

    cout << endl;
}
//----------------------------------------------------------------
template<class T>
vector<T> minus_vector(vector<T>  buf1,vector<T> buf2 )
{
     vector<T> buf3;


    for (int i=0; i < (int) buf1.size(); i++)
    {
        buf3.push_back(buf1[i] - buf2[i]);
    }
    return buf3;
}



#endif // VECTOR_FANCTION_H
