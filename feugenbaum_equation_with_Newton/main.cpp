#include "basic_include.h"
#include "vector_fanction.h"



int main()
{
   system("cp /dev/null logfile.log");

    #include "sys_param.h"

    Feug_function<scalar> G(col_unknown_g);
    G.init_funct2();
    // G.input_from_file(prec); // посмотри! возможно есть какие то внутренние ошибки тут
   // G.output_coeff_g(col_sign);
   // cout <<  G.alfa << endl;
 // cout << G.diff_g(1) << endl;

    vector<scalar> vect_F;
    vector<scalar> BUF1(N+1,0);
    vector<scalar> BUF2(N+1,0);


    matrix<scalar> MatIakobi(N,N);
    matrix<scalar> MatIakobi_buf(N,N);
    matrix<scalar> inverseIakobi(N,N);
    matrix<scalar> Phi(N,N);


    matrix<scalar> unitMat(N,N);
    unitMat.init_cound1();

    int t,t1,s=0, n =0;
      t = time(NULL);
      t1 = time(NULL);



//----podgotavlivaem pered zapuskom iterachii ---
   vect_F = vect_Funct(G,N,XU,BUF1,BUF2);
   MatIakobi.createIakobi(G,N,XU,BUF1,BUF2); 
   
   t1 = time(NULL) - t ;
   cout << "время заполнения матрицы Якоби  = " << t1 << " sek" << endl;  


 cout.setf(ios_base::fixed,ios_base::floatfield);
 //  MatIakobi.output_matrix(10);
  cout << endl;
   inverseIakobi.init_LU(MatIakobi);
 //    inverseIakobi.init_transp(MatIakobi);

   t1 = time(NULL) - t ;
    cout << "время LU-вычисления обратной матрицы Якоби   = " << t1 << " sek" << endl;

 //  inverseIakobi.init_transp(MatIakobi);
 //   inverseIakobi.output_matrix(10);
 //  cout <<"норма матрицы Якоби = " << MatIakobi .matrix_norm() << endl;
 //  cout <<"след матрицы Якоби = " << MatIakobi .matrix_trace() << endl;
   Phi = unitMat -  MatIakobi * inverseIakobi ;

   cout <<"Норма матрицы Phi_inf = " << Phi.matrix_norm_inf() << endl;


  cout.setf(ios_base::fixed,ios_base::floatfield);
  cout.precision(col_sign);


//---dop dannue -----------
   vector < scalar > buf_alfa(3,0);
   vector < scalar > buf_mod_a(3,0);
   scalar err_module_g = 0;
   scalar err_alfa = 0;
   scalar init_norm_inverse_matrix=0;
   scalar final_norm_inverse_matrix=0;
   scalar k_alfa = 0;
   scalar phi_norm = 0;
  

//--------osnovnoi chicl------------------
  for (int k=0 ;k < num_iter_Nuwton ; k++)
  {

    cout << endl;
    cout << " /--------------------------------/ " << endl;
    cout << k+1 <<"-ая двойная итерация" << endl;
    cout.precision(10);
  //  cout << "Iakobi matrix norm for inverse = "  << MatIakobi.matrix_norm() << endl;
  //  init_norm_inverse_matrix = inverseIakobi.matrix_norm();
  //  cout << "init matrix abs log norm for inverse = " << abs(log10( init_norm_inverse_matrix ))<< endl;
    cout.precision(col_sign);
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

  // -- 2 ая итерация
       cout << " 2-ая итерация " << endl;
      #include "body_cycle.h"

      buf_alfa[2] = G.alfa;
      buf_mod_a[2] = G.module_g();

   //  final_norm_inverse_matrix = inverseIakobi.matrix_norm();

     // исследуем сходимость и ошибку вычисления
      k_alfa = abs( log10( abs(buf_alfa[2] -  buf_alfa[1]) ) / log10( abs(buf_alfa[1] - buf_alfa[0]) )  );
      err_alfa = abs (buf_alfa[2] - buf_alfa[0] );
      err_module_g = abs (buf_mod_a[2] - buf_mod_a[0] );

      t1 = time(NULL) - t ;

    cout.precision(10);
   // cout << "final matrix abs log norm for inverse = " <<abs(log10( final_norm_inverse_matrix ))<< endl;
    cout.precision(5);
    cout << " порядок сходимости = " << k_alfa << endl;
    cout.precision(col_sign);
    cout << " ошибка вычисления alfa ( for order_eq_for_g = " << N <<" ) = " << err_alfa << endl;
    cout << " ошибка вычисления mass_a ( for order_eq_for_g = " << N <<" ) = " << err_module_g << endl;
    cout << "alfa i = "<< G.alfa << endl;
    cout << "vrema racheta = " << t1 << " sek" << endl;
    cout << " /--------------------------------/ " << endl;
    cout <<  endl;

    G.output_in_buf_file_coeff_g(col_sign);

     if ( abs( log10( abs(buf_alfa[2] - buf_alfa[0]) ) ) > (scalar)col_sign ) break;

  }


    G.output_coeff_g(col_sign);

    cout <<"перезаписать файл с g членами ? (Y/N) " << endl;
    char symb;
    cin >> symb;

   if( symb == 'Y')
      G.output_in_file_coeff_g(col_sign);

    return 0;
}
