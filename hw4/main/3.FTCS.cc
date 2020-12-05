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

void LAX(double u0[], double u1[], int J, double dt, double dx, double vMax, double uMax)
{

    for (int j=0; j<J+1;j++)//go thru the grid
    {  
        int jPlus1, jMinus1;
        if (j==0) {  jMinus1 = J;   jPlus1=j+1;}
        if (j==J) {  jMinus1 = j-1; jPlus1 = 0;}
        if (j!=0 && j!=J) { jMinus1=j-1; jPlus1=j+1;}

        u1[j]=0.5*( u0[jPlus1]+ u0[jMinus1])- dt/dx/2.0*vMax*(1.0-(u0[jPlus1]+u0[jMinus1] )/uMax)*(u0[jPlus1]-u0[jMinus1]);
    }//j loop
   
}

void FTCS(double u0[], double u1[], int J, double dt, double dx, double vMax, double uMax)
{

    for (int j=0; j<J+1;j++)//go thru the grid
    {  
        int jPlus1, jMinus1;
        if (j==0) {  jMinus1 = J;   jPlus1=j+1;}
        if (j==J) {  jMinus1 = j-1; jPlus1 = 0;}
        if (j!=0 && j!=J) { jMinus1=j-1; jPlus1=j+1;}

        u1[j]= u0[j]- dt/dx/2.0*vMax*(1.0-2.0*u0[j]/uMax)*(u0[jPlus1]-u0[jMinus1]);
    }//j loop
   
}
int main(int argc, char* argv[])//what are these for?
{ 
    int J=99; 
    double L=100.0;
    double dx = L/double(J+1);
    int N=1000; 
    double dt=0.01;    
    double uMax=1.0;//max density
    double vMax=10.0;//max velocity
    double* error=new double[N];
   //ARRAY TO HOLD THE FUNCTION AT TWO CONSECUTIVE TIME 
    double *u0;
    u0 = new double[J+1];
    double *u1;
    u1 = new double[J+1];
    double **uArray;
    uArray = new double*[N];
    for (int i=0;i<N;i++) uArray[i]=new double[J+1];

    ofstream outfile1,outfile2,outfile3,outfile4;
    outfile1.open("prob3.FTCS.dat");
    outfile2.open("prob3.FTCS.error.dat");
    outfile3.open("prob3.LAX.dat");
    outfile4.open("prob3.LAX.error.dat");
//FTCS

    //SET BOUNDARY CONDITION
    for (int j =0; j<J+1; j++)
        {
                if (  j<=(J+1)/4 || j>= ((J+1)/2) )    { u0[j]=0; u1[j]=0;  }    
                else { u0[j]=uMax ; u1[j]= uMax;}     //  printf("u[ %i] = %f \n",j,u1[j]);              
        }

   for (int n=0; n<7;n++) 
    { 
        FTCS(u0,u1,J,dt,dx,vMax,uMax);

        //calculate error here 
        double temp=0;
        for (int j= 0;j<J+1;j++)
        {
              if (  fabs(u1[j]-u0[j]) > temp )  { temp = fabs(u1[j]-u0[j])  ;} 
        }
        error[n]=temp ; printf ("error at n= %i is  %f \n",n, temp);
        //UPDATE V AT STEP N 
        for (int j=0; j<J+1;j++)//go thru the grid
         {  
            u0[j]=u1[j]; //update array at n 
            uArray[n][j]= u1[j];  //save to plot
         }//j loop
        
         
     }//n loop

// final result
    for (int n=0;n<7;n++){
        for (int j=0; j<J+1;j++)//go thru the grid
        {  
            outfile1<<n<<" "<<j-(J+1)/2<<" "<< uArray[n][j]<<endl;   
        }//j loop
    }
    for (int m=0;m<7;m++) { outfile2<<m<<" "<<error[m]<<endl;}
   

//LAX   
    //SET BOUNDARY CONDITION
    for (int j =0; j<J+1; j++)
        {
                if (  j<=(J+1)/4 || j>= ((J+1)/2)  )    { u0[j]=0; u1[j]=0;  }    
                else { u0[j]=uMax ; u1[j]= uMax;}     //  printf("u[ %i] = %f \n",j,u1[j]);              
        }

   for (int n=0; n<N;n++) 
    { 
        LAX(u0,u1,J,dt,dx,vMax,uMax);
        //calculate error here 
        double temp=0;
        for (int j= 0;j<J+1;j++)
        {
              if (  fabs(u1[j]-u0[j]) > temp )  { temp = fabs(u1[j]-u0[j])  ;} 
        }
        error[n]=temp ; printf ("error at n= %i is  %f \n",n, temp);
        //UPDATE V AT STEP N 
        for (int j=0; j<J+1;j++)//go thru the grid
         {  
            u0[j]=u1[j]; //update array at n 
            uArray[n][j]= u1[j];  //save to plot
         }//j loop
         
     }//n loop

// final result
    for (int n=0;n<N;n++){
        for (int j=0; j<J+1;j++)//go thru the grid
        {  
            outfile3<<n<<" "<<j<<" "<< uArray[n][j]<<endl;   
        }//j loop
    }
    for (int m=0;m<N;m++) { outfile4<<m<<" "<<error[m]<<endl;}
   
    delete [] error;
    delete [] u0;
    delete [] u1;
    for (int i=0;i<N;i++) delete [] uArray[i];
    delete [] uArray;
    return 0;

} 
