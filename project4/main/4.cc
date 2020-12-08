#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <complex>
#include <fftw3.h>
#include <string>
#include <random>
#include <cmath>

using namespace std;
typedef complex<double> mycomplex;
double alpha =0.001;
const int M=20;
int L=40;
double k[M+1];
mycomplex dt(0.1,0.0);
mycomplex I(0.0,1.0);

void createK()
{
    for (int i=0;i<2*M+1;i++)//from 0 to 40
    {
        int n_k;
        if (i<=20){ n_k= i;}
        if (i>20) { n_k= M-i;}
        k[i]= double(n_k)*M_PI/double(L);
    }
}

mycomplex* f(mycomplex c[] )//the right hand side of ODE

{     
     mycomplex* F =new mycomplex[M+1];
    for (int n=0;n<M+1;n++) //for every positive n element of c from 0 to 20
    { 
        mycomplex sum =  alpha*I*k[n]*k[n]*k[n]*c[n];
        for (int i=0;i<2*M+1;i++)         {   
           if (i<M+1)//loop for positive n_p, k is positive, from 0 to 20
                {   
                int n_p = i;
                if (n>=n_p)  sum= sum- c[n-n_p]*c[n_p]*I*k[n_p];//use positive n prime only
                else  sum= sum- conj(c[n_p-n])*c[n_p]*I*k[n_p];//use positive n prime only
                }
           else      //from 21 to 40, n_p from -1 to -20, k is negative
            {
                int np=M-i;//get negative index
                if (n-np<M+1) //limit to 20 modes only
                   { sum= sum- c[n-np]*conj(c[i-M])*I*k[i];}//abs use only positive n prime
            }
        }
        F[n]=  sum ;
    }//end of n from 0 -20 loop
    return F;
}

mycomplex* devideBy2(mycomplex ki[], int size )
{
    mycomplex* holder = new mycomplex[size];
    for (int i=0;i<size;i++) {  holder[i]=ki[i]/2.0;  }
    return holder;
}

mycomplex* add(mycomplex a[], mycomplex b[], int size)
{
    mycomplex* c= new mycomplex[size];
    for (int i=0;i<size;i++) { c[i]=a[i]+b[i];}
    return c;
}
    

mycomplex* RK4step(mycomplex c[] )
{
    mycomplex k1[M+1];
    mycomplex k2[M+1];
    mycomplex k3[M+1];
    mycomplex k4[M+1];
    for (int i=1;i<M+1;i++) //integrate only postive n for the c array
    {   k1[i]=f(c)[i]*dt;
        k2[i]=f(add(c,devideBy2(k1,M+1),M+1) )[i]*dt;
        k3[i]=f(add(c,devideBy2(k2,M+1),M+1) )[i]*dt;
        k4[i]=f(add(c,k3,M+1))[i]*dt; 
    c[i]=c[i]+(k1[i]+2.0*k2[i]+2.0*k3[i]+k4[i])/6.0;}
    return c;//integrate only postive n for the c array
}


int main(int argc, char* argv[])//what are these for?
{ 
    ofstream outfile1;
    outfile1.open("prob4.powSpect.dat");
    
    //array of c
    createK(); 
    mycomplex* c=new mycomplex[M+1]; //41 element from n=-20 to 20
    //initial condition
    c[1]=1.0/16.0; cout << "c[1]"<< c[1]<<endl;
    for (int i=0;i<M+1;i++)   
        {   if (i!=1 ) { c[i]=0;} 
            printf("n= %i,k=%f",i,k[i] ) ;
            cout<<"  iini c: "<<c[i]<<endl; }
    
    for (int t=0 ; t<2000;t++)
        {  
            RK4step(c); //integrate positive c
        }// move forward in time 

    for (int i= 0;i<M+1;i++) 
     { cout << "final c at n:= "<<i<<" "<<c[i]<<endl;
        outfile1<<i<<" "<<k[i]<<" "<<norm(c[i])<<" "<<c[i].real()<<" "<<c[i].imag()  <<endl;        }
 /*  cout << "---------a-------"<<endl<<std::fixed;
    for (int i= 0;i<2*M+1;i++) { cout<<setprecision(10) << c[i].real()<<",";}
    cout << "-------b------"<<endl;
    for (int i= 0;i<2*M+1;i++) { cout<<setprecision(10)<<fabs( c[i].imag()) <<",";}
   */ 
delete [] c;
     return 0;
    
} 
