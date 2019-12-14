
#ifndef INCLUDE_BASIC_H_
#define INCLUDE_BASIC_H_


#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <cmath>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <omp.h>

#include <iterator>
#include <algorithm>
#include <iomanip>

using namespace std;

#define pi (double) 3.1415926535897932384626433832795028841971

//библиотека высокоточных вычислений
#include <mpreal.h>
using namespace mpfr;

typedef mpreal scalar;


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


#include "funct_feugenbaim.h"
#include "own_funct.h"

#include "matrix.h"





#endif /* INCLUDE_BASIC_H_ */
