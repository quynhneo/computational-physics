#include <iostream>

#include <math.h>
#include <stdlib.h>
#include <fstream>

#include "../include/random_include.hh"

namespace randomness
{

using namespace std;

void random (long int n_r,long int n_max  ) //integral range a,b and initial number of interval 
{
    ofstream s2file;
    s2file.open("sigma2.dat");//name of output textfile

 const unsigned long int a= 9301; cout << "a=" << a<<" ";
 const unsigned long int c=   49297; cout << "c="<< c <<" "; 
 const unsigned long int m= 233280; cout << "m= "<< m <<" "<<endl;
 long int table[n_r][n_max];// store value of each 500 step for every seed

 for (long int k = 1; k< n_r +1; k++) //loop over 1000 seed
{   
    long int i=k;//k act as the seed
    
    long int x_j=0; //initial location
   
  //  long double sum=0; // use to calculate average
    
    cout<< "seed:="<<k<<" ";
    for (long int j=1; j < n_max +1 ; j++) // start walking 500 steps
    {
        
        i = (a * i + c)% m; //generate a pseudo-random number
        //cout << "rand number: " << i <<endl;
        
        if (i >= (m/2)){x_j++;} //step right if the random number > m/2
        else {x_j= x_j - 1 ;} //step left is the random number < m/2
        cout <<" " << x_j<<" ";
        
        table[k][j]= x_j;//save j step into the table
        
    }// walk loop end
  
    cout<<"  final position: "<< x_j <<" "<<endl ;   
    
}//seed loop end
    
    //CALCULATE SIGMA
    long double sigma2;
    long double x_ave;
     long double x3_ave;
     long double x4_ave;
      long double sigma3;
      long double sigma4;
    
    for (long int j =1; j< n_max+1; j++) //for each of 500 colum of x_j
    {
        
        long double sum1=0;
  
      //  cout << "step number: "<< j<<" ";
        
        for (long int k =1; k< n_r +1; k++ ) // this loop is for calculating x average use for later
        { 
      //     cout <<" " <<table[k][j]<<" ";
           sum1 = sum1+table[k][j];
        } 
       
        x_ave=sum1/n_r;

        long double sum2=0;
        long double sum3=0;
        long double sum4=0;
        long double sum_cube=0;
        long double sum_four=0;
        
        for (long int k =1; k< n_r +1; k++ ) 
        {
            sum2 = sum2 + table[k][j] * table[k][j]; //x^2 accumulate sum
            sum_cube=sum_cube+table[k][j]*table[k][j]*table[k][j]; //x^3 accumulate sum
            sum_four=sum_four+table[k][j]*table[k][j]*table[k][j]*table[k][j];//x^4 accumulate sum
            sum3= sum3 + (table[k][j]-x_ave)*(table[k][j]-x_ave)*(table[k][j]-x_ave);//sigma3 accumulate
            sum4= sum4 + (table[k][j]-x_ave)*(table[k][j]-x_ave)*(table[k][j]-x_ave)*(table[k][j]-x_ave);//sigma4 accumulate
        }
        
        x3_ave=sum_cube/n_r;
        x4_ave=sum_four/n_r;
        sigma2 = sum2/n_r;
        sigma3 = sum3/n_r;
        sigma4 = sum4/n_r;
        
        
        //cout <<"  sigma2 is  "<< sigma2 <<endl;
        s2file<<j<<" "<<sigma2<<" "<<x3_ave/sigma3<< " "<< (x4_ave/sigma4-3) << endl;//step,sigma2,s3,s4 in order
    }//end of j loop
    return ;

}//end of random


}//namespace
