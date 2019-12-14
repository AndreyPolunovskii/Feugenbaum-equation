#ifndef OWN_FUNCT_H
#define OWN_FUNCT_H

template <class T>
class own_funct
{
public:

    int N;
    T delta ;
    vector <T> h;
    int pr;


    own_funct(int N1): h(N1+1,0),N(N1) {}

//--------------------------
 void   init_funct()
 {
     delta  = 4.6692016;
     h[0] = 1;
     h[1] = -0.325651;
     h[2] = -0.050554;
     h[3] = 0.01456;
     h[4] = -0.000881;

 }

//--------------------------
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
  h[0] = 1;
  
  int k = 0;
  int prec = 0;
  T count = 0;
  T count1 = 0;
  string line;
  ifstream indata("output_data_h.txt");
  
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
                  pr =  (int) (count /log10(2) + 205);
                  prec = (int) pr;
                  mpreal::set_default_prec(prec);
               }

  

       if (k == 3)
       {
            delta = (T) line;
       }

       if (k > 3 &&  k < N + 5 )
      {
         h[(k - 4)] = (T)line;
      }


     }
      else
        continue;


  }
    h[0] = 1;
    mpreal::set_default_prec(mantiss);
    indata.close();
  
}
//--------------------------
T H(T x)
{
    T sum = 0;

    for (int i = 0 ; i <= N; i++)
    {
       sum += h[i]* pow(x,2*i);
    }

    return sum;
}
//-------------------------
void operator=(vector<T>  vect)
{
      delta = vect[0];

    for (int i = 1 ; i <= N; i++)
    {
        h[i] = vect[i];
    }
}
//-------------------------
T  operator[](int i){ return h[i]; }

//--------------------------
void output_coeff_h(int count_num)
{

    cout.setf(ios_base::fixed,ios_base::floatfield);
    cout.precision(count_num);

    cout << endl;
     cout << "delta  = "<< delta << endl;
     cout << endl;

      for (int i=0; i <= N; i++)
      {
          cout << "h[" <<2*i << "] = " << h[i] <<endl;
            cout << endl;
        }
}
//---------------------------
void output_in_buf_file_coeff_h(int col_sign)
 {
      system("cp /dev/null output_data_buf_h.txt");
     
      fstream outdata("output_data_buf_h.txt");
  
      outdata.setf(ios_base::fixed,ios_base::floatfield);//фиксируем плавающую точку
      outdata.precision(col_sign);

       outdata << " количество знаков после запятой = " << col_sign << endl;
       outdata << " количество членов ряда = " << h.size() << endl;
       outdata << endl;
   
       outdata<<"delta = " << delta << endl;
       outdata << endl;
       
       for (int i=0; i < h.size(); i++)
       {   
           outdata << "h[" <<2*i << "] = " << h[i] <<endl;
             outdata << endl;
         }
       
       outdata.close();
 }
//---------------------------
void output_in_file_coeff_h(int col_sign)
 {
      system("cp /dev/null output_data_h.txt");
     
      fstream outdata("output_data_h.txt");
  
      outdata.setf(ios_base::fixed,ios_base::floatfield);//фиксируем плавающую точку
      outdata.precision(col_sign);

       outdata << " количество знаков после запятой = " << col_sign << endl;
       outdata << " количество членов ряда = " << h.size() << endl;
       outdata << endl;
   
       outdata<<"delta = " << delta << endl;
       outdata << endl;
       
       for (int i=0; i < h.size(); i++)
       {   
           outdata << "h[" <<2*i << "] = " << h[i] <<endl;
             outdata << endl;
         }
       
       outdata.close();
 }
//---------------------------
vector<T> return_vector()
{
    vector<T> buf;

    buf.push_back(delta);

    for (int i=1; i <= N; i++)
    {
       buf.push_back(h[i]);

     }

    return buf;
}
//-------------------------
scalar module_h()
{
    scalar sum = 0;

    for (int i=1; i < h.size(); i++)
    {
       sum += abs(h[i]);
    }

    return sum;
}

};


#endif // OWN_FUNCT_H
