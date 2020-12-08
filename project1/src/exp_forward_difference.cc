#include <iostream>

#include <math.h>
#include <stdlib.h>
#include <fstream>

#include "../include/exp_forward_difference.hh"

float epsilon_m = 0.0000001; //machine precision


namespace d_exp
{

using namespace std;

float exp_forward_difference (float x, float h0) //function argument and intitial step
{
    float hi;
    float relative_err;
    float d_exp_forward;
                    
    cout << "epsilon_m:" <<epsilon_m<< endl <<"n of points" <<log2(h0/epsilon_m) << endl;
    
    ofstream exp_forward_output;
    exp_forward_output.open("exp_forward_0.1.dat");//name of output textfile
    
    for (int i =1; i < log2(h0/epsilon_m)+1 ; i = i+1) //each step, h decreases 2 times until getting passed machine precision
        {
            hi= h0/static_cast<float>(pow(2.0,i));
            d_exp_forward = ( static_cast<float>(expf(x+hi))- static_cast<float>(expf(x)) )  /  hi; //the derivative
            relative_err = fabs( ( static_cast<float>(expf(x))-d_exp_forward ) / static_cast<float>(expf(x)) ); //absolute value
            cout << "i:=" <<i <<"step:= "<< hi << " dexp("<< x << ")/dx:= " <<d_exp_forward << " relative err:= "<< relative_err << endl;
            exp_forward_output << hi <<" "<< relative_err <<endl ;//writing out to text file
            
        }   
}


}//namespace
