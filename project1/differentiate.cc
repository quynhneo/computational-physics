#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main ()
{
    float x, h, h0, epsilon_m, relative_err;// variable and step in single precision
    float d_cos_forward, d_cos_central, d_cos_extrapolated;
        
    h0=0.1; // 
    epsilon_m = 0.0000001; //machine precision
    
    cout << "epsilon_m:" <<epsilon_m<< endl <<"n of points" <<log2(h0/epsilon_m) << endl;
    
    ofstream cos_forward;
    cos_forward.open("cos_forward.txt");
    
    for (int i =1; i < log2(h0/epsilon_m)+15 ; i = i+1) //each step, h decreases 2 times until getting machine precision
        {
            h= h0/pow(2.0,i);
            d_cos_forward = (  cos(0.1+ h)-cos(0.1) )  /  h; //the derivative
            relative_err = fabs( ( -sin(0.1)-d_cos_forward ) / -sin(0.1) );
            cout << "i:=" <<i <<"step:= "<< h << " dcos(0.1)/dx:= " <<d_cos_forward << " relative err:= "<< relative_err << endl;
            cos_forward << d_cos_forward << " "<< relative_err <<endl ;
            
        }
        
    //write out the file    

    
    
    return 0;//stop
   
}
