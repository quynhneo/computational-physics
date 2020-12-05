#include <iostream>
#include "include/integral_trapezoid_include.hh"
#include "include/integral_simpson_include.hh"
#include "include/integral_gaussian_include.hh"

using namespace std;

//float epsilon_m = 0.0000001; //machine precision

int main ( int argc, char* argv[])
 

{
    
 //   integral::integral_simpson(1,0,1,2,15);
//      integral::integral_trapezoid(1,0,1,2,10);
    integral::integral_gaussian(1,0,1);
    
    return 0;//stop
   
}
