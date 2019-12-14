#ifndef VECTOR_FANCTION_H
#define VECTOR_FANCTION_H
#include "basic_include.h"

template<class T>
vector<T> vect_Funct(Feug_function<T> & G,int N,vector<T> & X,vector<T> & BUF1,vector<T> & BUF2)
{
          vector<T> buf(N+1,0);
          vector <T> BUF3(N+1,1);
          vector <scalar> * buf1_pow = new vector<scalar>(N+1,1);
          vector <scalar> * buf2_pow = new vector<scalar>(N+1,1);
          vector <scalar> * buf3_pow = new vector<scalar>(N+1,1);
          size_t i ;
            
           #pragma omp parallel for private(i)
           for (i = 0; i<= (size_t) N ; i++)
           {
                   BUF1[i] = 1;
                   (*buf1_pow)[i] = 1;
                   
                   BUF3[i] = 1;
                   (*buf3_pow)[i] = 1;
               for (int j = 1;j <= G.N ; j ++ )
                {
                    (*buf1_pow)[i] *= ( X[i]*X[i]  / (G.alfa * G.alfa ) );
                    BUF1[i] += G.a[j]* (*buf1_pow)[i];

                    (*buf3_pow)[i] *= (X[i] * X[i] );
                    BUF3[i] += G.a[j]* (*buf3_pow)[i];
                 }

                  BUF2[i] = 1;
                  (*buf2_pow)[i] = 1;
                for (int j = 1;j <= G.N ; j ++ )
                {
                    (*buf2_pow)[i] *= (BUF1[i] * BUF1[i] );
                    BUF2[i] += G.a[j]* (*buf2_pow)[i];
                 }

               buf[i] =  BUF2[i]*G.alfa  + BUF3[i] ;
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
