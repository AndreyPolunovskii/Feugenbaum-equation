
#ifndef INCLUDE_BASIC_H_
#define INCLUDE_BASIC_H_



#include <omp.h>

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <omp.h>
#include <list>
#include <iomanip>

#include <iterator>
#include <algorithm>
#include <iomanip>

using namespace std;

//библиотека высокоточных вычислений
#include <mpreal.h>
using namespace mpfr;





int n_threads = 4; //число потоков


typedef  mpreal scalar;

//typedef  double scalar;


//факториал
int fact(int i)
{
  if (i==0) return 1;
  else return i*fact(i-1);
}
//----------------------------
scalar POW(scalar  x, int i)
{
  if (i==0) return 1;
   else return POW(x,i-1) * x; 
}
//----------------------------
scalar POW1(scalar x, int i)
{
  scalar pow = 1;
  for (int k = 0 ;k < i ;k++)
       pow *= x;
  
 return pow;
}
//----------------------------



#endif /* INCLUDE_BASIC_H_ */
