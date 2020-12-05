#include <iostream>
#include <typeinfo>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <limits>
#include "../include/cos_center_difference.hh"

float epsilon_m = 0.0000001; //machine precision


namespace d_cos
{

using namespace std;

float cos_center_difference (float x, float h0) //function argument and intitial step. input in main
{
    
    float hi;// ith step in single precision
    float relative_err;//long double to better calculate deviation from 'exact' answer
    float d_cos_center;//the estimated derivative
                    
    cout << "epsilon_m:" <<epsilon_m<< endl <<"n of points" <<log2(h0/epsilon_m) << endl;//just to keep track of the program
    
    ofstream cos_center_output;
    cos_center_output.open("cos_center_0.1.dat");//name of output textfile
    
    //THE MEAT OF THE PROGRAM
    for (int i =1; i < log2(h0/epsilon_m)+1 ; i = i+1) //each step, h decreases 2 times until getting passed machine precision 
        {
            hi= h0/static_cast<float>(pow(2,i));
                        
            d_cos_center = (  static_cast<float>(cos(x+hi))-static_cast<float>(cos(x-hi)) )  /  (2*hi); //center difference estimation
           //IMPORTANT: static_cast is to avoid apparent atomatic casting to double precision
                     
            relative_err = fabs(  static_cast<float>((-sin(x))- d_cos_center ) / static_cast<float>(-sin(x)) ); //absolute value
                                    
            cout << "i:=" <<i <<"step:= "<< hi << " dcos("<< x <<")/dx:= " <<d_cos_center << " relative err:= "<< relative_err << endl;
            
            cos_center_output << hi <<" "<< relative_err <<endl ;//writing out to text file
            
            cout <<"hi typeid:"<<typeid(hi).name()<<" ";//just to make sure everything float
            cout <<"deriva typeid:"<<typeid(d_cos_center).name()<<" ";
            cout <<"err typeid:"<<typeid(relative_err).name()<<endl;
            
        }   
}


}//namespace
