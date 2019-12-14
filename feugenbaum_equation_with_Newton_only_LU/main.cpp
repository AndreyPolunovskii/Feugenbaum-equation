#include "basic_include.h"
#include "vector_fanction.h"



int main()
{
   system("cp /dev/null logfile.log");

    #include "sys_param.h"

    Feug_function<scalar> G(col_unknown_g);
   // G.init_funct2();
     G.input_from_file(prec); // посмотри! возможно есть какие то внутренние ошибки тут
   // G.output_coeff_g(col_sign);

    vector<scalar> vect_F;
    vector<scalar> BUF1(N+1,0);
    vector<scalar> BUF2(N+1,0);


 //   scalar * ptr =  new scalar [N*N];
 //   scalar * ptr2 =  new scalar [N*N];
    matrix<scalar> * MatIakobi = new matrix<scalar>(N,N);
    matrix<scalar> * L = new matrix<scalar>(N,N);   
    vector<scalar> buf_1(N+1,0);


    int t,t1,s=0, n =0;
      t = time(NULL);
      t1 = time(NULL);



//----podgotavlivaem pered zapuskom iterachii ---
   vect_F = vect_Funct(G,N,XU,BUF1,BUF2);

 t1 = time(NULL) - t ;
   cout << "время вычисления вектор Функции  = " << t1 << " sek" << endl;

   MatIakobi->createIakobi(G,N,XU,BUF1,BUF2); 

   t1 = time(NULL) - t ;
   cout << "время заполнения матрицы Якоби и вычисления вектор Функции  = " << t1 << " sek" << endl;  


 cout.setf(ios_base::fixed,ios_base::floatfield);
 cout.precision(col_sign);
  cout << endl;


//---dop dannue -----------
   vector < scalar > buf_alfa(3,0);
   vector < scalar > buf_mod_a(3,0);
   scalar err_module_g = 0;
   scalar err_alfa = 0;
   scalar k_alfa = 0;
   int k = 0; 
 

//--------osnovnoi chicl------------------
  while (1)
  {
    cout << endl;
    cout << " /--------------------------------/ " << endl;
    cout << k+1 <<"-ая двойная итерация" << endl;
    k++;
    cout << endl;

     buf_alfa[0] = G.alfa;
     buf_mod_a[0] = G.module_g();


  //--1 ая итерация

    cout << " 1-ая итерация " << endl;
      #include "body_cycle.h"

     t1 = time(NULL) - t ;
     cout << "vrema racheta = " << t1 << " sek" << endl;

       buf_alfa[1] = G.alfa;
       buf_mod_a[1] = G.module_g();

    G.output_in_buf_file_coeff_g(col_sign);

  // -- 2 ая итерация
       cout << " 2-ая итерация " << endl;
      #include "body_cycle.h"

      buf_alfa[2] = G.alfa;
      buf_mod_a[2] = G.module_g();

    // исследуем сходимость и ошибку вычисления
      k_alfa = abs( log10( abs(buf_alfa[2] -  buf_alfa[1]) ) / log10( abs(buf_alfa[1] - buf_alfa[0]) )  );
      err_alfa = abs (buf_alfa[2] - buf_alfa[0] );
      err_module_g = abs (buf_mod_a[2] - buf_mod_a[0] );

      t1 = time(NULL) - t ;

     cout.precision(5);
       cout << "vrema racheta = " << t1 << " sek" << endl;
    cout << " порядок сходимости = " << k_alfa << endl;
    cout << " логарифм ошибки вычисления alfa ( for order_eq_for_g = " << N <<" ) = " << log10( err_alfa ) << endl;
    cout << "логарифм ошибки вычисления mass_a ( for order_eq_for_g = " << N <<" ) = " << log10( err_module_g ) << endl;
  //  cout << "alfa i = "<< G.alfa << endl;
    cout << " /--------------------------------/ " << endl;
    cout <<  endl;

    G.output_in_buf_file_coeff_g(col_sign);

     if ( abs( log10( abs(buf_alfa[2] - buf_alfa[0]) ) ) > (scalar)col_sign ) break;

  }
    cout << "результат расчета" << endl;
   cout << endl;
   
   cout.precision((int) (col_sign)); 
   cout << "alfa  = "<< G.alfa << endl;
   cout << endl;

   // G.output_coeff_g(col_sign);

    cout <<"перезаписать файл с g членами ? (Y/N) " << endl;
    char symb;
    cin >> symb;

   if( symb == 'Y')
      G.output_in_file_coeff_g(col_sign);

    return 0;
}
