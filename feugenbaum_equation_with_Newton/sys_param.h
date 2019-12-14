#ifndef SYS_PARAM_H
#define SYS_PARAM_H


  int col_unknown_g ;

  int num_iter_for_matr ;
  int num_iter_Nuwton ;

  cout << "Vvedite chislo Nuwtonowskix iterachii " << endl;
  cin >> num_iter_Nuwton;

 // cout << "Vvedite chislo iterachii obratnoi matrichi " << endl;
 // cin >> num_iter_for_matr;

  cout << "Vvedite chislo unknown clenov rada g " << endl;
  cin >> col_unknown_g;

  cout << endl;


    int N = col_unknown_g ;

    //задаем параметры для начальной матрицы
    scalar relax_parameter1 = 0;//pow(10,-2*N);
    scalar relax_parameter2 = pow(10,-0.2*N);
    scalar relax_parameter3 =0;//pow(10,-4*N);
   // в случае тейлоровского нач условия
    int num_iter_for_initial_matr = 10;


// Количество бит под мантиссу вещественного числа
     int prec = (int) (2* N / log10(2) )+850;
     int col_sign =2* N ;


    cout << endl;
    mpreal::set_default_prec(prec);
    cout << "machinnui epsilon = " << machine_epsilon() << endl;
    cout << endl;


    cout << "colichestvo znachachix chifr = " << col_sign << endl;
    cout << endl;
    cout << "//============================//" << endl;


    vector<scalar> XU(N+1);
           //почему то распараллеливание ругается на возведение в степень
           for (int i = 0; i<= N ; i++)
           {
               XU[i] = pow((scalar)i/N , 0.4) ;
           }


#endif // SYS_PARAM_H
