#include <iostream>

#include <math.h>
#include <stdlib.h>
#include <fstream>

#include "../include/exp_extrapolation_header.hh"

float epsilon_m = 0.0000001; //machine precision


namespace d_exp
{

using namespace std;

float exp_extrapolated_difference (float x, float h0) //function argument and intitial step
{
    float hi;
    float relative_err;
    float d_exp_extrapolated;
    float d1,d2;
                    
    cout << "epsilon_m:" <<epsilon_m<< endl <<"n of points" <<log2(h0/epsilon_m) << endl;
    
    ofstream exp_extrapolated_output;
    exp_extrapolated_output.open("exp_extrapolated_10.dat");//name of output textfile
    
  for (int i =1; i < log2(h0/epsilon_m)+1 ; i = i+1) //each step, h decreases 2 times until getting passed machine precision
        {
            hi = h0/static_cast<float>(pow(2.0,i));/* for (int i=1;i< 1000; i=i+1) { hi = h0-i*epsilon_m*10000;*/
            d1 = ( static_cast<float>(expf(x+hi/2))-static_cast<float>(expf(x-hi/2)) ) /hi;
            d2 =  ( static_cast<float>(expf(x+hi/4))-static_cast<float>(expf(x-hi/4)) ) / (hi/2);
            
            d_exp_extrapolated = (4*d2-d1)/3;
            
            relative_err = fabs( ( static_cast<float>(expf(x))-d_exp_extrapolated ) / static_cast<float>(expf(x)) ); //absolute value
            cout << "i:=" <<i <<" step:= "<< hi << " dExp("<< x << ")/dx:= " <<d_exp_extrapolated << " relative err:= "<< relative_err << endl;
            exp_extrapolated_output << hi <<" "<< relative_err <<endl ;//writing out to text file
            
        }   
}


}//namespace
