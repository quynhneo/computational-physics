#include "Riostream.h"
#include "TGraph.h"
#include "TFile.h"//need?
#include "TCanvas.h"

void plot() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("sigma2.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("%ssigma2.dat",dir.Data()));

   Float_t x,y,z,t;
   Float_t x_array[500];
   Float_t y_array[500];
   Float_t z_array[500];
   Float_t t_array[500];
   Int_t nlines = 0;

   while (1) {
      in >> x >> y >>z >>t;
      if (!in.good()) break;

      x_array[nlines]=x;
      y_array[nlines]=y;
       z_array[nlines]=z;
       t_array[nlines]=t;
       
      printf("x[%f8]=%8f",nlines,x_array[nlines]);  
      printf("y[%f8]=%8f",nlines,y_array[nlines]);  
      printf("z[%f8]=%8f\n",nlines,z_array[nlines]); 
      
      nlines++;
   }
   printf(" found %d points\n",nlines);
   

 c0 = new TCanvas("c1","multigraph L3",200,10,700,500);
 TMultiGraph *mg = new TMultiGraph();
 mg.SetTitle(" behavior of #sigma^{2},s_{3},s_{4} over number of steps ; step n ;    ");

TGraph *gr1 = new TGraph(nlines,x_array,y_array); gr1->SetLineColor(kRed);
TGraph *gr2 = new TGraph(nlines,x_array,z_array); gr2->SetLineColor(kGreen);
TGraph *gr3 = new TGraph(nlines,x_array,t_array); gr3->SetLineColor(kBlue);

mg->Add(gr2); gr2->SetTitle("#s_{3}") ; gr2->SetLineWidth(3);
mg->Add(gr1); gr1->SetTitle("#sigma^{2}") ; gr1->SetLineWidth(3);
mg->Add(gr3); gr3->SetTitle("#s_{4}") ; gr3->SetLineWidth(3);

mg->Draw("ACP");

 leg = new TLegend(0.1,0.7,0.3,0.6);
 leg->SetHeader("Legend");
 leg->AddEntry(gr1,"#sigma^{2}","l");
 leg->AddEntry(gr2,"s_{3}","l");
 leg->AddEntry(gr3,"s_{4}","l");
 leg->Draw();

return c0;
    
   in.close();
   
   

//   f->Write();
}

