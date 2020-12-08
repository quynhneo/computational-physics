#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <complex.h>
#include <fftw3.h>


      
double getAverage(double arr[], int from, int size)
  {
    double sum=0;
    double avg;          

    for (int i = from-1; i < from-1 + size; ++i)
    {
      sum += arr[i];
     }

    avg = double(sum) / (size);

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
    sqrtAve= double(sum)/(size);
    return sqrtAve;
   }


using namespace std;
int main(int argc, char* argv[])//what are these for?
{   
//READ IN THE DATA FILE
    double temp, humid;
    double TandH[104][2];//will store temparature and himidity here
    double T[104];
    double H[104];
    int line = 0;
    
    ifstream infile;
    infile.open("TandH.dat");
    while(!infile.eof())
       { 
         infile>> temp >> humid;//read line by line
         if (!infile.good()) break;
         cout<< " begin loop"<<line << endl;         
         TandH[line][0]=temp;//save to array
         T[line]=temp;
         TandH[line][1]=humid;//save to array
         H[line]=humid;
         cout<<"end loop"<< line <<endl;
         line ++;        }
//FINISH READING IN THE FILE STORED IN THE ARRAY TandH[104][2]
cout<< "last 2  temp: " << T[102]<<" " <<T[103];    

//OUTPUT FILE
    ofstream outfile;
    outfile.open("1a.dat");//

    //for (int i =0; i<104; i++)//print out to test
    //   { outfile<<i<<" "<<TandH[i][0]<< " " <<TandH[i][1]<<endl;  }

//part 1.a. calculate average and rms
    double T_ave12;
    T_ave12= getAverage(T,1,104);cout <<"-- T ave: "<< T_ave12<<" ";
    double H_ave12;
    H_ave12 = getAverage(H,1,104); cout<< "--ave H: "<< H_ave12<<" ";

    double T2_ave12;
    T2_ave12=getSquareAverage(T,1,104); cout << "--sqrt ave of T: " << T2_ave12<<" ";
    double H2_ave12;
    H2_ave12=getSquareAverage(H,1,104); cout << "--sqrt ave of H: "<< H2_ave12<< " ";

    double Trms12,Hrms12;
    Trms12= sqrt(T2_ave12-T_ave12*T_ave12);cout << "--Trms both year: "<<Trms12<<" ";
    Hrms12 = sqrt(H2_ave12-H_ave12*H_ave12); cout << "--H rms both year: " <<Hrms12<<" ";
    
    cout<< "first year:----------------"<<endl;

   double T_ave1;
    T_ave1= getAverage(T,1,52);cout <<"--1st T ave: "<< T_ave1<<" ";
    double H_ave1;
    H_ave1 = getAverage(H,1,52); cout<< "--1st ave H: "<< H_ave1<<" ";

    double T2_ave1;
    T2_ave1=getSquareAverage(T,1,52); cout << "--sqrt ave of1st T: " << T2_ave1<<" ";
    double H2_ave1;
    H2_ave1=getSquareAverage(H,1,52); cout << "--sqrt ave of 1st H: "<< H2_ave1<< " ";

    double Trms1,Hrms1;
    Trms1= sqrt(T2_ave1-T_ave1*T_ave1);cout << "--Trms first year: "<<Trms1<<" ";
    Hrms1 = sqrt(H2_ave1-H_ave1*H_ave1); cout << "--H rms 1st year: " <<Hrms1<<" ";
    
    cout<< "second year--------"<<endl;
   
  
    double T_ave2;
    T_ave2= getAverage(T,53,52);cout <<"--2nd T ave: "<< T_ave2<<" ";
    double H_ave2;
    H_ave2 = getAverage(H,53,52); cout<< "--2nd ave H: "<< H_ave2<<" ";

    double T2_ave2;
    T2_ave2=getSquareAverage(T,53,52); cout << "--sqrt ave of 2nd T: " << T2_ave2<<" ";
    double H2_ave2;
    H2_ave2=getSquareAverage(H,53,52); cout << "--sqrt ave of 2nd H: "<< H2_ave2<< " ";

    double Trms2,Hrms2;
    Trms2= sqrt(T2_ave2-T_ave2*T_ave2);cout << "--Trms 2nd year: "<<Trms2<<" ";
    Hrms2 = sqrt(H2_ave2-H_ave2*H_ave2); cout << "--H rms 2nd year: " <<Hrms2<<" ";
    

    cout << endl;


   //writing out an output file for Fourier transform, removing seasonal variation     
    ofstream outfile2;
    outfile2.open("fft.dat");//

//FFT, USE COMPLEX
     fftw_complex *Tin, *Tout, *Hin, *Hout;
     fftw_plan pT, pH;
     
     Tin = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 104);
     Tout = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *104);
      Hin = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 104);
     Hout = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *104);
     

     pT = fftw_plan_dft_1d(104, Tin, Tout, FFTW_FORWARD, FFTW_MEASURE);
      pH = fftw_plan_dft_1d(104, Hin, Hout, FFTW_FORWARD, FFTW_MEASURE);

     //initialize in
     for (int i=0;i<104;i++)
           { Tin[i][0]=T[i]-T_ave12; //substract the mean out, removing k=0 mode
             Tin[i][1]=0;//the ogrinal data is real, so input array is real
             Hin[i][0]=H[i]-H_ave12; 
             Hin[i][1]=0;

           }         


     fftw_execute(pT); /* repeat as needed */
     fftw_destroy_plan(pT);
      fftw_execute(pH); /* repeat as needed */
     fftw_destroy_plan(pH);


     double k[104];
     cout << "---FFT of temperature----"<<endl;
     for (int j=0; j< 104; j++)
        {  
           if (j<52) { k[j]=2.0*M_PI/104.0*j;}
           else if (j==52) { k[j] = M_PI;}
           else if ( j>52 && j<104) { k[j] = 2.0*M_PI/104.0*(-52.0+j-52.0);}
       
             cout <<j<<" "<<T[j]<<" " << H[j]<<" "<<k[j]<<" "<<2*( Tout[j][0]*Tout[j][0]+Tout[j][1]*Tout[j][1])<<" "<< 2*( Hout[j][0]*Hout[j][0]+Hout[j][1]*Hout[j][1])<<endl; 
          
            //calculate k from j and write to output file
            
            outfile <<j<<" "<<T[j]<<" " << H[j]<<" "<<k[j]<<" "<<2*( Tout[j][0]*Tout[j][0]+Tout[j][1]*Tout[j][1])<<" "<< 2*( Hout[j][0]*Hout[j][0]+Hout[j][1]*Hout[j][1])<<endl; 
            outfile2 <<k[j]<<" "<<Tout[j][0]<<" "<<Tout[j][1]<<" "<< Hout[j][0]<<" "<<Hout[j][1]<<endl; 
         }
     

    
     fftw_free(Tin); fftw_free(Tout);
     fftw_free(Hin); fftw_free(Hout);


return 0;


		
}



