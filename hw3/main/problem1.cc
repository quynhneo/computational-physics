#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <complex.h>
#include <fftw3.h>


//problem 1C: inverse FFT
      
double getAverage(double arr[], int from, int size)
  {
    double sum=0;
    double avg;          

    for (int i = from-1; i < from-1 + size; ++i)
    {
      sum += arr[i];
     }

    avg = double(sum) / double(size);

    return avg;
    } 

double getSquareAverage(double arr[], int from, int size)
   {
    double sum=0;
    double sqrtAve;
    for (int i=from-1; i<from-1+size; ++i)
       {
         sum+=arr[i]*arr[i];
       }
    sqrtAve= double(sum)/double(size);
    return sqrtAve;
   }


using namespace std;
int main(int argc, char* argv[])//what are these for?
{   
//READ IN THE DATA FILE contain FFT of T and H which are both complex
    double temp[2], humid[2];
    double T[104][2];
    double H[104][2];
    double k[104];
    int line = 0;
    
    ifstream infile;
    infile.open("fft.dat");
    while(!infile.eof())
       { 
         infile>> k[line]>>temp[0]>> temp[1] >> humid[0]>>humid[1];//read line by line
         if (!infile.good()) break;
         T[line][0]=temp[0];
         T[line][1]=temp[1];
         H[line][0]=humid[0];
         H[line][1]=humid[1];
          line ++;
        }
 for (int i=0; i<104;i++)
     { cout << k[i]<<" "<<T[i][0]<<" "<< T[i][1]<<" " <<H[i][0]<<" "<<H[i][1]<<endl;
     }
//FINISH READING IN THE FILE STORED IN THE ARRay
   infile.close(); 

//OUTPUT FILE
    ofstream outfile;
    outfile.open("ifft.dat");//


// inverse FFT, USE COMPLEX without removing seasonal
     fftw_complex *Tin, *Tout, *Hin, *Hout;
     fftw_plan pT, pH;
     
     Tin = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 104);
     Tout = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *104);
      Hin = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 104);
     Hout = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *104);
     

     pT = fftw_plan_dft_1d(104, Tin, Tout, FFTW_BACKWARD, FFTW_MEASURE);
      pH = fftw_plan_dft_1d(104, Hin, Hout, FFTW_BACKWARD, FFTW_MEASURE);

     //initialize in
     for (int i=0; i<104;i++)
           { 
             Tin[i][0]=T[i][0]; 
             Tin[i][1]=T[i][1];
             Hin[i][0]=H[i][0]; 
             Hin[i][1]=H[i][1];

           }         

     fftw_execute(pT); // repeat as needed 
     fftw_destroy_plan(pT);
      fftw_execute(pH); // repeat as needed 
     fftw_destroy_plan(pH);
    
     fftw_complex *Tin2, *Tout2, *Hin2, *Hout2;
     fftw_plan pT2, pH2;
     
     Tin2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 104);
     Tout2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *104);
      Hin2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 104);
     Hout2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *104);
     
//FOURIERE TRANSFORM WIHOUT SEASONAL VARIATION
     pT2 = fftw_plan_dft_1d(104, Tin2, Tout2, FFTW_BACKWARD, FFTW_MEASURE);
      pH2 = fftw_plan_dft_1d(104, Hin2, Hout2, FFTW_BACKWARD, FFTW_MEASURE);

     //initialize in
     for (int i=0; i<104;i++)
           { 
             if (( i==2)||(i==102) ) {  Tin2[i][0]=0; 
                          Tin2[i][1]=0;
                          Hin2[i][0]=0;
                          Hin2[i][1]=0; 
                       } 

             if (( i!=2) && (i!=102)) {
                       Tin2[i][0]=T[i][0]; 
                       Tin2[i][1]=T[i][1];
                       Hin2[i][0]=H[i][0]; 
                       Hin2[i][1]=H[i][1];
             }
           }         

     fftw_execute(pT2); // repeat as needed 
     fftw_destroy_plan(pT2);
      fftw_execute(pH2); // repeat as needed 
     fftw_destroy_plan(pH2);




     //SAVE THE non seasonal INVERSE TRANSFORM IN AN ARRAY TO COMPUTE AVERAGE
    double t[104];
    double h[104];
    for (int j=0; j<104; j++)
         { 
          t[j]= sqrt(Tout2[j][0]*Tout2[j][0]+Tout2[j][1]* Tout2[j][1])/104.0 ;
          h[j]= sqrt(Hout2[j][0]* Hout2[j][0]+ Hout2[j][1]* Hout2[j][1])/104.0  ; 

         }

//part 1.c calculate average and rms
    double T_ave12;
    T_ave12= getAverage(t,1,104);cout <<"INVERSE-- T ave: "<< T_ave12<<" ";
    double H_ave12;
    H_ave12 = getAverage(h,1,104); cout<< "--ave H: "<< H_ave12<<" ";

    double T2_ave12;
    T2_ave12=getSquareAverage(t,1,104); cout << "--sqrt ave of T: " << T2_ave12<<" ";
    double H2_ave12;
    H2_ave12=getSquareAverage(h,1,104); cout << "--sqrt ave of H: "<< H2_ave12<< " ";

    double Trms12,Hrms12;
    Trms12= sqrt(T2_ave12-T_ave12*T_ave12);cout << "--Trms both year: "<<Trms12<<" ";
    Hrms12 = sqrt(H2_ave12-H_ave12*H_ave12); cout << "--H rms both year: " <<Hrms12<<" ";
    
//	SAVE THE FOURIER TRANSFROM TO OUTPUT FILE
     cout << "---inverse FFT of temperature----"<<endl;
     for (int j=0; j< 104; j++)
        {  
             cout <<j<<" "<< sqrt(Tout[j][0]*Tout[j][0]+Tout[j][1]* Tout[j][1])/104.0+23.3635 <<" " <<sqrt(Hout[j][0]* Hout[j][0]+ Hout[j][1]* Hout[j][1])/104.0 + 41.0962 <<endl; 
             outfile <<j<<" "<< sqrt(Tout[j][0]*Tout[j][0]+Tout[j][1]* Tout[j][1])/104.0 <<" " <<sqrt(Hout[j][0]* Hout[j][0]+ Hout[j][1]* Hout[j][1])/104.0 << " "<< t[j]-T_ave12 <<" " << h[j]-H_ave12  <<endl; 
          

            
         }
     

    
     fftw_free(Tin); fftw_free(Tout);
     fftw_free(Hin); fftw_free(Hout);


    cout << endl;

return 0;


		
}



