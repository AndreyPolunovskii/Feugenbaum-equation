#ifndef FUNCT_FEUGENBAIM_H
#define FUNCT_FEUGENBAIM_H

template <class T>
class Feug_function
{
public:

    int N;
    T alfa ;
    vector <T> a;


    Feug_function(int N1): a(N1+1,0),N(N1) {}

//--------------------------
 void   init_funct1()
 {
     alfa  =  (T)"2.502907873";

     a[0] = (T)"1";
     a[1] = (T)"-1.5276329";
     a[2] = (T)"0.1048151";
     a[3] = (T)"0.0267056";
  //   a[4] = (T)"-0.0035274";

 }
//------------------------
void   init_funct2()
 {
    alfa = (T)"2.50290787509588";

a[0] = (T)"1.00000000000000";

a[1] = (T)"-1.52763299703626";

a[2] = (T)"0.10481519478626";

a[3] = (T)"0.02670567053980";

a[4] = (T)"-0.00352740977264";

a[5] = (T)"0.00008160147106";

a[6] = (T)"0.00002528364803";

a[7] = (T)"-0.00000255365083";

a[8] = (T)"-0.00000009976237";

a[9] = (T)"0.00000003073988";

a[10] = (T)"-0.00000000148607";


 }
//-------------------------
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
void input_from_file(int mantiss)
{
  int k = 0;
  int prec = 0;
  T count = 0;
  string line;
  ifstream indata("output_data_g.txt");

  cout << endl;

  while (indata)
  {

    indata >> line;
    if ( check_sumbol(line) )
     {

       kill_comma(line);

       k++;
       if (k == 1)
       {
          count = line;
          prec = (int) ( (count - 1) / log10(2) ) + 205;
          mpreal::set_default_prec(prec);

       }

       if (k == 3)
       {
            alfa = (T) line;
       }

       if (k > 3 && k < count + 2 && k < N + 3 )
      {
         a[(k - 4)] = (T)line;
      }


     }
      else
        continue;


  }

    mpreal::set_default_prec(mantiss);
    indata.close();

}
//--------------------------
T g_prob(const T x,int i,vector<T> & power)
{

 if (i == 0) return a[0];
    else return g(x,i-1) + a[i]* power[i] ;
}

//--------------------------
T g(const T x,int i)
{

 if (i == 0) return a[0];
    else return g(x,i-1) + a[i]* POW(x,2*i) ;
}
//-------------------------
T diff_g(const T x,int i1)
{
 if (i1 == 0) return "0";
    else return ( diff_g(x,i1-1) +  (2*i1)*a[i1]*POW(x,2*i1-1) ) ;
}
//-------------------------
T g(const T x)
{
    return g(x,N);
}
//-------------------------
T diff_g(const T x)
{
    return diff_g(x,N);
}
//------------------------------
T g(const T x,vector <T> & power)
{
    return g_prob(x,N,power);
}
//------------------------------
T  operator[](int i){ return a[i]; }

//--------------------------
void operator=(vector<T>  vect)
{
      alfa = vect[0];

    for (int i = 1 ; i <= N; i++)
    {
        a[i] = vect[i];
    }
}
//--------------------------
void output_coeff_g(int count_num)
{

    cout.setf(ios_base::fixed,ios_base::floatfield);
    cout.precision((int) (count_num));

    cout << endl;
     cout << "alfa  = "<< alfa << endl;
     cout << endl;

      for (int i=0; i <= N; i++)
      {
          cout << "a[" <<2*i << "] = " << a[i] <<endl;
            cout << endl;
        }
}
//---------------------------
void output_in_file_coeff_g(int col_sign)
 {
      system("cp /dev/null output_data_g.txt");

      fstream outdata("output_data_g.txt");

      outdata.setf(ios_base::fixed,ios_base::floatfield);//фиксируем плавающую точку
      outdata.precision((int) (col_sign));

       outdata << " количество знаков после запятой = " << col_sign << endl;
       outdata << " количество членов ряда = " << a.size() << endl;
       outdata << endl;

       outdata<<"alfa = " << alfa << endl;
       outdata << endl;

       for (int i=0; i < a.size(); i++)
       {
           outdata << "a[" <<2*i << "] = " << a[i] <<endl;
             outdata << endl;
         }

       outdata.close();
 }
//---------------------------
void output_in_buf_file_coeff_g(int col_sign)
 {
      system("cp /dev/null output_data_buf_g.txt");

      fstream outdata("output_data_buf_g.txt");

      outdata.setf(ios_base::fixed,ios_base::floatfield);//фиксируем плавающую точку
      outdata.precision((int) (col_sign));

       outdata << " количество знаков после запятой = " << col_sign << endl;
       outdata << " количество членов ряда = " << a.size() << endl;
       outdata << endl;

       outdata<<"alfa = " << alfa << endl;
       outdata << endl;

       for (int i=0; i < a.size(); i++)
       {
           outdata << "a[" <<2*i << "] = " << a[i] <<endl;
             outdata << endl;
         }

       outdata.close();
 }
//---------------------------
vector<T> return_vector()
{
    vector<T> buf;

    buf.push_back(alfa);

    for (int i=1; i <= N; i++)
    {
       buf.push_back(a[i]);

     }

    return buf;
}
//-------------------------
scalar module_g()
{
    scalar sum = 0;

    for (int i=1; i < a.size(); i++)
    {
       sum += abs(a[i]);
    }

    return sum;
}

};



#endif // FUNCT_FEUGENBAIM_H
