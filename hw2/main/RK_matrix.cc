#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

double ERK( double t_i, double t_f, const int n_max)//write a method to apply explicit Runge-Kutta
{
    const int nu_max =4;
    double integral = 0;    
    double h = (t_f-t_i)/n_max;
    double t_n;
    double b1=0.166666666666;double b2=0.333333333333; double b3=b2; double b4=b1;
    double b[5]={0,b1,b2,b3,b4};
    double c1=0; double c2=0.5; double c3=c2; 
    double c[5]={0,c1,c2,c3,1};
    double psi[nu_max];
    double A[5][5]={
          {0,0,0,0,0}, 
          {0,0,0,0,0},
          {0,0.5,0,0,0},
          {0, 0,0.5,0,0},
          {0,0,0,1.0,0} } ;
   
    double y=1;//initial value	
    
    for (int n=1; n < n_max+1; n=n+1 ) 
    {
        t_n = t_i+ h*(n-1); cout<< "t_"<<n<<": "<<t_n<<" ";
        
        double sum_y=0;//the sum in the  y expression
        double psi[nu_max+1]={0};
        for (int i=1; i< nu_max+1 ; i=i+1 ) // loop over all stages to update y_n 
        {
           double sum_psi =0 ;//the sum in expression of psi
           for (int j=1; j < i ; j=j+1)//  //calculate all psi for the step n
           {
                sum_psi = A[i][j]*(-2*psi[j]+(t_n+c[j]*h)+4);// how to define F(t,y)?
           }//end of psi loop
           psi[i]= y + h * sum_psi;//save psi i to array
        } //end of stages loop
        for (int i=1;i<nu_max+1; i=i+1) 
              { cout << (-2*psi[i]+(t_n+c[i]*h)+4)<<endl;
              y = y +h* b[i]*(-2*psi[i]+(t_n+c[i]*h)+4); }//calculate y for step n
        cout << "y_"<<n<<": "<< y<<endl;
    }//end of the main loop
   std::cout<<"y:  "<< y<<endl;
	return y;
}


int main(int argc, char* argv[])//what are these for?
{
    ERK(0,0.2,1);
  return 0; 
		
}



