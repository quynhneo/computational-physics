#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

float epsilon_m = 0.0000001; //machine precision

float cos_forward_difference (float x, float h0) //function argument and intitial step
{
    float h, relative_err;// variable and step in single precision
    float d_cos_forward;
                    
    cout << "epsilon_m:" <<epsilon_m<< endl <<"n of points" <<log2(h0/epsilon_m) << endl;
    
    ofstream cos_forward_output;
    cos_forward_output.open("cos_forward.txt");
    
    for (int i =1; i < log2(h0/epsilon_m)+15 ; i = i+1) //each step, h decreases 2 times until getting machine precision
        {
            h= h0/pow(2.0,i);
            d_cos_forward = (  cos(0.1+ h)-cos(0.1) )  /  h; //the derivative
            relative_err = fabs( ( -sin(0.1)-d_cos_forward ) / -sin(0.1) );
            cout << "i:=" <<i <<"step:= "<< h << " dcos(0.1)/dx:= " <<d_cos_forward << " relative err:= "<< relative_err << endl;
            cos_forward_output << d_cos_forward <<" "<< relative_err <<endl ;//writing out to text file
            
        }   
}

int main ( int argc, char* argv[])
 

{
    
    cos_forward_difference(0.1,0.1);
        
     

    
    
    return 0;//stop
   
}
