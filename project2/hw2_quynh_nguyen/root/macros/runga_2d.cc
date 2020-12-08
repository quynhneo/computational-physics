#include "Riostream.h"
#include "TGraph.h"
#include "TFile.h"//need?
#include "TCanvas.h"

void runga() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

TString dir = gSystem->UnixPathName(__FILE__);
   dir.ReplaceAll("runga.cc","");
   dir.ReplaceAll("/./","/");
  // read file and add to fit object
   Double_t *x = new Double_t[133];
   Double_t *y = new Double_t[133];
   Double_t vX, vY;
   Int_t vNData = 0;
   ifstream vInput;
   vInput.open(Form("%soutput.dat",dir.Data()));
   while (1) {
      vInput >> vX >> vY;
      if (!vInput.good()) break;
      x[vNData] = vX;
      y[vNData] = vY;
      vNData++;
   }//while
   vInput.close();
   graph = new TGraph(vNData,x,y); 



   graph->SetTitle(" 10; step ; u         ");
    gROOT->SetStyle("Plain");
    graph->SetMarkerStyle(kFullCircle);
    graph->SetMarkerColor(kBlue);
    graph->SetLineColor(kBlue);

   //how to delete old canvas?
   TCanvas* mycanvas = new TCanvas();
   
  // mycanvas->SetLogx();
  // mycanvas->SetLogy();
    
   graph->DrawClone("APE");
    
   
// cleanup
   delete [] x;
   delete [] y;
   delete graph;


//   f->Write();
}
