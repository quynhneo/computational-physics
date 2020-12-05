#include "Riostream.h"
#include "TGraph.h"
#include "TFile.h"
#include "TCanvas.h"

//PLOTTING IN ROOT
void plot() {

      
// read file $ROOTSYS/macros/cos_center_0.1.dat
// this file has 2 columns of data
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("cos_center_diff.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("%scos_center_0.1.dat",dir.Data()));//open input text file

   Float_t x,y;
   Float_t x_array[50];
   Float_t y_array[50];
   Int_t nlines = 0;


   while (1) {
      in >> x >> y ;//read in line by line
      if (!in.good()) break;

      x_array[nlines]=x;
      y_array[nlines]=y;
      
      printf("x[%f8]=%8f\n",nlines,x_array[nlines]);  
      printf("y[%f8]=%8f\n",nlines,y_array[nlines]);  
      
      nlines++;//move to next line
   }
   printf(" found %d points\n",nlines);
   TGraph graph(nlines,x_array,y_array);
   graph.SetTitle(" SP Center difference estimation of #frac{dCos(x)}{dx} at x=0.1; step size h ; relative error       ");

    gROOT->SetStyle("Plain");
    graph.SetMarkerStyle(kOpenCircle);
    graph.SetMarkerColor(kBlue);
    graph.SetLineColor(kBlue);

   //how to delete old canvas?
   TCanvas* mycanvas = new TCanvas();
   
   mycanvas->SetLogx();//set log-log scale
   mycanvas->SetLogy();
    
   graph.DrawClone("APE");
    
   in.close();
   
   //mycanvas->Print("cos_center_0.1.png"); // doesn't work

//   f->Write();
}
