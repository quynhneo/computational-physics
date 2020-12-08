#include <iostream>
#include <random>
#include <math.h>
#include <iomanip>
#include <fstream>

using namespace std;


int main(int argc, char* argv[])

{
    
    int L=50;
    int N=1000;
    double T=1.0;
    double **lattice;
    lattice = new double*[L];
    for (int i=0; i<L;i++) lattice[i] = new double[L];
    ofstream outfile,outfile2;
    outfile.open("p1.dat");

//random number : uniform 
    std::random_device rd;
    std::default_random_engine generator( rd());
    std::uniform_real_distribution<double> random(0.0,1.0);
    cout<< random(generator)<<endl;

//initialize a random state
    for (int i=0; i<L;i++)
       { for (int j=0;j<L;j++)
            { 
                if (random(generator) <0.5) {lattice[i][j]=1.0;}//RE NORMALIZE !
                else { lattice[i][j]=-1.0;}
        //       printf("s %i %i is %f  \n ", i, j, lattice[i][j]);
            }        
        }
//the main loop
    for (int n=0;n<N*L*L;n++)
    {   int i,j; //pick a random coordinate
        i = random(generator)*L/1 ;   j = random(generator)*L/1; //divide by integer to get integer 
        double deltaU, up, down, left, right;
        if (i == 0) { left =0; right = lattice[i+1][j];}
        if (i == L-1) { left = lattice[i-1][j]; right =0;}
        if (i != 0 && i!=L-1) { left = lattice[i-1][j]; right = lattice[i+1][j];}

        if (j == 0) { up = lattice[i][j+1]; down = 0;}
        if (j == L-1) { up = 0; down  = lattice[i][j-1];}
        if (j != 0 && j!=L-1) { up = lattice[i][j+1]; down  = lattice[i][j-1];}
        //check if delta U is correct
        deltaU = lattice[i][j]*2.0*( up + down + left + right);// printf("up %f; down %f; left %f; right %f ",up,down,left, right);
        cout<< n << " del U " <<deltaU <<endl;
   //monte carlo 
        if (deltaU<=0) { lattice[i][j]=-1.0*lattice[i][j];}
            else {  if (random(generator)< exp(-1.0*deltaU/T)) { lattice[i][j]=-1.0*lattice[i][j];}
                 }
    }

//output
    for (int i=0; i<L;i++) {  for (int j=0;j<L;j++)  { outfile<<i<<" "<<j<<" "<<lattice[i][j]<<endl; }        
     }

    for (int i=0;i<L;i++) delete [] lattice[i];
    delete [] lattice;
    return 0;
}

