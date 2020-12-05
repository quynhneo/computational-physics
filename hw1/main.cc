#include <iostream>
#include "include/cos_forward_difference.hh"//each problem per module
#include "include/cos_center_difference.hh"
#include "include/cos_extrapolation_header.hh"
#include "include/exp_forward_difference.hh"
#include "include/exp_center_difference.hh"
#include "include/exp_extrapolation_header.hh"

using namespace std;

//float epsilon_m = 0.0000001; //machine precision

int main ( int argc, char* argv[])
 

{
    
    //d_cos::cos_forward_difference(10,0.1);
    //d_cos::cos_center_difference(0.1,0.1);// argument pair: (x,h)
    //d_cos::cos_extrapolated_difference(0.1,1);
    
    //d_exp::exp_forward_difference(0.1,0.1);
    //d_exp::exp_center_difference(10,1);// argument pair: (x,h)
    d_exp::exp_extrapolated_difference(10,10);
    
    return 0;//stop
   
}
