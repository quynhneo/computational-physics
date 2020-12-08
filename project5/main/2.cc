#include <iostream>
#include <random>
#include <math.h>
#include <iomanip>
#include <fstream>

using namespace std;
double jump( double v, double dv)//imposing boundary condition
{
    if (v+dv > 0 ) { v=v+dv;}
    //else { v=0;   } 
    return v;
}
int main(int argc, char* argv[])

{
    int N=200; double epsilon = 0.920703; double T=0.5 ; int run=500;
    double *u;
    u = new double[N];
    double *equiU;
    equiU = new double[N*run];
    double *allU;
    allU = new double[N*run];
    double **array;
    array = new double*[N*run];
    for (int j=0;j<N*run;j++) { array[j] = new double[N];}
    
    ofstream outfile,outfile2, outfile3;
    outfile.open("p2.dat");
    outfile2.open("p2C.dat");
    outfile3.open("p2H.dat");
    //random number : uniform 
    std::random_device rd;
    std::default_random_engine generator( rd());
    std::uniform_real_distribution<double> random(0.0,1.0);
    std::uniform_int_distribution<int> randInt(0,N);//random particle 
    std::uniform_real_distribution<double> random2(-1.0*epsilon,epsilon);//define jumping interval
    cout<< random(generator)<<endl;

    //initialize the state
    for (int i=0; i<N;i++) { u[i] = 1.0; array[0][i]=1.0;  }     
    double totalU=N*1.0; 
    //the main loop - Metropolis monte carlo
    double aveU=0; double aveAll=0; 
    int cut=N*run/2; 
    int count=0;
    for (int n=0;n<N*run;n++)
    {   int i; //pick a random particle
        i = randInt(generator) ;   //divide by integer to get integer 
        double deltaU ;//change in energy 
        double tempo=u[i];//hold potential before change
        deltaU = random2(generator);// pick a random jump`
       cout<< n/1000  << endl;
    //monte carlo 
        if (deltaU<=0) { u[i]=jump(u[i],deltaU) ;}
            else {  if ( random(generator)< exp(-1.0*deltaU/T)) { u[i]=jump(u[i],deltaU) ;}
                 }
        totalU = totalU + u[i]-tempo  ;
        outfile << n << " "<< totalU<<endl; //cout <<"."<<endl;
    //calculate average after equilibrium    
        allU[n]=totalU;
        if (n>= cut) { aveU= aveU+ totalU  ; 
                     }
        //aveAll=aveAll+totalU;
//        int corr_time=1500;
//        if (n>=cut && n%corr_time==0) { for (int p=0;p<N;p++) { outfile3<<u[p]<<endl;}}//save to hist
        for (int p=0;p<N;p++) { array[n][p]= u[p];} 
    
    }//Monte carlo  loop end
    
    aveU= aveU/double(N*run-cut);//average after equilibrium
    outfile<< cut <<" "<< aveU <<endl;//save the mean to plot 
    //  aveAll= aveAll/double(N*run);//average of all run
    double rmsCut=0.0; // STATISTIC LOOP
    double *C; double rmsAll=0.0;
    C= new double[N*run]; 
    for (int i=0;i< N*run ;i++)  {  //move this to all steps in main loop 
            if (i<N*run-cut) {rmsCut = rmsCut + (allU[cut+i]-aveU)*(allU[cut+i]-aveU);}
           // rmsAll = rmsAll + (allU[i]-aveU)*(allU[i]-aveU);
        }
    rmsCut = sqrt(rmsCut / double( N*run-cut));//LARGER THAN IN R 
  //  rmsAll =sqrt(rmsAll/ double(N*run));
    printf("average after equi : %f and rms %f \n",aveU, rmsCut);
    double diff=1.0-1.0/exp(1); //see how close c[m] is to correlation value
    int correlation_step=0;
    for (int m=0;m<N*run-cut;m++)  {  
            C[m]=0; count=0;//find C[m] loop
            for (int n=0;n<N*run-cut-m;n++) {
                C[m]= C[m] + (allU[n+cut]-aveU)*(allU[n+cut+m]-aveU); count=count+1;
            }
            C[m]=C[m]/rmsCut/rmsCut/double(N*run-cut-m );  outfile2 << m <<" " << C[m]<<endl; 
            if ( (abs( C[m]-C[0]/exp(1))< diff )  && ( m< 10000)  ) { diff=abs( C[m]-C[0]/exp(1)); correlation_step=m; } //find minimum distance from correlation value to decide correlation time
    }
    cout<< "correlation step " << correlation_step<<endl; cout<< "c [0]: "<< C[0]<<endl;
    for (int n=0;n<N*run;n++) {
    //after equilibrium time, save data after every correlation steps to histogramming 
    if (n>=cut && n%correlation_step  ==0) { for (int p=0;p<N;p++)  outfile3<<array[n][p]<<endl;}//save to hist
    }
    outfile2<<correlation_step<<" "<<C[correlation_step]<< endl;//mark this to plot
     delete [] u; delete [] equiU; delete [] C; delete [] allU;
    for (int i=0;i<N*run;i++) delete [] array[i];
    delete [] array;
    return 0;
}

