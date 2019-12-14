      //--LU calculate----              

       MatIakobi->LU(L);
       buf_1  = MatIakobi->solve_L_B_eq(L,vect_F);
       vect_F = MatIakobi->solve_R_B_eq(buf_1);
       L->init_zero();
   


      H = minus_vector(H.return_vector(), vect_F); 
      vect_F = vect_Funct(G,H,XU,N,BUF1,BUF2,BUF3);
      MatIakobi -> createIakobi(G,N,XU,H.delta,BUF1,BUF2,BUF3);
    
