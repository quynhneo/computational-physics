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
      
 

int FFT(string infilename, string outfilename, string Fft3DOutName, int Ngrid, double binsize, int N, int window)
{ 
//declare the type of appropriate array
     int GridVolume = Ngrid * Ngrid * Ngrid ; cout<< "volume ok \n"; 
    int line = 0;
//READ IN THE DATA FILE contain FFT of density  a
//OUTPUT FILE
     ofstream outfile;
     outfile.open(outfilename);//

//  FFT, USE COMPLEX 
     fftw_complex *in, *out;
     fftw_plan p;
     
     in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * GridVolume);
     out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *GridVolume);

     p = fftw_plan_dft_3d(Ngrid, Ngrid,Ngrid,
                                in, out,
                                FFTW_FORWARD, FFTW_MEASURE); 
     
    ifstream infile; cout<< "start open infile\n";
    infile.open(infilename);
    double temp=0; 
    while(!infile.eof())
       { 
         infile>>temp;
        in[line][0]=temp-double(N)/double(GridVolume) ;//read line by line x y z density
         in[line][1]=0;
         if (!infile.good()) break;
         line ++;
        }
    cout<< "read in OK"<<endl;        
    cout<<"again next to last input line: "<< in[line-2]<<endl;
   
//FINISH READING IN THE FILE STORED IN THE ARRay
    infile.close(); 
    cout << "initialization OK, now execute FFT..."<<endl;
     fftw_execute(p); // repeat as needed 
     cout<< "FFt done, next to last density line read in " <<in[Ngrid*Ngrid*Ngrid-2][1]<<endl;
    // cout <<"avarage of field: "<< getAverage(PHI, 1,GridVolume); 
     double* K= new double[GridVolume]; //each line, exists a kx ky kz
     double* k_x= new double[GridVolume];
     double* k_y= new double[GridVolume];
     double* k_z= new double[GridVolume];
     double* W_x = new double[GridVolume]; 
     double* W_y = new double[GridVolume]; 
     double* W_z = new double[GridVolume]; 
     int i_x,i_y,i_z;     
     int J=GridVolume;//line number
//3d power histogram array
     double ***spect3d;
    spect3d = new double**[Ngrid];
    for (int i=0;i<Ngrid;i++)   
        {
            spect3d[i] = new double*[Ngrid];
            for (int j=0; j<Ngrid; j++)
               spect3d[i][j]= new double[Ngrid];
        }

     ofstream Fft3DOut;
     Fft3DOut.open(Fft3DOutName);//

     for (int j=0; j< J; j++)//go thru all density grid point, find kx, ky,kz and K base one line number. 
        {  
	//CALCULATE Ki
         i_z=j%Ngrid ;
         if (i_z <= Ngrid/2) { k_z[j]=2.0*M_PI/double(Ngrid)*i_z;}
         //else if (i_z ==Ngrid/2) { k_z[j]= M_PI;}
         //else if (i_z > Ngrid/2 && i_z <Ngrid)
         else {k_z[j]= 2.0*M_PI/double(Ngrid)*(i_z-Ngrid);}
        
         i_y=( (j-i_z)/Ngrid )%Ngrid ;
         if (i_y <= Ngrid/2) { k_y[j]=2.0*M_PI/double(Ngrid)*i_y;}
         //else if (i_y ==Ngrid/2) { k_y[j]= M_PI;}
         //else if (i_y > Ngrid/2 && i_y <Ngrid)
         else  {k_y[j]= 2.0*M_PI/double(Ngrid)*(i_y-Ngrid);}
         
         i_x=( ( (j-i_z)/Ngrid ) - i_y  )/Ngrid ;
         if (i_x <= Ngrid/2.0) { k_x[j]=2.0*M_PI/double(Ngrid)*i_x;}
         //else if (i_x ==Ngrid/2) { k_x[j]= M_PI;}
        // else if (i_x > Ngrid/2 && i_x <Ngrid) 
         else {k_x[j]= 2.0*M_PI/double(Ngrid)*(i_x-Ngrid);}
    //     printf ("cal ki %i \n",j);
        
         K[j] = sqrt ( k_x[j]*k_x[j]+  k_y[j] *k_y[j] *k_z[j]*k_z[j]   );//k is only positive
        //CALCULATE FFT OF  WINDOW FUNCTION 
        if (window==1) {
                 if (k_x[j]==0) {W_x[j] =1;} else if (k_x[j] !=0){ W_x[j]= ( sin(k_x[j]*binsize*0.5 ) / (k_x[j]*binsize*0.5 )        ) * ( sin(k_x[j]*binsize*0.5 ) / (k_x[j]*binsize*0.5 )   )  ;}
                 if (k_y[j]==0){ W_y[j] =1;} else if (k_y[j] !=0) { W_y[j] =  ( sin(k_y[j]*binsize*0.5 ) / (k_y[j]*binsize*0.5     )    )*  ( sin(k_y[j]*binsize*0.5 ) / (k_y[j]*binsize*0.5 )    )  ;}
                 if (k_z[j]==0) {W_z[j]=1;} else if (k_z[j] !=0) { W_z[j] = ( sin(k_z[j]*binsize*0.5 ) / (k_z[j]*binsize*0.5 )        ) * ( sin(k_z[j]*binsize*0.5 ) / (k_z[j]*binsize*0.5 )    ) ;} 
         };
        //SAVE 3D Histogram
        if (window==1)
        spect3d[i_x][i_y][i_z] = ( out[j][0]*out[j][0] + out[j][1]*out[j][1])/W_x[j]/W_y[j]/W_z[j]/W_x[j]/W_y[j]/W_z[j];
        else  spect3d[i_x][i_y][i_z] = ( out[j][0]*out[j][0] + out[j][1]*out[j][1]);
        Fft3DOut <<k_x[j]<<" "<<k_y[j]<<" "<<k_z[j]<<" "<<spect3d[i_x][i_y][i_z]<<endl;
 
        //else { W_x[j]=1; W_y[j]=1; W_z=1;}
    }//end of k w loop
   cout<< "\n k xyz and Kndex calculated"<<endl; 

        cout<< "k in line Ngrid/2 "<< K[Ngrid/2]<<endl;
        cout<< "k in line Ngrid/2+1  "<< K[Ngrid/2+1]<<endl;

//SET UP K SHELL AND ADD
 /*    for (int r=1; r<Ngrid/2;r++)// loop through all radial bin (50)
         { //   cout << "shell at: " << r*2*M_PI/100<<endl;
              int shellVolume=0;//by counting
              double shellContribution = 0;

              for (int l=0; l<GridVolume;l++)// for each spherical bin, loop through all points
              {                     if( (r*2*M_PI/double(Ngrid) < K[l] ) && ( K[l]<= (r+1)*2*M_PI/double(Ngrid)  ) ) 
                   
                      { //CALCULATE POWER SPECTRUM IN HERE
                      //DEPEND ON HOW ROOT 2D PLOTS WORKS, SET UP APPROPRIATE ARRAY OF POWER SPECTRUM
                        shellVolume = shellVolume+1;
                        if (window==1)
                        shellContribution = shellContribution+ ( out[l][0]*out[l][0] + out[l][1]*out[l][1])/W_x[l]/W_y[l]/W_z[l]/W_x[l]/W_y[l]/W_z[l];
                        else
                        shellContribution = shellContribution+ out[l][0]*out[l][0] + out[l][1]*out[l][1];
                  //      printf(" sort for shelf %i at bin:  %i \n",r,l);
                        //2-- save k radius to do log log plot//50 lines. do this first.
                        //NORMALIZATION ??
                     }               
              }   //end of collecting poins for the shell
             cout<< "shell volume:"<<shellVolume<<endl;
             cout <<"k:  " << r*2*M_PI/double(Ngrid) << " " << shellContribution/shellVolume <<endl;
             outfile << r*2*M_PI/double(Ngrid) << " " << shellContribution/double(shellVolume) <<endl;
     //cout<< "k in line 567:   "<< k[567]<<endl;
    //     cout<< "test: 100/100 and 100 modulo 100: "<<100/100<<" "<<100%100<<endl; 
                       
         }   //end of looping through all k shell
        cout<< "outfile FFT written"<<endl;
*/

    fftw_destroy_plan(p);
    fftw_free(in); fftw_free(out);
    cout << endl;
   // delete [] PHI;
    delete [] k_x;
    delete [] k_y;
    delete [] k_z;
    delete [] K;
    delete [] W_x;
    delete [] W_y;
    delete [] W_z;

return 0;


		
}

int nextPoint( int n, int Ngrid )
  {
    int next; 
    if (n == Ngrid-1) { next = 0;} 
    else next = n+1;
    return next;
  }

int main(int argc, char* argv[])//what are these for?
{ 
//FFT("gaussian1.dat","gauss1fft.dat");
//FFT("gaussian2.dat","gauss2fft.dat");
//FFT("gaussian3.dat","gauss3fft.dat");
	//OUT PUT FILE
    ofstream outfile;
    outfile.open("randwalk.dat");//
    ofstream outfile2;
    outfile2.open("randomWalkDensity.dat"); 
    //DECLARATION OF RANDOM UNIFORM NUMBER AND CONSTANT
    const double alpha = 1.5;
    const int Ns=100; const int Nc=500; const int  Ngrid=400; const double Lbox=250.0;
    
    double X[Nc*Ns]; double Y[Nc*Ns]; double Z[Nc*Ns];
 
    std::random_device rd;
    std::default_random_engine generator( rd() );
    std::uniform_real_distribution<double> u1(0.0,1.0);
    std::uniform_real_distribution<double> u2(0.0,1.0);
    std::uniform_real_distribution<double> u3(0.0,1.0);
    std::cout << "some random numbers between 0.0 and 1.0: " << std::endl;
    std::uniform_real_distribution<double> ux(0.0,Lbox);
    std::uniform_real_distribution<double> uy(0.0,Lbox);
    std::uniform_real_distribution<double> uz(0.0,Lbox);
  
        for (int j=0; j<Nc; j++)
        {

        //STATING POINT WITHIN THE 250 BOX, DIFFERENT FOR EACH IN 500 WALK
        double x = ux(generator)-double(Lbox)/2.0; 
        double y = uy(generator)-double(Lbox)/2.0; 
        double z = uz(generator)-double(Lbox)/2.0;//have to generate stating point randomly
       // printf ( "start walking NUMBER %i at: %f %f %f \n",j, x, y, z);
        //START WALKING
        for (int i=0; i<Ns; ++i){
            //ALL RANDOM-DEPENDENT VARS HAVE TO BE UPDATED FOR EVERY ITERATION
            double r= 1.0/pow( (  (1.0-u1(generator))),1.0/alpha);
            double theta = acos(2.0*u2(generator)-1.0);
            double phi = 2.0*M_PI*u3(generator);
            double dx= sin(theta)*cos(phi)*r;
            double dy= sin(theta)*sin(phi)*r;
            double dz = r*cos(theta);
            x = x+dx; y = y+ dy; z= z+dy;//STEP 
            //CREAT BOUNDARY CONDITIONS
            while (abs(x)>=Lbox/2) { if (x<0) x=x+double(Lbox);   else x = x-double(Lbox);  }
            while (abs(y)>=Lbox/2) { if (y<0) y=y+double(Lbox);   else y = y-double(Lbox); }
            while (abs(z)>=Lbox/2) { if (z<0) z=z+double(Lbox);   else z = z-double(Lbox); }
    
      /*  std::cout<< "step: "<< i;//<<" " << u1(generator) <<" "<< u2(generator)<<" " <<u3(generator)<<" ";
        cout << " r:"<<r <<" theta: "<<theta<<" phi: "<< phi<<" ";
        printf ("dx %f, x %f, dy %f, y %f, dz %f z %f \n", dx, x, dy, y, dz, z);
      */  outfile <<x<<" "<<y<<" "<<z<<endl;//original random walk   
        int line = j*Ns + i;
        X[line]=x; Y[line]=y; Z[line]=z;//SAVE THE CO ORDINATE OF PARTICLE TO ARRAY 
        }//end of 100 steps loop
        cout <<" "<<j;
    }//end of the Nc =500 walks loop
    cout<< "\n done walking"; 
    //DONE WITH THE WALK.
    vector<vector<vector<double> > > densityArray;//an array to hold the density
    densityArray.resize(Ngrid);
    for (int i = 0; i < Ngrid; ++i) {
        densityArray[i].resize(Ngrid);
    for (int j = 0; j < Ngrid; ++j)
        densityArray[i][j].resize(Ngrid);
    }    
    for (int i=0; i<Ngrid; i++)
        for (int j = 0; j<Ngrid; j++)
            for (int k=0; k<Ngrid; k++) 
                densityArray[i][j][k] =0; 
    
    double binsize=double(Lbox)/double(Ngrid);
    int nx, ny, nz;    
    //GOING THROUGH ALL CREATED PARTICLES AND DISTRIBUTE THEIR DENSITY
    for (int k=0; k< Nc*Ns; k++) {
        //LOCATE THE PARTICLe, the indices are coordinates rounded down
        nx = int ( ( X[k]+ double(Lbox)/2.0) /binsize);//shift coordinate to positive value for indexing  
        ny = int( ( Y[k]+ double(Lbox)/2.0)/binsize); nz = int( (Z[k]+double(Lbox)/2.0)/binsize);
        //printf (" %i grid index: %i , %i, %i,\n",k, nx, ny, nz);
        //cout <<"test"<< int ( 0.99/1);
        //CALCULATE DENSITY CIC distributing fractional density to 8 neighboring points
        //UPDATING GRID POINTS
        densityArray[nx][ny][nz] += (binsize-abs((X[k]+double(Lbox)/2.0)-double(nx)*binsize ))*(binsize-abs((Y[k]+double(Lbox)/2.0)-ny*binsize ))*(binsize-abs((Z[k]+double(Lbox)/2.0)-nz*binsize )  )/binsize/binsize/binsize;
        
        densityArray[nextPoint(nx,Ngrid)][ny][nz]+= (binsize-abs((X[k]+double(Lbox)/2.0)-(double(nx)+1)*binsize ))*(binsize-abs((Y[k]+double(Lbox)/2.0)-ny*binsize ))*(binsize-abs((Z[k]+double(Lbox)/2.0)-nz*binsize )  ) /binsize/binsize/binsize;
 
        densityArray[nx][nextPoint(ny,Ngrid)][nz]+= (binsize-abs((X[k]+double(Lbox)/2.0)-double(nx)*binsize ))*(binsize-abs((Y[k]+double(Lbox)/2.0)-(ny+1)*binsize ))*(binsize-abs((Z[k]+double(Lbox)/2.0)-nz*binsize )  ) /binsize/binsize/binsize;
        
         densityArray[nextPoint(nx,Ngrid)][nextPoint(ny,Ngrid)][nz] += (binsize-abs((X[k]+double(Lbox)/2.0)-(double(nx)+1)*binsize ))*(binsize-abs((Y[k]+double(Lbox)/2.0)-(ny+1)*binsize ))*(binsize-abs((Z[k]+double(Lbox)/2.0)-nz*binsize )  )/binsize/binsize/binsize;
        
        densityArray[nx][ny][nextPoint(nz,Ngrid)] += (binsize-abs((X[k]+double(Lbox)/2.0)-double(nx)*binsize ))*(binsize-abs((Y[k]+double(Lbox)/2.0)-ny*binsize ))*(binsize-abs((Z[k]+double(Lbox)/2.0)-(nz+1)*binsize )  )/binsize/binsize/binsize;
        
        densityArray[nextPoint(nx,Ngrid)][ny][nextPoint(nz,Ngrid)]+= (binsize-abs((X[k]+double(Lbox)/2.0)-(double(nx)+1)*binsize ))*(binsize-abs((Y[k]+double(Lbox)/2.0)-ny*binsize ))*(binsize-abs((Z[k]+double(Lbox)/2.0)-(nz+1)*binsize )  ) /binsize/binsize/binsize;
 
        densityArray[nx][nextPoint(ny,Ngrid)][nextPoint(nz,Ngrid)]+= (binsize-abs((X[k]+double(Lbox)/2.0)-double(nx)*binsize ))*(binsize-abs((Y[k]+double(Lbox)/2.0)-(ny+1)*binsize ))*(binsize-abs((Z[k]+double(Lbox)/2.0)-(nz+1)*binsize )  )/binsize/binsize/binsize;
        
         densityArray[nextPoint(nx,Ngrid)][nextPoint(ny,Ngrid)][nextPoint(nz,Ngrid)] += (binsize-abs((X[k]+double(Lbox)/2.0)-(double(nx)+1)*binsize ))*(binsize-abs((Y[k]+double(Lbox)/2.0)-(ny+1)*binsize ))*(binsize-abs((Z[k]+double(Lbox)/2.0)-(nz+1)*binsize )  )/binsize/binsize/binsize;
        

    }//END OF DENSITY DISTRIBUTION    
    double totalDensity=0;
   //testing 
    for (int i=0; i<Ngrid; i++)
        for (int j = 0; j<Ngrid; j++)
            for (int k=0; k<Ngrid; k++) 
                if ( densityArray[i][j][k] !=0) {
                totalDensity = densityArray[i][j][k]+totalDensity;
                }
    
    cout << "\n TEST: total density is:"<< totalDensity<<endl;
    //WRITE OUT OUTPUT IN ROW MAJOR FORMAT
    for (int i=0; i<Ngrid; i++)
        for (int j = 0; j<Ngrid; j++)
            for (int k=0; k<Ngrid; k++)  {
                outfile2<<densityArray[i][j][k]<<endl;  //not sure about X Y Z , should they be shifted to positive range ? 
                 }
      cout<< "density file written"<<endl; 
 
    //CALL FFT WHICH READ OUTPUT FILE OF DENSITY GRID
  FFT("randomWalkDensity.dat","randomWalkFft.dat","Fft3DOut.dat",Ngrid,binsize, Nc*Ns, 1); 

     
    return 0;

} 
