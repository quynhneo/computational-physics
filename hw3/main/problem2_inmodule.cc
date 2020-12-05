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

    avg = double(sum) / size;

    return avg;
    }
      
 

int FFT(string infilename, string outfilename, string outfilename2)
{ 
//declare the type of appropriate array

    double temp[3];
  //  double* phi=new double[100][100][2] ;//2D data, unused
    
    
    double* PHI=new double[10000];// Row major format data


    double* PHI_real=new double[10000];
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
  //       phi[line/100][line%100][0] = temp[2];
    //     phi[line/100][line%100][1] = 0;//the field is real
         PHI[line]=temp[2];//cout<< PHI[line][0]<<endl;
         PHI_real[line]=temp[2];
   //      PHI[line][1]=0;         
         //cout<<"end"<<line<<endl;
         line ++;
        }
        
         //cout<<"                 "<< temp[0]<<"                   "<<temp[1]<<" " <<temp[2]<<endl;
         //cout<<"line :  "<<line <<" x index:  " << line/100<<"  y index:  "<< line%100   <<endl;
         PHI[line]=temp[2]; cout<<"last inputline: "<< line<<" " << PHI[line]<<endl;
        // PHI[line][0]=0;         

         cout<<"again: "<< PHI[9999]<<endl;
      //   phi[line/100][line%100][0] = temp[2];
        // phi[line/100][line%100][1] = 0;



 
    
//FINISH READING IN THE FILE STORED IN THE ARRay
   infile.close(); 

//OUTPUT FILE
    ofstream outfile,outfile2;
    outfile.open(outfilename);//
	outfile2.open(outfilename2);	

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
             in[i][0]=PHI[i]-getAverage(PHI_real, 1,10000);//substract the mean from data  
             in[i][1]=0;                                     //which is not really necc. since mean near 0

           }         
      
     fftw_execute(p); // repeat as needed 
     cout<< PHI[9999]<<" " <<in[9999][1]<<endl;
     cout <<"avarage of field: "<< getAverage(PHI_real, 1,10000); 
     double* K=new double[10000];
     double* k_x=new double[10000];
     double* k_y=new double[10000];
     int i_x,i_y;     
     int J=10000;//line number

    double **spect2d;
    spect2d = new double*[100];
    for (int i=0;i<100;i++) spect2d[i] = new double[100];
    

//     double* spect2d= new double[100][100];	
     for (int j=0; j< J; j++)
        {  
	//CALCULATE Ki
         i_y = j%100;
         if (i_y < 50) { k_y[j]=2*M_PI/100.0*double(i_y);}
         else if (i_y ==50) { k_y[j]= M_PI;}
         else if (i_y >50 && i_y <100) {k_y[j]= 2*M_PI/100.0*(-50+double(i_y)-50);}
         i_x = j/100; 
         if (i_x < 50) { k_x[j]=2*M_PI/100.0*double(i_x);}
         else if (i_x ==50) { k_x[j]= M_PI;}
         else if (i_x >50 && i_x <100) {k_x[j]= 2*M_PI/100.0*(-50+double(i_x)-50);}
         K[j] = sqrt ( k_x[j]*k_x[j]+  k_y[j] *k_y[j]    );//k is only positive
	    
        spect2d[i_x][i_y] =  out[j][0]*out[j][0] + out[j][1]*out[j][1]; 
//	cout<<" inline "<<j<<"xi is: "<<i_x<<" kx is:"<< k_x[j]<<" yi is: "<<i_y<<" ky is:  "<<k_y[j]<< " k is  : " << K[j]<<endl;
            
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
              {                     if( (r*2*M_PI/100.0 < K[l] ) && ( K[l]<= (r+1)*2*M_PI/100.0  ) ) 
                   
                      { //CALCULATE POWER SPECTRUM IN HERE
                      //DEPEND ON HOW ROOT 2D PLOTS WORKS, SET UP APPROPRIATE ARRAY OF POWER SPECTRUM
                        shellVolume = shellVolume+1;
                        shellContribution = shellContribution+ out[l][0]*out[l][0] + out[l][1]*out[l][1]; 
                        //2-- save k radius to do log log plot//50 lines. do this first.
                        //NORMALIZATION ??
                     }               
              }   //end of collecting poins for the shell
             cout<< "shell volume:"<<shellVolume<<endl;
             cout << r*2*M_PI/100.0 << " " << shellContribution/double(shellVolume) <<endl;
             outfile << r*2*M_PI/100.0 << " " << shellContribution/double(shellVolume) <<endl;
     //cout<< "k in line 567:   "<< k[567]<<endl;
    //     cout<< "test: 100/100 and 100 modulo 100: "<<100/100<<" "<<100%100<<endl; 
         
	}   //end of looping through all k shell
	int a,b;//PPIRNT OUT TO PLOT	
	for (int i=0;i<100;i++)
		for (int j= 0;j<100;j++)
			{ 
			//	if (i<50) a = i+50; else a=i-50;
			//	if (j< 50) b = j+50; else b=j-50;
				outfile2 <<k_x[i*100+j]<<" "<<k_y[i*100+j]<<" "<<spect2d[i][j]<<endl;
          		}

    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);
    cout << endl;
    
    delete [] K;
    delete [] k_x;
    delete [] k_y;

    for (int i=0;i<100;i++) delete [] spect2d[i];
    delete [] spect2d;

    delete [] PHI_real;
    delete [] PHI;
    
return 0;


		
}


int main(int argc, char* argv[])//what are these for?
{ 
FFT("gaussian1.dat","gauss1fft.dat","gauss1Kplane.dat");
FFT("gaussian2.dat","gauss2fft.dat","gauss2Kplane.dat");
FFT("gaussian3.dat","gauss3fft.dat","gauss3Kplane.dat");
return 0;
} 
