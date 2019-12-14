#include "basic_include.h"
#include "matrix_iakobi.h"
#include "vector_fanction.h"



int main()
{
    system("cp /dev/null logfile.log");    

    #include "sys_param.h"

    Feug_function<scalar> G(col_unknown_h);
    G.input_from_file(prec);
  //  G.output_coeff_g(col_sign);


    own_funct<scalar> H(col_unknown_h);
    H.input_from_file(prec);
  //   H.init_funct();
  //  H.output_coeff_h(col_sign);


    vector<scalar> vect_F;
    vector<scalar> BUF1(N+1,0);
    vector<scalar> BUF2(N+1,0);
    vector<scalar> BUF3(N+1,0);


    matrix<scalar> * MatIakobi = new matrix<scalar>(N,N);
    matrix<scalar> * L = new matrix<scalar>(N,N);   
//    matrix<scalar> * R = new matrix<scalar>(N,N);
    vector<scalar> buf_1(N+1,0);
   
    int t,t1,s=0, n =0;
     t = time(NULL);
     t1 = time(NULL);



//----podgotavlivaem pered zapuskom iterachii ---
   vect_F = vect_Funct(G,H,XU,N,BUF1,BUF2,BUF3);

  t1 = time(NULL) - t ;
   cout << "время вычисления вектор Функции  = " << t1 << " sek" << endl;

  // *MatIakobi = createIakobi(G,H,N);
    MatIakobi -> createIakobi(G,N,XU,H.delta,BUF1,BUF2,BUF3);

     t1 = time(NULL) - t ;
   cout << "время заполнения матрицы Якоби и вычисления вектор Функции  = " << t1 << " sek" << endl; 


     cout.setf(ios_base::fixed,ios_base::floatfield);
     cout.precision(col_sign);
     cout << endl;



//---dop dannue -----------
   vector < scalar > buf_delta(3,0);
   vector < scalar > buf_mod_h(3,0);
   scalar err_module_h = 0;
   scalar err_delta = 0;
   scalar k_delta = 0;
   int k = 0;

//--------osnovnoi chicl------------------
  while (1)
  {
    
    cout << endl;
    cout << " /--------------------------------/ " << endl;
    cout << k+1 <<"-ая двойная итерация" << endl;
    k++;
    cout << endl;


    buf_delta[0] = H.delta;
    buf_mod_h[0] = H.module_h();

    //--1 ая итерация

    cout << " 1-ая итерация " << endl;
      #include "body_cycle.h"

     t1 = time(NULL) - t ;
     cout << "vrema racheta = " << t1 << " sek" << endl;

       buf_delta[1] = H.delta;
       buf_mod_h[1] = H.module_h();

    H.output_in_buf_file_coeff_h((int) ((scalar)col_sign/1.2));
     

  // -- 2 ая итерация
       cout << " 2-ая итерация " << endl;
      #include "body_cycle.h"

      buf_delta[2] = H.delta;
       buf_mod_h[2] = H.module_h();

    // исследуем сходимость и ошибку вычисления
      k_delta = abs( log10( abs(buf_delta[2] -  buf_delta[1]) ) / log10( abs(buf_delta[1] - buf_delta[0]) )  );

      err_delta = abs (buf_delta[2] - buf_delta[0] );
      err_module_h = abs (buf_mod_h[2] - buf_mod_h[0] );

      t1 = time(NULL) - t ;

     cout.precision(5);
       cout << "vrema racheta = " << t1 << " sek" << endl;
    cout << " порядок сходимости = " << k_delta << endl;
    cout << " логарифм ошибки вычисления delta ( for order_eq_for_h = " << N <<" ) = " << log10( err_delta ) << endl;
    cout << "логарифм ошибки вычисления mass_h ( for order_eq_for_h = " << N <<" ) = " << log10( err_module_h ) << endl;
    cout << " /--------------------------------/ " << endl;
    cout <<  endl;

    H.output_in_buf_file_coeff_h((int) ((scalar)col_sign/1.2));

     if ( abs( log10( abs(buf_delta[2] - buf_delta[0]) ) ) > (scalar)(col_sign/1.5)) break;
   

  }

   cout << "результат расчета" << endl;
   cout << endl;
   
   cout.precision((int) ((scalar)col_sign/1.5)); 
   cout << "delta  = "<< H.delta << endl;
   cout << endl;
 
  //  H.output_coeff_h(col_sign);
   
    cout <<"перезаписать файл с h членами ? (Y/N) " << endl;
    char symb;
    cin >> symb;
 
   if( symb == 'Y')
      H.output_in_file_coeff_h((int) ((scalar)col_sign/1.2));

    return 0;
}
