#include "basic_include.h"
#include "many_sum.h"
#include "right_part.h"
#include "solver_file.h"



int main()
{

   system("cp /dev/null logfile.log");
      setlocale(LC_ALL,""); // все равно не работает

    int number_IT ; // число итераций для решения системы
    int col_member_ser ;// количество задействованных коэффициентов (размерность системы)



    cout << "Vvedite chislo iterachii " << endl;
     cin >> number_IT;
     cout << "Vvedite poradok sistemu " << endl;
     cin >> col_member_ser;

     cout << endl;


     // Количество бит под мантиссу вещественного числа
     int prec = (int) ( 1* col_member_ser / log10(2) ) + 555;


    mpreal::set_default_prec(prec);
    cout << "machinnui epsilon = " << machine_epsilon() << endl;
    cout << endl;

     int size_mass = col_member_ser +1;

    cout << "colichestvo znachachix chifr = " << size_mass - 1 + 555 * log10(2)   << endl;
    cout << endl;

    cout << "//============================//" << endl;

    funct_solver(number_IT, size_mass,prec );
}
