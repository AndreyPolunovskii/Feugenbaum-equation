#ifndef SYS_PARAM_H
#define SYS_PARAM_H


  int col_unknown_h ;

  cout << "Vvedite chislo unknown clenov rada h " << endl;
  cin >> col_unknown_h;

  cout << endl;


    int N = col_unknown_h ;

   // Количество бит под мантиссу вещественного числа
     int prec = (int) (2* N / log10(2) )+750;
     int col_sign =2* N ;


    cout << endl;
    mpreal::set_default_prec(prec);
    cout << "machinnui epsilon = " << machine_epsilon() << endl;
    cout << endl;


    cout << "количество значащих цифр в расчете = " << col_sign + (int) (750. * log10(2))  << endl;
    cout << endl;
    cout << "//============================//" << endl;


    vector<scalar> XU(N+1);
           //почему то распараллеливание ругается на возведение в степень
           for (int i = 0; i<= N ; i++)
           {
               XU[i] = pow( (scalar)i/N , 0.4 ) ;
           }


#endif // SYS_PARAM_H
