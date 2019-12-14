#ifndef MATRIX_H
#define MATRIX_H




//--------------------------------------

template <class T>
class matrix
{
public:

    int x_count;
    int y_count;

    T ** matr2;



//------------------------------------
    matrix(int x_count1 ,int y_count1 )
    {

            x_count = x_count1;
            y_count = y_count1;

            matr2 = new T* [x_count+1];

             for (size_t i = 0 ; i <= (size_t) x_count ; ++i)
                    matr2[i] = new T [y_count+1];


             for (size_t i=0 ; i <= (size_t) x_count ; ++i)
                       for (size_t j=0; j <= (size_t) y_count; ++j)
                        {
                                      matr2[i][j] = 0;
                         }
    }
//-----------------------------------------
   void  init_cound1()
    {

                        for (size_t i=0; i <= (size_t) x_count; ++i)
                            for (size_t j=0; j <= (size_t) y_count; ++j)
                            {
                               if (i == j)
                                   matr2[i][j] = 1;
                                    else
                                         matr2[i][j] = 0;
                            }

    }
 //------------------------------------------
  void  init_zero()
    {

                        for (size_t i=0; i <= (size_t) x_count; ++i)
                            for (size_t j=0; j <= (size_t) y_count; ++j)
                            {
                                         matr2[i][j] = 0;
                            }

    }
 //-------------------------------------------
    void  init_cound2()
    {

                        for (size_t i=0; i <= (size_t) x_count; ++i)
                            for (size_t j=0; j <= (size_t) y_count; ++j)
                            {
                                matr2[i][j] = i+j;
                            }

    }
//---------------------------------------------
    void  init_cound3()
    {

        matr2[0][0] = -2.51714;
        matr2[0][1] = 0.99748;
        matr2[0][2] = 0.4361901;
        matr2[0][3] = -0.231307e-1;
        matr2[0][4] = 0.00131438;

        matr2[1][0] = 1.1491064;
        matr2[1][1] = -2.0906919;
        matr2[1][2] = 0.361972742;
        matr2[1][3] = -0.4800464e-1;
        matr2[1][4] = 0.0033441;

        matr2[2][0] = -1.57027847;
        matr2[2][1] = 2.33492;
        matr2[2][2] = -.825639;
        matr2[2][3] = 0.124509;
        matr2[2][4] = -0.90806e-2;

        matr2[3][0] = 0.4657332;
        matr2[3][1] = -.7044025;
        matr2[3][2] = 0.3210481;
        matr2[3][3] = -0.7649583e-1;
        matr2[3][4] = 0.0063562;

        matr2[4][0] = -0.40220e-1;
        matr2[4][1] = 0.06217180;
        matr2[4][2] = -0.3142167e-1;
        matr2[4][3] = 0.0092206;
        matr2[4][4] = -0.114418e-2;



    }
//---------------------------------------------
    void init_taylor(matrix<T> & A, T relax_coeff,int col_it)
    {
        matrix<T> prob(A.x_count,A.y_count);
        matrix<T> F(A.x_count,A.y_count);

        matrix<scalar> unitMat(A.x_count,A.y_count);
        unitMat.init_cound1();

        prob =  A * relax_coeff - unitMat ;

        cout << "norm preinitial_cond_matrix = " << prob.matrix_norm() << endl;
     

        F += unitMat;

        for (int k =1 ; k <= col_it; k++ )
        {
            F +=  prob.Pow(k) * pow(-1,k);
        }

        *this = F * relax_coeff;

    }
//--------------------------------------------
  void init_rand(matrix<T> & A,matrix<T> & unitMat)
{
          int first_value = -2; 
          int last_value = 5; 
     
  
   matrix<T> Phi(A.x_count,A.y_count);
   matrix<T> Buf(A.x_count,A.y_count);

   Phi = unitMat - A * Buf ;
   
  while (1)
  {
   srand( time(0) );
   for (size_t i=0; i <= (size_t) x_count; ++i)
         for (size_t j=0; j <= (size_t) y_count; ++j)
              {
                Buf.matr2[i][j] = first_value + abs(sin( rand() )) * last_value;
              }
   
    Phi = unitMat - A * Buf ;
    cout << " невязка = " <<  Phi.matrix_norm() << endl;    

   if ( Phi.matrix_norm() < 1 )
            break;
   }
   
   *this = Buf;

}
//--------------------------------------------
  void init_unit(T scalar)
{
   this->init_cound1();
   *this = (*this) * scalar;
}
//---------------------------------------------
   void diag(T coeff = "1")
    {
 

                        for (size_t i=0; i <= (size_t) x_count; ++i)
                            for (size_t j=0; j <= (size_t) y_count; ++j)
                            {
                               if (i == j)
                                   matr2[i][j] = coeff;
                                    else
                                         matr2[i][j] = 0;
                            }

    }
//---------------------------------------------
  void init_tr(matrix<T> & A,T scalar)
{
    *this = A;
    this->transpose_matrix();

   *this = (*this) * scalar;
}
//---------------------------------------------
  void init_inv_tr(matrix<T> & A,T scalar)
{
    for (size_t i=0; i <= (size_t) x_count; ++i)
        for (size_t j=0; j <= (size_t) y_count; ++j)
               matr2[i][j] = 1/A.matr2[i][j];

    this->transpose_matrix();

   *this = (*this) * scalar;
}
//---------------------------------------------
void init_transp(matrix<T> & A)
{
    matrix<T> unit(x_count,y_count);
    matrix<T> buf(x_count,y_count);
    scalar init_param = 0;
    unit.init_cound1();
    
  
    buf = A;
    buf.transpose_matrix();
   // init_param = 1 / (A * buf).matrix_norm();
    init_param = 1.4 / ( pow( (A).matrix_norm() ,2)  );
   

    cout << "ралксационный параметр для начальной матрицы " << endl;
    cout << init_param << endl;
    cout << endl;

  //  matrix<T> unitd(x_count,y_count);
   // unitd.diag();

    *this = buf * init_param;//unitd *init_param ; 
}
//--------------------------------------------

matrix<T> init_inv_diag(matrix<T> & A)
{
     matrix<T> R(x_count,y_count);

                       for (size_t i=0; i <= (size_t) x_count; ++i)
                            for (size_t j=0; j <= (size_t) y_count; ++j)
                            {
                                         if (i == j)
                                   matr2[i][j] = 1/A[i][j];
                                    else
                                         matr2[i][j] = 0;
                            }
     return R;
}
//--------------------------------------------
vector<T> Gauss_Zeudel(matrix<T> & A,vector<T> b,int N,int iter)
{
 
 vector<T> p(N+1,0);
 vector<T> x(N+1,0);
 T omega = 1.9;  

for (int k = 0 ; k < iter; k++)
{
    for (int i = 0; i <= N; i++)
        p[i] = x[i];
    for (int i = 0; i <= N; i++)
    {
        T var = 0;
        for (int j = 0; j < i; j++)
            var += (A.matr2[i][j] * x[j]);
        for (int j = i + 1; j <= N; j++)
            var += (A.matr2[i][j] * p[j]);
        x[i] = (b[i] - var) / A.matr2[i][i];
    }

    for (int i = 0; i <= N; i++)
        x[i] = omega * x[i] + (1- omega) *p[i];
    

}

return x;

}
//--------------------------------------------
void init_gauss_Zeudel(matrix<T> & A)
{
    matrix<T> A_sym(x_count,y_count);
    matrix<T> A_transp(x_count,y_count);
    vector<T> B(x_count+1,0);

   A_transp = A;
   A_transp.transpose_matrix();
   A_sym =  A_transp * A ;     


   for (int i1 = 0; i1 <= y_count ; i1++)
    {
               B[i1] = 1;
         this->add_column( Gauss_Zeudel(A_sym,A_transp*B,A.x_count,40500) ,i1 );
               B[i1] = 0;
    }
    
}
//--------------------------------------------
void add_column(vector<T>  col, int n)
{
    for (size_t i=0; i <= (size_t) x_count; ++i)
                matr2[i][n] = col[i];
}
//-------------------------------------------
void add_line(vector<T>  col, int n)
{
    for (size_t i=0; i <= (size_t) x_count; ++i)
                matr2[n][i] = col[i];
}
//--------------------------------------------
void init_LU(matrix<T> & A)
{
   matrix<T> * L = new matrix<T>(x_count,y_count);   
   matrix<T> * R = new matrix<T>(x_count,y_count);
   matrix<T> buf(x_count,y_count); 
   matrix<T> unit(x_count,y_count);
   unit.init_cound1();

   LU(A,L,R);

     #pragma omp parallel for 
    for (int i1 = 0; i1 <= y_count ; i1++)
       buf.add_column(  solve_L_B_eq(L,unit.output_column(i1)) ,i1);
   
    #pragma omp parallel for 
    for (int i1 = 0; i1 <= y_count ; i1++)
      this->add_column(  solve_R_B_eq(R,buf.output_column(i1)) ,i1);
     

}
//--------------------------------------------
void LU(matrix<T> * L)
{
    

        #pragma omp parallel for 
	for(int i = 0; i <=x_count; i++)
        {
		for(int j = i; j <= x_count; j++)
			L->matr2[j][i]=matr2[j][i]/matr2[i][i];
        }

     

	for(int k = 1; k <= x_count; k++)
	{
                #pragma omp parallel for
		for(int i = k-1; i <= x_count; i++)
			for(int j = i; j <= x_count; j++)
				L->matr2[j][i]=matr2[j][i]/matr2[i][i];
           
                 #pragma omp parallel for
		for(int i = k; i <= x_count; i++)
			for(int j = k-1; j <= x_count; j++)
				matr2[i][j]=matr2[i][j]-(*L)[i][k-1]*matr2[k-1][j];
	}
}
//----------------------------------------------
vector<T> solve_L_B_eq(matrix<T> * L,vector<T> B)
{
   vector<T> X(L->x_count+1 ,0);

   X[0] = B[0]/(*L)[0][0];

        for (size_t i=1; i <= (size_t) L->x_count; ++i)
        {
             X[i] = B[i];
              for (size_t j=0; j < i; ++j)
                X[i] -=  (*L)[i][j] *X[j];
              X[i] = X[i]/(*L)[i][i];
        }
     return X;
}
//---------------------------------------------
vector<T> solve_R_B_eq(vector<T> B)
{
  int n =x_count;

   vector<T> X(n+1,0);

   X[n] = B[n]/matr2[n][n];

        for (size_t i=1; i <= (size_t) n; ++i)
        {
             X[n-i] = B[n-i];
              for (size_t j=n-i+1; j <= n; ++j)
                X[n-i] -=  matr2[n-i][j] *X[j];
              X[n-i] = X[n-i]/matr2[n-i][n-i];
        }
     return X;


}
//----------------------------------------------
vector<T> output_column(int n)
{
   vector<T> buf(x_count+1,0);

   for (size_t i=0; i<=(size_t) x_count; ++i)
   {
        buf[i] = matr2[i][n]; 
    }
  return buf;

}
//----------------------------------------------
void init_pro_transp(matrix<T> & A,int m)
{
    matrix<T> unit(x_count,y_count);
    matrix<T> buf(x_count,y_count);
    matrix<T> phi(x_count,y_count);
    matrix<T> SUM_phi(x_count,y_count);
    scalar init_param = 0;
    unit.init_cound1();
    SUM_phi.init_cound1();
    
  
    buf = A;
    buf.transpose_matrix();
    init_param = 1 / (A * buf).matrix_norm();

    phi = unit -  A * buf *init_param ;

   for (int i = 1 ;i<m ;i++)
        SUM_phi += phi.Pow(i);

    cout << "ралксационный параметр для начальной матрицы " << endl;
    cout << init_param << endl;
    cout << endl;

    *this = buf * SUM_phi * init_param;//unitd *init_param ; 
}
//---------------------------------------------
void transpose_matrix()
{
  T t = 0;


    for (size_t i=0; i <= (size_t) x_count; ++i)
        for (size_t j=i; j <= (size_t) y_count; ++j)
          {
            t = matr2[j][i] ;
            matr2[j][i] = matr2[i][j];
            matr2[i][j] = t;
          }

}
//---------------------------------------------
T matrix_trace()
{
  T trace = 0;
 

   for (size_t i=0; i <= (size_t) x_count; ++i)
          trace += matr2[i][i];


 return trace ;
}
//---------------------------------------------
T matrix_norm()
{
  T norm = 0;
 
  
   for (size_t i=0; i <= (size_t) x_count; ++i)
      for (size_t j=0; j <= (size_t) y_count; ++j)
      {
          norm += pow(matr2[i][j],2);
      }

 return sqrt( norm ) ;
}
//---------------------------------------------
T matrix_norm_inf()
{
  T max = 0;
 
  
   for (size_t i=0; i <= (size_t) x_count; ++i)
      for (size_t j=0; j <= (size_t) y_count; ++j)
      {
           if ( abs(matr2[i][j]) > max ) 
                       max = abs(matr2[i][j]);
      }

 return max ;
}
//---------------------------------------------
    matrix<T> operator+(const matrix<T> & matr21) const
{
    matrix<T> Mat(x_count,y_count);
    size_t i,j;
                    
                    #pragma omp parallel for private(i,j)
                    for (i=0; i <= (size_t) x_count; ++i)
                        for (j=0; j <= (size_t) y_count; ++j)
                        {
                            Mat.matr2[i][j] = matr21.matr2[i][j] + matr2[i][j];
                        }
          return  Mat;
}
//-----------------------------------------------
   matrix<T> & operator+=(const matrix<T> & matr21)
{
   size_t i,j;

                    #pragma omp parallel for private(i,j)
                    for (i=0; i <= (size_t) x_count; ++i)
                        for (j=0; j <= (size_t) y_count; ++j)
                        {
                            matr2[i][j] = matr21.matr2[i][j] + matr2[i][j];
                        }

              return *this;
}
//-----------------------------------------------
    matrix<T> operator-(const matrix<T> & matr21) const
    {
        matrix<T> Mat(x_count,y_count);
        size_t i,j;

                        #pragma omp parallel for private(i,j)
                        for (i=0; i <= (size_t) x_count; ++i)
                            for (j=0; j <= (size_t) y_count; ++j)
                            {
                                Mat.matr2[i][j] = matr2[i][j] - matr21.matr2[i][j];
                            }
              return  Mat;
    }
//---------------------------------------------------
    matrix<T> & operator=(const matrix<T> & matr21)
    {

    size_t i,j;

                #pragma omp parallel for private(i,j)
                for (i=0; i <= (size_t) x_count; ++i)
                    for (j=0; j <= (size_t) y_count; ++j)
                            {
                                matr2[i][j] = matr21.matr2[i][j];
                            }
            return *this;
    }
//----------------------------------------------------

    matrix<T> operator/(const T & scal) const
    {
        matrix<T> Mat(x_count,y_count);
        size_t i,j;

                        #pragma omp parallel for private(i,j)
                        for (i=0; i <= (size_t) x_count; ++i)
                            for (j=0; j <= (size_t) y_count; ++j)
                            {
                                Mat.matr2[i][j] = matr2[i][j]/scal;
                            }
              return  Mat;
    }
//---------------------------------------------------
    matrix<T> operator*(const matrix<T> & matr21) const
    {
        matrix<T> Mat(x_count,y_count);
        size_t i,j,k; 

               #pragma omp parallel for private(i,j,k)
               for (i=0; i <= (size_t) x_count; ++i)
                     for (j=0; j <= (size_t) y_count; ++j)
                      {
                          for(k=0; k <= (size_t) y_count; k++)
                            Mat.matr2[i][j] += matr2[i][k] * matr21.matr2[k][j] ;
                      }
        return  Mat;
    }
 //----------------------------------------------------
    vector<T> operator*(const vector<T> & vect) const
    {
        vector<T> buf(x_count+1,0);
        size_t i,k;

               #pragma omp parallel for private(i,k)
               for (i=0; i <= (size_t) x_count; ++i)
                          for(k=0; k <= (size_t) y_count; k++)
                            buf[i] += matr2[i][k] * vect[k] ;

        return  buf;
    }
//-----------------------------------------------------
    matrix<T> operator*(const T & scalar) const
    {
       matrix<T> Mat(x_count,y_count);
       size_t i,j;

        #pragma omp parallel for private(i,j)
        for (i=0; i <= (size_t) x_count; ++i)
              for (j=0; j <= (size_t) y_count; ++j)
                            Mat[i][j] = matr2[i][j] * scalar ;

        return  Mat;
    }
//---------------------------------------------------
    matrix<T> Pow(int n)
    {
        matrix<T> prob(x_count,y_count);
        prob.init_cound1();

             for (int i=0 ; i< n ;i ++)
                      prob = prob * (*this);
        return prob;
    }

//---------------------------------------------------
  T * operator[](int i){ return matr2[i]; }
//-------------------------------------------------------
void createIakobi(Feug_function<T> & G,int N,vector<T> & X,T  delta ,vector<T> & BUF1,vector<T> & BUF2, vector<T> & BUF3) 
{
   size_t i,j;

   vector <T> buf3(N+1,0);
   vector <T> buf4(N+1,0);
   vector <scalar> * BUF1_pow = new vector<scalar>(N+1,1);
   vector <scalar> * BUF2_pow = new vector<scalar>(N+1,1);
   vector <scalar> * BUF3_pow = new vector<scalar>(N+1,1);
   vector <scalar> * BUF4_pow = new vector<scalar>(N+1,1);
   vector <scalar> * BUF5_pow = new vector<scalar>(N+1,1);

    #pragma omp parallel for private(i,j)
    for (i = 0; i<= N ; i++)
    {     

        matr2[i][0] = BUF3[i]  ;
       
        for (j = 1; j<= N ; j++)
        {
          (*BUF2_pow)[i] *= BUF1[i]* BUF1[i];
          (*BUF3_pow)[i] *= X[i]*X[i];
          (*BUF1_pow)[i] *= ( X[i]*X[i]  * G.alfa * G.alfa  );           

          matr2[i][j] = delta * (*BUF1_pow)[i] / G.alfa - BUF2[i] * (*BUF3_pow)[i] -  (*BUF2_pow)[i];
 
  
             
        }
    }     

    buf3.clear();
    buf4.clear();

    BUF1_pow->clear();
    BUF2_pow->clear();
    BUF3_pow->clear();
    BUF4_pow->clear();
    BUF5_pow->clear();


}
//-------------------------------------------------------
     ~matrix()
     {
              for (size_t i=0 ; i <= (size_t) x_count  ; ++i)
                     delete [] matr2[i];

         delete [] matr2;

     }
//-------------------------------------------------------
       void output_matrix(int count_num)
       {

           cout.setf(ios_base::fixed,ios_base::floatfield);
           cout.precision(count_num);

           cout << endl;

           for (size_t i=0 ; i <= (size_t)x_count; ++i)
           {
                               for (size_t j=0; j <= (size_t) y_count; ++j)
                                   cout << matr2[i][j] << " " ;
                               cout << endl;
           }

       }

};

#endif // MATRIX_H
