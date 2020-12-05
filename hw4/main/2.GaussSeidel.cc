#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <complex.h>
#include <fftw3.h>
#include <string>
#include <random>
using namespace std;

int main(int argc, char* argv[])//what are these for?
{ 
    int J=99; int L=99;   int N=2000;
    int gridSize=(J+1)*(L+1);
    double dx = 1.5/double(J+1);  double dy =2.0/double(L+1);
    double* error=new double[N];
   //ARRAY TO HOLD THE FUNCTION AT TWO CONSECUTIVE TIME 
    double **v0;
    v0 = new double*[J+1];
    for (int i=0;i<J+1;i++) v0[i] = new double[L+1];

    double **v1;
    v1 = new double*[J+1];
    for (int i=0;i<J+1;i++) v1[i] = new double[L+1];

    ofstream outfile1,outfile2;
    outfile1.open("prob2.GS.dat");
    outfile2.open("prob2.GS.error.dat");
    //SET BOUNDARY CONDITION
    for (int j =0; j<J+1; j++)
        {
        for (int l=0; l<L+1; l++)
            {
                if ( (j==0) || (j==L) || ( l==0) || (l==L) ||  ( (double(l)*dy)  < (1.5 -2.0*dx*double(j)) ) ||
                  ( (double(l)*dy)  > (2.75-1.5*dx*double(j)) )     
                   ) 
                    { v0[j][l]=0; v1[j][l]=0;  }                          
            }
        }

//TIME iteration Gauss seidel
   for (int n=0; n<N;n++) 
    { 
        for (int j=0; j<J+1;j++)//go thru the grid
         {  
            for (int l=0;l<L+1;l++){
                if ( (j!=0) && (j!=L) && ( l!=0) && (l!=L) && //IF INTERIOR
                     ( (double(l)*dy)  >= (1.5 -2.0*dx*double(j)) )&&
                    ( (double(l)*dy)  <= (2.75-1.5*dx*double(j)) )    )
                     {  
                         v1[j][l]=( (v0[j+1][l] + v1[j-1][l]  ) *dy*dy +
                                  (v0[j][l+1] + v1[j][l-1]  ) *dx*dx -
                                   dx*dx*dy*dy ) /2.0/(dx*dx+dy*dy);  
                     }  
            }//l loop
         }//j loop
   
        //calculate error here 
        double temp=0;
        for (int j= 0;j<J+1;j++)
        {
            for (int l=0;l<L+1;l++)
            {  if ((fabs(v1[j][l]-v0[j][l])) > temp) { temp = (fabs(v1[j][l]-v0[j][l]));} }   
        }
        error[n]=temp ; printf ("error at n= %i is  %f \n",n, temp);
        //UPDATE V AT STEP N 
        for (int j=0; j<J+1;j++)//go thru the grid
         {  
            for (int l=0;l<L+1;l++){
                
             if ( (j!=0) && (j!=L) && ( l!=0) && (l!=L) && //IF INTERIOR
                     ( (double(l)*dy)  >= (1.5 -2.0*dx*double(j)) )&&
                    ( (double(l)*dy)  <= (2.75-1.5*dx*double(j)) )    )
                     {   v0[j][l]=v1[j][l];   } 
            }//l loop
         }//j loop
   
     }//n loop

// final result

    for (int j=0; j<J+1;j++)//go thru the grid
    {  
        for (int l=0;l<L+1;l++){
            outfile1<<j<<" "<<l<<" "<<v1[j][l]<<endl;   
        }//l loop
    }//j loop
    for (int m=0;m<N;m++) { outfile2<<m<<" "<<error[m]<<endl;}
   
    delete [] error;
    for (int i=0;i<J+1;i++) delete [] v0[i];
    delete [] v0;
    for (int i=0;i<J+1;i++) delete [] v1[i];
    delete [] v1;

    return 0;

} 
