#ifndef RIGHT_PART_H
#define RIGHT_PART_H

//----------------------------------------------------------
scalar y2_0_rec(int m,int k, vector<scalar> & a,scalar & pow_k)
{
    if (m == 0) return a[k] * a[0] / pow_k;
          else return y2_0_rec(m-1,k,a,pow_k) + a[k - m] * a[m] / pow_k ;
}
//-----------------------------------
inline scalar y2_0(int k, vector<scalar> & a,scalar & pow_k)
{
    return y2_0_rec(k,k,a,pow_k);
}
//----------------------------------
scalar y2_n_rec(int m,int k, int n, vector < vector<scalar> > & Mass_y2_n)
{
    if (m == 0) return Mass_y2_n[n-1][k] * Mass_y2_n[1][0];
          else return y2_n_rec(m-1,k,n,Mass_y2_n) + Mass_y2_n[n-1][k-m] * Mass_y2_n[1][m] ;
}
//----------------------------------
inline scalar y2_n(int k, int n, vector < vector<scalar> > & Mass_y2_n)
{
    return y2_n_rec(k,k,n,Mass_y2_n);
}
//-----------------------------------
void create_Mass_y2_n(many_sum & Mass, scalar & alpha , int & N)
{

   int k,n;
   vector <scalar> power(N+1,1);
   
   power[1] *= pow(-alpha,2);
   for (k=2;k<N;k++)
       power[k] *= power[k-1]*pow(-alpha,2);
    
    #pragma omp parallel for private(k)
    for (k = 0 ;k < N; k++)
    {
    
             Mass.Mass_yn[1][k] = y2_0(k,Mass.a,power[k]);
    }

     k = 0;

  for (n=2 ;n < N;n++) 
   {
    #pragma omp parallel for private(k)
     for (k=0 ;k < N;k++)
        {
         Mass.Mass_yn[n][k] = y2_n(k,n,Mass.Mass_yn);
        }
    }

}
//-----------------------------------
scalar solve_right_Part(int n ,int k,const many_sum & Mass)
{
       if (n == 1) return  Mass.a[1] * Mass.Mass_yn[1][k];
            else return  solve_right_Part(n-1,k,Mass) + Mass.a[n] * Mass.Mass_yn[n][k] ;
}
//-----------------------------------
inline scalar solve_right_Part(int k,const many_sum & Mass , int & N)
{
        return solve_right_Part(N-1,k,Mass);
}
//--------------------------------------------------------
void alg_right_part(many_sum & Mass_in,scalar & alfa_in, many_sum & Mass_out,  scalar & alfa_out ,int & col_massiv)
{
    many_sum * Mass_buf = new many_sum(col_massiv);

    *Mass_buf = Mass_in;

    Mass_in.a[1] = -1/alfa_in - Mass_in.sum_a_without_a2();

    create_Mass_y2_n(*Mass_buf, alfa_in, col_massiv);

    size_t s;

     #pragma omp parallel for private(s)
    for (s=2; s< (size_t)col_massiv;s++)
             Mass_in.a[s] = - alfa_in * solve_right_Part((int)s,*Mass_buf,col_massiv) ;



    Mass_out = Mass_in;

    alfa_out = -Mass_in.sum_a2();
       
   Mass_buf->~many_sum();

}


#endif // RIGHT_PART_H
