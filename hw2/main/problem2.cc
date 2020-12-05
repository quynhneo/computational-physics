#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <fftw3.h>
using namespace std;

double ERK( double t_i, double t_f, const int n_max)//write a method to apply explicit Runge-Kutta
{
    const int nu_max =4;
    double integral = 0;    
    double h = (t_f-t_i)/n_max;
    double t_n;
    double b1=1.0/6.0;double b2=1.0/3.0; double b3=b2; double b4=b1;
    double b[5]={0,b1,b2,b3,b4};//using 5 dimension just for indexing convenient. first dimension =0
    double c1=0; double c2=0.5; double c3=c2; 
    double c[5]={0,c1,c2,c3,1};//using 5 dimension just for indexing convenient.
    double psi[nu_max];
    double A[5][5]={
          {0,0,0,0,0}, 
          {0,0,0,0,0},
          {0,0.5,0,0,0},
          {0, 0,0.5,0,0},
          {0,0,0,1.0,0} } ;//using 5 dimension just for indexing convenient.
    double eccentricity_mercury = 0.20563069;
    double alpha =1/( 57.91*1e9 *(1-eccentricity_mercury*eccentricity_mercury)      );
    double beta =0;  //meter   
    double y[3]={0,alpha*(1+eccentricity_mercury),0};//initial value. y=(u,v). the first dimension is unused	
   
    ofstream outfile;
    outfile.open("output2.dat");//write out for plot
 
    for (int n=1; n < n_max+1; n=n+1 ) //phi step
    {
        t_n = t_i+ h*(n-1);        
        double sum_y[3]={0};//the sum in the  y expression
        double psi[3][nu_max+1]={0};
        for (int i=1; i< nu_max+1 ; i=i+1 ) // loop over all stages to update y_n 
        {
           double sum_psi[3] ={0} ;//the sum in expression of psi
           double F[3][5]={0};
           for (int j=1; j < i ; j=j+1)//  //calculate all psi for the step n
           {
              //  F[1][j]=(-2*psi[1][j]+(t_n+c[j]*h)+4);
              //  sum_psi[1] = A[i][j]*F[1][j];// how to define F(t,y)?
                F[1][j]=(psi[2][j]);// u_n+1 = v_nv
                sum_psi[1] = A[i][j]*F[1][j];
                
                F[2][j]=(-psi[1][j] + pow(alpha,0.95)*pow(psi[1][j],0.05) );//v_n+1 = -u + alpha + beta* u^2
                sum_psi[2] = A[i][j]*F[2][j]; 
           }//end of psi loop
           //psi[1][i]= y[1] + h * sum_psi[1];//save psi i to array
            psi[1][i]= y[1] + h * sum_psi[1];//save psi i to array
            psi[2][i]= y[2] + h * sum_psi[2];//save psi i to array


        } //end of stages loop
        double f[3][5]={0};
        for (int i=1;i<nu_max+1; i=i+1) 
            { 
               //f[1][i]=(-2*psi[1][i]+(t_n+c[i]*h)+4);
               //y[1] = y[1] +h* b[i]*f[1][i];

               f[1][i]=psi[2][i];
               y[1] = y[1] +h* b[i]*f[1][i];
               f[2][i]=(-psi[1][i] + pow(alpha,0.95) * pow(psi[1][i],0.05));
               y[2] = y[2] +h* b[i]*f[2][i];
            }//calculate y for step n
        //cout << "  V_"<<n<<": "<< y[2];
        
  //      double newton_u;
  //      newton_u =alpha*(1+eccentricity_mercury*cos(t_n)); 	
if (t_n==0 || t_n>6.1){
        outfile<< setprecision(15)  <<t_n<<" "<<setprecision(15)   << y[1]<<" " << endl;//newton_u<<" "<< y[1]-newton_u<<" "<<1/y[1] <<endl;

        cout<< "t_"<<n<<": "<<setprecision(15)   <<t_n<<" ";
        cout << "RK_U_"<<n<<": "<<setprecision(15) << y[1];
        cout << " v " << y[2]<<endl;
//        cout << " newton_U: "<<newton_u<<" diff: "<< y[1]-newton_u<< endl;
}
    }//end of the main loop
   
    std::cout<<"y:  "<< y[1]<<endl;
	return y[1];
}


int main(int argc, char* argv[])//what are these for?
{
    //ERK(0,0.2,10);
    ERK(0,6.5,10000);
  return 0; 
		
}


