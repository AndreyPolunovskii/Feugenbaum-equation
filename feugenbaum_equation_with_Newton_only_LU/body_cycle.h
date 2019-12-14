      //--LU calculate----              
       MatIakobi->LU(L);
       buf_1  = MatIakobi->solve_L_B_eq(L,vect_F);
       vect_F = MatIakobi->solve_R_B_eq(buf_1);
       L->init_zero();
   


      G = minus_vector(G.return_vector(), vect_F); 
      vect_F = vect_Funct(G,N,XU,BUF1,BUF2);
      MatIakobi->createIakobi(G,N,XU,BUF1,BUF2);
    
