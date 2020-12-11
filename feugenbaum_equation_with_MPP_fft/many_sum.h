#ifndef MANY_SUM_H
#define MANY_SUM_H


class many_sum
{

public:

    vector< vector<scalar> > Mass_yn;
    vector<scalar> a;

    int size1;

//-----------------------------------
    many_sum(int & size_M): a(size_M,0),size1(size_M)
    {

                Mass_yn.resize(size_M);

                    for (int i=0; i< size_M; i++)
                    {

                        Mass_yn[i].resize(size_M);
                               for(size_t j = 0; j < size_M; ++j)
                                    Mass_yn[i][j] = 0;
                    }
    }

//-------------------------------------
    void initial_cond1()
    {
       a[0] = 1;

       a[1] = -1.52763299703630145403589031018;

       a[2] = 0.10481519478730373321674261394;

       a[3] = 0.02670567052519335403265209432;

       a[4] = -0.00352740966090870917023418858;

       a[5] = 0.00008160096654753174517218423;

       a[6] = 0.00002528508423396353617627729;

       a[7] = -0.00000255631716627849384638260;

       a[8] = -0.00000009651271550891203211340;

       a[9] = 0.00000002819346397450409129529;

       a[10] = -0.00000000027730511607990107224;

       a[11] = -0.0000000003028427022130567519171;

       a[12] = 0.00000000002670589280748088278;

       a[13] = 0.00000000000099622916410272472;

       a[14] = -0.00000000000036242029829030622;

       a[15] = 0.00000000000002179657744818188;

       a[16] = 0.00000000000000152923289954734;

       a[17] = -0.00000000000000031847287904112;


     //  a[4]=0;
    //   a[3]=0.0261;     //  a[3] = 0.0261;
    //   a[4]=-0.0035;      //   a[4] = 0;//-0.0035;
     //   a[5]=0;     //   a[5] = 0;
    }

//-------------------------------------
    void initial_cond2()
    {
        a[0] = (scalar)"1.00000000000000";

        a[1] = (scalar)"-1.52763299703626";

        a[2] = (scalar)"0.10481519478626";

        a[3] = (scalar)"0.02670567053980";

        a[4] = (scalar)"-0.00352740977264";

        a[5] = (scalar)"0.00008160147106";

        a[6] = (scalar)"0.00002528364803";

        a[7] = (scalar)"-0.00000255365083";

        a[8] = (scalar)"-0.00000009976237";

        a[9] = (scalar)"0.00000003073988";

        a[10] = (scalar)"-0.00000000148607";

    }
//--------------------------------------
    void initial_cond3()
    {
        a[0] = 1;

        a[1] = -1.5;
        a[2] = 0.1;

        a[3] = 0.026;
    }
//--------------------------------------
    void initial_cond4()
    {
        a[0] = 1;

        a[1] = -1.527;
        a[2] = 0.105;

        a[3] = 0.027;
    }
 //------------------------------------

  void initial_cond1_n()
{
  for(size_t j = 1; j < size1; ++j)
                      a[j] = 1/j;

}

//-------------------------------------
private:
int check_sumbol(string & stroka)
{
   char mass[11] = {'0','1','2','3','4','5','6','7','8','9','-'};

  for (int i = 0 ; i < 11 ;i++)
     if (mass[i] == stroka[0])
           return 1;

  return 0;

}
//-------------------------
void kill_comma(string & stroka)
{
  for (int i=0; i < stroka.length(); i++)
       if (stroka[i]==',')
         {
           stroka[i] = '.' ;
           break;
         }
}
//-------------------------
public:
void input_from_file(int mantiss,scalar & alfa)
{

  int k = 0;
  int prec = 0;
  scalar count = 0;
  string line;
  ifstream indata("output_data_g.txt");

  cout << endl;

  while (indata)
  {

    indata >> line;
    if ( check_sumbol(line)  )
     {

       kill_comma(line);

       k++;
       if (k == 1)
       {
          count = line;
          prec = (int) ( (count - 1) / log10(2) ) + 55;
          mpreal::set_default_prec(prec);

       }

       if (k == 3)
       {
            alfa = line;
       }

       if (k > 3 && k < count + 4 && k < size1+4)
      {
         a[(k - 4)] = line;
      }


     }
      else
        continue;

  }
    mpreal::set_default_prec(mantiss);
    indata.close();

}
 //------------------------------------
 many_sum & operator=(many_sum mass)
   {
       this->a = mass.a;

        for (int i=0; i< Mass_yn.size() ; i++)
              this->Mass_yn[i] = Mass_yn[i];

     return *this ;
   }
//-----------------------------------
 many_sum  operator+(many_sum  mass)
   {

     many_sum buf(size1);

     for (int i=1; i< size1; i++)
     {
       buf.a[i] = mass.a[i] + a[i];
     }

     return buf ;
   }
//------------------------------------
 many_sum operator/(int scalar1)
   {

     many_sum buf(size1);

     for (int i=1; i< size1; i++)
     {
       buf.a[i] = a[i] /( (scalar) scalar1);
     }

     return buf ;
   }
//------------------------------------
 many_sum  operator-(many_sum & mass)
   {

     many_sum buf(size1);

     for (int i=1; i< size1; i++)
     {
       buf.a[i] =  a[i] - mass.a[i] ;
     }

     return buf ;
   }
//------------------------------------
 void output_coeff_a()
 {

       for (int i=1; i < a.size(); i++)
       {
           cout << "a[" <<2*i << "] = " << a[i] <<endl;
             cout << endl;
         }
 }
//---------------------------------------
void output_in_file_coeff_a(int col_sign,scalar alfa)
 {
      system("cp /dev/null output_data_g.txt");

      fstream outdata("output_data_g.txt");

      outdata.setf(ios_base::fixed,ios_base::floatfield);//фиксируем плавающую точку
      outdata.precision((int) (2.*col_sign));

       outdata << " количество знаков после запятой = " << (int) (2.*col_sign) << endl;
       outdata << " количество членов ряда = " << a.size() << endl;
       outdata << endl;

       outdata<<"alfa = " << alfa << endl;
       outdata << endl;

       for (int i=0; i < a.size() ; i++)
       {
           outdata << "a[" <<2*i << "] = " << a[i] <<endl;
             outdata << endl;
         }

       outdata.close();
 }
//----------------------------------------
void output_in_file_coeff__buf_a(int col_sign,scalar alfa)
 {
      system("cp /dev/null output_data_buf_g.txt");

      fstream outdata("output_data_buf_g.txt");

      outdata.setf(ios_base::fixed,ios_base::floatfield);//фиксируем плавающую точку
      outdata.precision((int) (1.*col_sign));

       outdata << " количество знаков после запятой = " <<(int) (1 * col_sign) << endl;
       outdata << " количество членов ряда = " << a.size() << endl;
       outdata << endl;

       outdata<<"alfa = " << alfa << endl;
       outdata << endl;

       for (int i=0; i < a.size() ; i++)
       {
           outdata << "a[" <<2*i << "] = " << a[i] <<endl;
             outdata << endl;
         }

       outdata.close();
 }
//----------------------------------------
void zero_yn()
{
    for (int i=0; i< Mass_yn.size(); i++)
        for(size_t j = 0; j < Mass_yn.size(); ++j)
                    Mass_yn[i][j] = 0;

}
//----------------------------------------
 scalar sum_a_without_a2()
 {
     scalar sum = 1;

     for (int i=2; i < a.size(); i++)
     {
        sum += a[i];
     }


     return sum;
 }
//---------------------------------------
 scalar sum_a2()
 {
     scalar sum = 0;

     for (int i=1; i < a.size(); i++)
     {
        sum += (2*i) * a[i];
     }

     return sum;
 }
//---------------------------------------
scalar module_a()
{
    scalar sum = 0;

    for (int i=1; i < a.size(); i++)
    {
       sum += abs(a[i]);
    }

    return sum;
}
//---------------------------------------
~many_sum()
{
   Mass_yn.clear();
   a.clear();
}
//---------------------------------------
};

#endif // _MANY_SUM_H
