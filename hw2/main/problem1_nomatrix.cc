#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

double ERK( double t_i, double t_f, const int n_max)//write a method to apply explicit Runge-Kutta
{
    const int nu_max =4;
    double h = (t_f-t_i)/n_max;
    double t_n;
    double b1=0.166666666666;double b2=0.333333333333; double b3=b2; double b4=b1;

    double b[4]={b1,b2,b3,b4};
    double c1=0; double c2=0.5; double c3=c2; 
    double c[4]={c1,c2,c3,1};
    double psi[nu_max];
    double alpha = 1;//for testing
    double beta =0;//for testing newtonian only, will make beta an argument
    double y[2]={0,0};//initial value of the function
    
    for (int n=0; n < n_max; n=n+1 )//loop over all time interval 
    {
        t_n = t_i+ h*n; //time step
        
       double psi_temp=0;//place holder to update psi
       double psi[nu_max]={0};
  
       for (int i=0; i< nu_max ; i=i+1 ) // loop over all stages to update y_n 
        {   
           double new_t=   (t_n+c[i]*h);
           double new_y[2]= { (y[0]+h*c[i]*psi_temp), (y[1]+h*c[i]*psi_temp)};       
          psi[i] =
          psi_temp=psi[i];
          
         } //end of stages loop

 
        y = y + h*(psi[0]*b[0]+psi[1]*b[1]+psi[2]*b[2]+b[3]*psi[3]);     //updating y_n
        cout << "y_"<<n<<": "<< y<<endl;
  
    }//end of the main loop
  
    std::cout<<"y:  "<< y<<endl;

    return y;
}


int main(int argc, char* argv[])//what are these for?
{
    ERK(0,20,20);
  return 0; 
		
}



