#ifndef SOVER_FILE_H
#define SOVER_FILE_H


void funct_solver(int & number_it,int & col_massiv,int & prec)
{

  //-----------инициализация--------------

    many_sum Mass(col_massiv);


    scalar alfa = (scalar)"2.50290787509588";//2.5029078750958928;
    scalar alfa_buf1 = 0;
    scalar alfa_buf2 = 0;

    scalar err_alfa = 0;
    scalar err_a = 0;

    scalar k_alfa = 0;//порядок сходимости

   Mass.initial_cond3();
    // Mass.input_from_file(prec,alfa);
 //   Mass.output_coeff_a();
  //  cout << alfa << endl;


    cout.setf(ios_base::fixed,ios_base::floatfield);
    cout.precision(2*col_massiv+10);

    // Mass.output_coeff_a();

    int t,t1;
      t = time(NULL);
      t1 = time(NULL);



 //------------алгоритм----------------

    for (int i=1; i<=number_it;i++)
    {

        cout << i <<" dvoinaa iterachia" << endl;


          alg_right_part(Mass,alfa,  Mass,alfa_buf1,col_massiv) ;

          alg_right_part(Mass,alfa_buf1, Mass,alfa_buf2,col_massiv) ;

          k_alfa = abs( log10( abs(alfa_buf2 -  alfa_buf1) ) / log10( abs(alfa_buf1 - alfa) )  );

          cout.precision(5);
          cout << "Skorost cxodimosti k alfa = " << k_alfa << endl;//k_alfa << endl;
          cout.precision((int) (1.*col_massiv));



         err_alfa =  abs( alfa - alfa_buf1 ) ;

       //  if (k_alfa  == inf ) break;

         alfa =  alfa_buf2 ;

            t1 = time(NULL) - t ;

            cout << "ochibka vuch alpha ( for order_eq = " << col_massiv <<" ) = " << err_alfa << endl;
            cout << "vrema racheta = " << t1 << " sek" << endl;
            cout << endl;

     //        Mass.output_coeff_a();

        //    cout << endl;

             Mass.output_in_file_coeff__buf_a(col_massiv,alfa);

            if ( abs( log10( abs(alfa_buf1 - alfa) ) ) > (scalar)(1 * col_massiv) + 5 ) break;


      }


//----------вывод на экран--------------

    cout << endl;

    cout <<"rezultatu racheta :" << endl;
    cout << endl;

    cout <<"alpha = "<< alfa << endl;
    cout << endl;

   // Mass.output_coeff_a();


    cout <<"перезаписать файл с g членами ? (Y/N) " << endl;
    char symb;
    cin >> symb;

   if( symb == 'Y')
     Mass.output_in_file_coeff_a(col_massiv, alfa);


}



#endif // SOLVER_FILE_H
