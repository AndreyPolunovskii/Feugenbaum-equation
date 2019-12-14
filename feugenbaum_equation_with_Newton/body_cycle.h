      //--iterracii vuch obr matricu----              

         n = 0;
          cout.precision(10);
         cout << " начальная норма Phi_inf =  " << Phi.matrix_norm_inf() << endl;
         cout.precision(col_sign);

       while (1)  
       {
         inverseIakobi = inverseIakobi *(unitMat + Phi);
          Phi = unitMat - MatIakobi * inverseIakobi ;
         
          phi_norm = Phi.matrix_norm_inf();
          n++;
          cout.precision(7);
          t1 = time(NULL) - t ;
          cout << n <<" - ая итерация обратной матрицы, норма phi_inf = " << phi_norm << endl;
          cout << "  время расчета = " << t1 << " сек" << endl;     
          cout.precision(col_sign);

              if ( phi_norm < 1e-12)
                            break;

           /*  if ( phi_norm > 1e+240)
                            {
                                cout << " расхождение при вычислении матрицы " << endl;
                                return 0;
                             } */
                                    
       }

      cout.precision(14);
       cout << " конечная норма Phi_inf =  " << phi_norm <<" ( " << n <<" итераций обратной матрицы )"<< endl;
      cout.precision(col_sign);
      cout << endl;


      G = minus_vector(G.return_vector(), inverseIakobi * vect_F); 
      vect_F = vect_Funct(G,N,XU,BUF1,BUF2);

      MatIakobi_buf = MatIakobi ;
      MatIakobi.createIakobi(G,N,XU,BUF1,BUF2);
          
      

        if ( (MatIakobi_buf -  MatIakobi).matrix_norm() > 10e-8 )
      //if (Phi.matrix_norm() > 1 || Phi.matrix_norm() == 1 )
         {
           inverseIakobi.init_LU(MatIakobi);
           Phi = unitMat -  MatIakobi * inverseIakobi ;
         }
         else
            Phi = unitMat -  MatIakobi * inverseIakobi ; 

