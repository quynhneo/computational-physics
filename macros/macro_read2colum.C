#include "TCanvas.h"
#include "TROOT.h"
#include "TGraph.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"
#include "Riostream.h"
//jkjk
void graph() {
/*
ifstream in;
//in.open("cos_forward.txt");
in.open("test.txt");
Int_t nlines=0;


const int n_points=100;
Double_t x_vals[n_points];
Double_t y_vals[n_points];
//TVectorD& x_vals[n_points]=0;
//TVectorD& y_vals[n_points]=0;

//for (int i=1; i < n_points+1; i=i+1)
while (1)
    {   
        //in >> x_vals[i] >> y_vals[i];/// CORRECT ?
        //std::cout<< x_vals[i]<<"   ";//test print
        //std::cout<< y_vals[i]<<endl;//test print

        Double_t x,y;
        in >> x >> y ;
        if (!in.good()) break;        
        x_vals[nlines]=x;
        y_vals[nlines]=y;//CAN'T READ THE 
        
        
        nlines++;
    }
    
in.close();    
*/

ifstream file("test.txt");

 
    if(file.is_open()) //can't open the file
   
    {
        double x_vals[5]; 
        double y_vals[5]; 

        for(int i = 0; i < 5; ++i)
        {
            file >> x_vals[i]>>y_vals[i];
            std::cout <<"test" <<x_vals[i]<<" "<<x_vals[i]<<endl;
        }
    }



//std::cout<<"number of lines found:" <<nlines <<endl;//test print
/*
TGraph graph(n_points,x_vals,y_vals);
graph.SetTitle("#psi measurement XYZ;length [cm^{-1}];Arb.Units");

gROOT->SetStyle("Plain");
graph.SetMarkerStyle(kOpenCircle);
graph.SetMarkerColor(kBlue);
graph.SetLineColor(kBlue);

TCanvas* mycanvas = new TCanvas();

graph.DrawClone("APE");

//TF1 f("Linear law","[0]+x*[1]",.5,10.5);
//f.SetLineColor(kRed); f.SetLineStyle(2);

//graph.Fit(&f);
//f.DrawClone("Same");

//TLegend leg(.1,.7,.3,.9,"Lab. Lesson 1");
//leg.SetFillColor(0);
//graph.SetFillColor(0);
//leg.AddEntry(&graph,"Exp. Points");
//leg.AddEntry(&f,"Th. Law");
//leg.DrawClone("Same");


TLatex text(8.2,7.5,"#splitline{Maximum^{1}}{#delta}");
text.DrawClone();

mycanvas->Print("comp_physics.pdf");


*/
}

#ifndef __CINT__
int main(){
graph();
}
#endif
