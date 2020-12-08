#include "Riostream.h"
#include "TGraph.h"
#include "TFile.h"//need?
#include "TCanvas.h"

void hw3_2D() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

TString dir = gSystem->UnixPathName(__FILE__);
   dir.ReplaceAll("hw3_2D.cc","");
   dir.ReplaceAll("/./","/");
  // read file and add to fit object
   Double_t *x = new Double_t[10000];
   Double_t *y = new Double_t[10000];
   Double_t *z = new Double_t[10000];
  // Double_t *w = new Double_t[10000];   

   Double_t vX, vY, vZ,vW,vP;
   Int_t vNData = 0;
   ifstream vInput;
   vInput.open(Form("%sgauss1Kplane.dat",dir.Data()));
   while (1) {
      vInput >> vX >> vY>>vZ;//>> vW>>vP;
      if (!vInput.good()) break;
      x[vNData] = vX;//phi
      y[vNData] = vY;
      z[vNData] = vZ;
         vNData++;
   }//whilei

   vInput.close() ; 
   vC1 = new TCanvas() ;
  vC1->SetLogz();
  // vC1->SetLogx();
  // vC1->Divide(1,3);
//   TMultiGraph *mg = new TMultiGraph();
  // vC1->cd(1);
   TGraph2D *graph = new TGraph2D(); 
    for ( Int_t j=0;j<10000;j++)
        graph -> SetPoint(j,x[j],y[j],z[j]);
    gStyle->SetPalette(1);
    graph->Draw("surf1"); 
    //graph->Draw("CONT");
    graph->SetTitle( "2D power spectrum of Gaussian field 1 ; x ; y ");
 
  //  vC1->BuildLegend();

// cleanup
   delete [] x;
   delete [] y;
   delete [] z;
//------

   Double_t *x2 = new Double_t[10000];
   Double_t *y2 = new Double_t[10000];
   Double_t *z2 = new Double_t[10000];
  // Double_t *w = new Double_t[10000];   

   Double_t vX2, vY2, vZ2;
   Int_t vNData2 = 0;
   ifstream vInput2;
   vInput2.open(Form("%sgauss2Kplane.dat",dir.Data()));
   while (1) {
      vInput2 >> vX2 >> vY2>>vZ2;//>> vW>>vP;
      if (!vInput2.good()) break;
      x2[vNData2] = vX2;//phi
      y2[vNData2] = vY2;
      z2[vNData2] = vZ2;
         vNData2++;
   }//whilei

   vInput2.close() ; 
   vC2 = new TCanvas() ;
 vC1->SetLogz();
  // vC1->SetLogx();
  // vC1->Divide(1,3);
//   TMultiGraph *mg = new TMultiGraph();
  // vC1->cd(1);
   TGraph2D *graph2 = new TGraph2D(); 
    for ( Int_t j=0;j<10000;j++)
        graph2 -> SetPoint(j,x2[j],y2[j],z2[j]);
    gStyle->SetPalette(1);
    graph2->Draw("surf1"); 
 //   graph->Draw("CONT");
    graph2->SetTitle( "2D power spectrum of Gaussian field 2 ; x ; y ");
 
  //  vC1->BuildLegend();

// cleanup
   delete [] x2;
   delete [] y2;
   delete [] z2;
///////-----

   Double_t *x3 = new Double_t[10000];
   Double_t *y3 = new Double_t[10000];
   Double_t *z3 = new Double_t[10000];
  // Double_t *w = new Double_t[10000];   

   Double_t vX3, vY3, vZ3;//,vW,vP;
   Int_t vNData3 = 0;
   ifstream vInput3;
   vInput3.open(Form("%sgauss3Kplane.dat",dir.Data()));
   while (1) {
      vInput3 >> vX3 >> vY3>>vZ3;//>> vW>>vP;
      if (!vInput3.good()) break;
      x3[vNData3] = vX3;//phi
      y3[vNData3] = vY3;
      z3[vNData3] = vZ3;
         vNData3++;
   }//whilei

   vInput3.close() ; 
   vC3 = new TCanvas() ;
   vC3->SetLogz();
  // vC1->SetLogx();
  // vC1->Divide(1,3);
//   TMultiGraph *mg = new TMultiGraph();
  // vC1->cd(1);
   TGraph2D *graph3 = new TGraph2D(); 
    for ( Int_t j=0;j<10000;j++)
        graph3 -> SetPoint(j,x3[j],y3[j],z3[j]);
    gStyle->SetPalette(1);
    graph3->Draw("surf1"); 
    //graph->Draw("CONT");
    graph3->SetTitle( "2D power spectrum of Gaussian field 3 ; x ; y ");
 
  //  vC1->BuildLegend();

// cleanup
   delete [] x3;
   delete [] y3;
   delete [] z3;
//   f->Write();


}
