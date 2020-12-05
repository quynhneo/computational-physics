#include <iostream>

#include <math.h>
#include <stdlib.h>
#include <fstream>

#include "../include/integral_trapezoid_include.hh"

float epsilon_m = 0.0000001; //machine precision


namespace integral
{

using namespace std;

float integral_trapezoid (float x, float a, float b, float N_0, int loops ) //integral range a,b and initial number of interval 
{
    float relative_err;
    float output;
    
    ofstream outfile;
    outfile.open("trapez.dat");//name of output textfile
                
    for (int j=1; j< loops+1 ; j=j+1)//to vary number of interval N    
    {
        output=0;  //reset the variable                  
        cout << " j start output"<<output <<" ";
        
        int N_j = N_0 * static_cast<float>(pow(2,j));//double number of interval every time until 2^loops
        
        float h=(b-a)/(N_j);//step size
        
        float sum=0;//reset the sum
         
        for (int i =1; i < N_j+2 ; i = i+1) // loop over N_j interval, i.e N_j+1 times
            {
              
                
                float f_i,x_i;
                x_i = a+(i-1)*h;
                f_i = static_cast<float>(exp(-1*x_i)) ;
                
                //cout << "x_"<<i<<" " << x_i << "  f_"<<i<<" "<<f_i;
                
                if ( (i==1) ||  ( i==(N_j+1) ) ) //first and last point, the weight is only  1/2
                { 
                    sum = sum + f_i*h/2; 
                }
                else  { sum = sum+f_i*h ;//every other point
                }
                
                output=sum;
               // cout <<"  ith accumulated output"<< output << endl;                                  
                
            }//for i loop end
        
        relative_err = fabs(  (  (exp(1)-1 )/exp(1)  - output)/ ((exp(1)-1 )/exp(1))      )  ;
              
        cout <<"number of interval: " << N_j  <<" integral exp("<< x << ")dx:= " << output << " relative err:= "<< relative_err << endl;
        outfile << N_j <<" "<< relative_err <<endl ;//writing out to text file     
        
        
        }//for j loop end

}//integral


}//namespace
