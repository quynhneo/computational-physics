#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <complex.h>
#include <fftw3.h>
#include <string>

using namespace std;

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
      
 

int FFT(string infilename, string outfilename)
{ 
//declare the type of appropriate array

    double temp[3];
    double phi[100][100][2] ;//2D data, unused
    double PHI[10000][2];// Row major format data
    double PHI_real[10000];
    int line = 0;
 
//READ IN THE DATA FILE contain FFT of T and H which are both complex
    
    ifstream infile;
    infile.open(infilename);
    while(!infile.eof())
       { 
         infile>>temp[0]>>temp[1]>>temp[2] ;//read line by line
         if (!infile.good()) break;
         //cout<<"                 "<< temp[0]<<"                   "<<temp[1]<<" " <<temp[2]<<endl;
         //cout<<"line :  "<<line <<" x index:  " << line/100<<"  y index:  "<< line%100   <<endl;
         //cout<<"begin: "<<line<<"--------";
         phi[line/100][line%100][0] = temp[2];
         phi[line/100][line%100][1] = 0;//the field is real
         PHI[line][0]=temp[2];//cout<< PHI[line][0]<<endl;
         PHI_real[line]=temp[2];
         PHI[line][1]=0;         
         //cout<<"end"<<line<<endl;
         line ++;
        }
        
         //cout<<"                 "<< temp[0]<<"                   "<<temp[1]<<" " <<temp[2]<<endl;
         //cout<<"line :  "<<line <<" x index:  " << line/100<<"  y index:  "<< line%100   <<endl;
         PHI[line][0]=temp[2]; cout<<"last inputline: "<< line<<" " << PHI[line][0]<<endl;
         PHI[line][0]=0;         

         cout<<"again: "<< PHI[9999][0]<<endl;
         phi[line/100][line%100][0] = temp[2];
         phi[line/100][line%100][1] = 0;



 
    
//FINISH READING IN THE FILE STORED IN THE ARRay
   infile.close(); 

//OUTPUT FILE
    ofstream outfile;
    outfile.open(outfilename);//


//  FFT, USE COMPLEX 
     fftw_complex *in, *out;
     fftw_plan p;
     
     in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * 10000);
     out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *10000);

     p = fftw_plan_dft_2d(100, 100,
                                in, out,
                                FFTW_FORWARD, FFTW_MEASURE); 
      

     //initialize in
     for (int i=0; i<10000;i++)
           {   
		if (i%2==0)
             in[i][0]=PHI[i][0];//-getAverage(PHI_real, 1,10000);//substract the mean from data  
             else in[i][0] = 0; 
		in[i][1]=0;                                     //which is not really necc. since mean near 0
		cout<< "in put: "<< in[i][0]<<endl;
           }         
      
     fftw_execute(p); // repeat as needed 
     cout<< PHI[9999][0]<<" " <<in[9999][1]<<endl;
     cout <<"avarage of field: "<< getAverage(PHI_real, 1,10000); 
     double K[10000];
     double k_x[10000];
     double k_y[10000];
     int i_x,i_y;     
     int J=10000;//line number
     for (int j=0; j< J; j++)
        {  
	//CALCULATE Ki
         i_y = j%100;
         if (i_y < 50) { k_y[j]=2*M_PI/100.0*double(i_y);}
         else if (i_y ==50) { k_y[j]= M_PI;}
         else if (i_y >50 && i_y <100) {k_y[j]= 2*M_PI/100.0*(-50.0+double(i_y)-50.0);}
     
          i_x = j/100; 
         if (i_x < 50) { k_x[j]=2*M_PI/100.0*double(i_x);}
         else if (i_x ==50) { k_x[j]= M_PI;}
         else if (i_x >50 && i_x <100) {k_x[j]= 2.0*M_PI/100.0*(-50.0+double(i_x)-50.0);}
         K[j] = sqrt ( k_x[j]*k_x[j]+  k_y[j] *k_y[j]    );//k is only positive
         }
        //test if k is correct in any line
        cout<< "k in line 567:   "<< K[567]<<endl;
        cout<< "k in line 3478:   "<< K[3478]<<endl;

//CLEAN UP THE PLAN
    
//SET UP K SHELL AND ADD
     for (int r=1; r<50;r++)// loop through all radial bin (50)
         { //   cout << "shell at: " << r*2*M_PI/100<<endl;
              int shellVolume=0;
              double shellContribution = 0;

              for (int l=0; l<10000;l++)// for each radial bin, loop through all points
              {                     if( (r*2.0*M_PI/100.0 < K[l] ) && ( K[l]<= (r+1)*2.0*M_PI/100.0  ) ) 
                   
                      { //CALCULATE POWER SPECTRUM IN HERE
                      //DEPEND ON HOW ROOT 2D PLOTS WORKS, SET UP APPROPRIATE ARRAY OF POWER SPECTRUM
                        shellVolume = shellVolume+1;
                        shellContribution = shellContribution+ out[l][0]*out[l][0] + out[l][1]*out[l][1]; 
                        //2-- save k radius to do log log plot//50 lines. do this first.
                        //NORMALIZATION ??
                     }               
              }   //end of collecting poins for the shell
             cout<< "shell volume:"<<shellVolume<<endl;
             cout << r*2.0*M_PI/100.0 << " " << shellContribution/double(shellVolume) <<endl;
             outfile << r*2.0*M_PI/100.0 << " " << shellContribution/double(shellVolume) <<endl;
     //cout<< "k in line 567:   "<< k[567]<<endl;
    //     cout<< "test: 100/100 and 100 modulo 100: "<<100/100<<" "<<100%100<<endl; 

           
         }   //end of looping through all k shell


    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);
    cout << endl;

return 0;


		
}


int main(int argc, char* argv[])//what are these for?
{ 
FFT("gaussian1.dat","gauss1fft_coarse.dat");
FFT("gaussian2.dat","gauss2fft_coarse.dat");
FFT("gaussian3.dat","gauss3fft_coarse.dat");
return 0;
} 
