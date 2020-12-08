#include <iostream>
#include <random>
#include <math.h>
#include <iomanip>
#include <fstream>

using namespace std;


int main(int argc, char* argv[])

{
    
    int L=50;
    int N=1000; int t=50*4; double Tmax=5.0;
    double T[t];//={0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5,5.5,6,6.5,7,7.5,8,8.5,9,9.5};
    for (int i=0; i<t;i++) { if (i==0)  {T[i]=0.000000001; }
                                else { T[i] = double(i)* Tmax/double(t);}}
    double **lattice;
    lattice = new double*[L];
    for (int i=0; i<L;i++) lattice[i] = new double[L];
    ofstream outfile;
    outfile.open("p1.manyT.dat");

//random number : uniform 
    std::random_device rd;
    std::default_random_engine generator( rd());
    std::uniform_real_distribution<double> random(0.0,1.0);
    std::uniform_int_distribution<int> random2(0,49);
    cout<< random2(generator);
//the main loop
for (int t=0;t<50*4;t++) { //100 temperature points
    double sum=0;
    double magnetization=0;//reset 
    for (int l=0;l<5;l++) { 
        //initialize a random state
        for (int a=0; a<L;a++)
        {   for (int b=0;b<L;b++) { 
                if (random(generator) <0.5) {lattice[a][b]=1.0;}//RE NORMALIZE !
                else { lattice[a][b]=1.0;}       }        
        }
        for (int n=0;n<N*L*L;n++)
            {   int i,j; //pick a random coordinate
            i = random2(generator) ;   j = random2(generator); //divide by integer to get integer 
            double deltaU, up, down, left, right;// the neighbors
            if (i == 0) { left =0; right = lattice[i+1][j];}
            if (i == L-1) { left = lattice[i-1][j]; right =0;}
            if (i != 0 && i!=L-1) { left = lattice[i-1][j]; right = lattice[i+1][j];}

            if (j == 0) { up = lattice[i][j+1]; down = 0;}
            if (j == L-1) { up = 0; down  = lattice[i][j-1];}
            if (j != 0 && j!=L-1) { up = lattice[i][j+1]; down  = lattice[i][j-1];}
            //check if delta U is correct
            deltaU = lattice[i][j]*2.0*( up + down + left + right);// printf("up %f; down %f; left %f; right %f ",up,down,left, right);
            // cout<< n << " del U " <<deltaU <<endl;
            //monte carlo 
            if (deltaU<=0) { lattice[i][j]=-1.0*lattice[i][j];}
            else {  if (random(generator) < exp(-1.0*deltaU/T[t])) { lattice[i][j]=-1.0*lattice[i][j];}
                 }
        }//n loop
        //output
        magnetization=0;//reset mag for this l
        for (int i=0; i<L;i++) {  for (int j=0;j<L;j++)  { magnetization = magnetization+lattice[i][j]; }  }
        sum=sum+abs(magnetization);
    }//5 times average loop
    outfile << T[t]<<" " <<sum/2500.0/5.0 <<endl;
    cout<< T[t]<<" " <<sum/2500.0/5.0<<endl;

}//t loop`

    for (int i=0;i<L;i++) delete [] lattice[i];
    delete [] lattice;
    return 0;
}

