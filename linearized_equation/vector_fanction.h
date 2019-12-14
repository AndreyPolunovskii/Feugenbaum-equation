#ifndef VECTOR_FANCTION_H
#define VECTOR_FANCTION_H
#include "basic_include.h"

template<class T>
vector<T> vect_Funct(Feug_function<T> & G,own_funct<T> & H,vector<T> & X,int N,vector<T> & BUF1,vector<T> & BUF2,vector<T> & BUF3)
{
          vector<T> buf(N+1,0);
          vector <T> buf3(N+1,0);
          vector <T> BUF4(N+1,0);
          vector <T> BUF5(N+1,0);

          vector <scalar> * buf1_pow = new vector<scalar>(N+1,1);
          vector <scalar> * buf2_pow = new vector<scalar>(N+1,1);
          vector <scalar> * buf3_pow = new vector<scalar>(N+1,1);
          vector <scalar> * buf4_pow = new vector<scalar>(N+1,1);
          vector <scalar> * buf5_pow = new vector<scalar>(N+1,1);
         
           #pragma omp parallel for
           for (int i = 0; i<= N ; i++)
           {
               BUF1[i] = 1 ;   
               (*buf1_pow)[i] = 1;

               BUF3[i] = 1 ;   
               (*buf3_pow)[i] = 1;

               BUF4[i] = 1 ;   
               (*buf4_pow)[i] = 1;
              
       
                for (int j = 1;j <= G.N ; j ++ )
                {
                    (*buf1_pow)[i] *= ( X[i]*X[i] );
                    BUF1[i] += G.a[j]* (*buf1_pow)[i];
                      
                    (*buf3_pow)[i] *= ( G.alfa * X[i]*G.alfa * X[i] );
                    BUF3[i] += H.h[j]* (*buf3_pow)[i];

                    (*buf4_pow)[i] *= (X[i]*X[i] );
                    BUF4[i] += H.h[j]* (*buf4_pow)[i];


                }

                  buf3[i] = 0;
                 (*buf2_pow)[i] = BUF1[i];

                  BUF5[i] = 1 ;   
                 (*buf5_pow)[i] = 1;
              
                 for (int j = 1;j <= G.N ; j ++ )
                {
                   buf3[i] += (2*j) * G.a[j]* (*buf2_pow)[i];
                   (*buf2_pow)[i] *= ( BUF1[i] * BUF1[i] );

                   (*buf5_pow)[i] *= ( BUF1[i] * BUF1[i] );
                   BUF5[i] += H.h[j]* (*buf5_pow)[i];

                }

            //   BUF1[i] = G.g(X[i]);
               BUF2[i] = buf3[i]; //G.diff_g(BUF1[i]);
               BUF3[i] = BUF3[i] / G.alfa;  // H.H(G.alfa * X[i]) / G.alfa;
             //  BUF4[i] = H.H(X[i]);
             //  BUF5[i] = H.H(BUF1[i]);


               buf[i] = H.delta *BUF3[i] - BUF2[i] * BUF4[i] - BUF5[i];
           }


    buf1_pow->clear();
    buf2_pow->clear();
    buf3_pow->clear();
    buf4_pow->clear();
    buf5_pow->clear();

    buf3.clear();
    BUF4.clear();
    BUF5.clear();

   

     return buf;
}

//----------------------------------------------------------------
template<class T>
void output_vector(vector<T> & buf)
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
vector<T> minus_vector(vector<T>  buf1,vector<T> & buf2 )
{
     vector<T> buf3;

    for (int i=0; i < buf1.size(); i++)
    {
        buf3.push_back(buf1[i] - buf2[i]);
    }
    return buf3;
}



#endif // VECTOR_FANCTION_H
