#include "Riostream.h"
#include "TGraph.h"
#include "TFile.h"//need?
#include "TCanvas.h"

void plot() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("integral_trapezoid_root.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("%strapez.dat",dir.Data()));

   Float_t x,y;
   Float_t x_array[100];
   Float_t y_array[100];
   Int_t nlines = 0;

   while (1) {
      in >> x >> y ;
      if (!in.good()) break;

      x_array[nlines]=x;
      y_array[nlines]=y;
      
      printf("x[%f8]=%8f\n",nlines,x_array[nlines]);  
      printf("y[%f8]=%8f\n",nlines,y_array[nlines]);  
      
      nlines++;
   }
   printf(" found %d points\n",nlines);
   TGraph graph(nlines,x_array,y_array);
   graph.SetTitle(" SP trapezoidal estimation of #int_{0}^{1}e^{-x} dx at x=0.1; number of interval N ; relative error         ");

    gROOT->SetStyle("Plain");
    graph.SetMarkerStyle(kOpenCircle);
    graph.SetMarkerColor(kBlue);
    graph.SetLineColor(kBlue);

   //how to delete old canvas?
   TCanvas* mycanvas = new TCanvas();
   
   mycanvas->SetLogx();
   mycanvas->SetLogy();
    
   graph.DrawClone("APE");
    
   in.close();
   


//   f->Write();
}
