#include "Riostream.h"
#include "TGraph.h"
#include "TFile.h"//need?
#include "TCanvas.h"

void prob2root() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

TString dir = gSystem->UnixPathName(__FILE__);
   dir.ReplaceAll("prob2root.cc","");
   dir.ReplaceAll("/./","/");
  // read file and add to fit object
   Double_t *x = new Double_t[10000];
   Double_t *y = new Double_t[10000];
   Double_t *z = new Double_t[10000];
  // Double_t *w = new Double_t[10000];   

   Double_t vX, vY, vZ;
   Int_t vNData = 0;
   ifstream vInput;
   vInput.open(Form("%sprob2.GS.dat",dir.Data()));
   while (1) {
      vInput >> vX >> vY>>vZ;//>> vW>>vP;
      if (!vInput.good()) break;
      x[vNData] = vX;//phi
      y[vNData] = vY;
      z[vNData] = vZ;
         vNData++;
   }//whilei

   vInput.close() ; 
   vC1 = new TCanvas("vC1","GS",0,0,800,600) ;
   TGraph2D *graph = new TGraph2D(); 
    for ( Int_t j=0;j<10000;j++)
        graph -> SetPoint(j,x[j]*1.5/100.0,y[j]*2.0/100.0,z[j]);
    gStyle->SetPalette(1);
    //graph->Draw("surf1"); 
    graph->Draw("CONTZ");
    graph->SetTitle( "Plot of #Phi(x,y) Gauss-Seidel ; x ; y ");
   delete [] x;
   delete [] y;
   delete [] z;
//------
  vC1->SaveAs("2GS.png");

   Double_t *x1 = new Double_t[10000];
   Double_t *y1 = new Double_t[10000];
  // Double_t *w = new Double_t[10000];   

   Double_t vX1, vY1;
   Int_t vNData1 = 0;
   ifstream vInput1;
   vInput1.open(Form("%sprob2.GS.error.dat",dir.Data()));
   while (1) {
      vInput1 >> vX1 >> vY1;//>> vW>>vP;
      if (!vInput1.good()) break;
      x1[vNData1] = vX1;//phi
      y1[vNData1] = vY1;
         vNData1++;
   }//whilei

   vInput1.close() ; 
   vc2 = new TCanvas() ;
   TMultiGraph *mg = new TMultiGraph();
   graph1 = new TGraph(vNData1,x1,y1);
    graph1->SetTitle("Gauss-Seidel");
    graph1->SetMarkerStyle(kFullDotMedium);
    graph1->SetMarkerColor(kBlue);
    mg->Add(graph1);
  //  vC1->BuildLegend();

// cleanup
   delete [] x1;
   delete [] y1;
//------
   Double_t *x3 = new Double_t[10000];
   Double_t *y3 = new Double_t[10000];
  // Double_t *w = new Double_t[10000];   

   Double_t vX3, vY3;
   Int_t vNData3 = 0;
   ifstream vInput3;
   vInput3.open(Form("%sprob2.SOR.error.dat",dir.Data()));
   while (1) {
      vInput3 >> vX3 >> vY3;//>> vW>>vP;
      if (!vInput3.good()) break;
      x3[vNData3] = vX3;//phi
      y3[vNData3] = vY3;
         vNData3++;
   }//whilei

   vInput3.close() ; 

   graph3 = new TGraph(vNData3,x3,y3);

    graph3->SetMarkerStyle(kFullDotMedium);
    graph3->SetMarkerColor(kRed);
    graph3 -> SetTitle("SOR");
    
    mg->Add(graph3);
    mg->SetTitle("Error vs time step; time step ; error ");
    mg->Draw("ap");
    vc2->BuildLegend();

// cleanup
   delete [] x3;
   delete [] y3;
//------
  vc2->SaveAs("2error.png");


//----
  Double_t *x2 = new Double_t[10000];
   Double_t *y2 = new Double_t[10000];
   Double_t *z2 = new Double_t[10000];
  // Double_t *w = new Double_t[10000];   

   Double_t vX2, vY2, vZ2;
   Int_t vNData2 = 0;
   ifstream vInput2;
   vInput2.open(Form("%sprob2.SOR.dat",dir.Data()));
   while (1) {
      vInput2 >> vX2 >> vY2>>vZ2;//>> vW>>vP;
      if (!vInput2.good()) break;
      x2[vNData2] = vX2;//phi
      y2[vNData2] = vY2;
      z2[vNData2] = vZ2;
         vNData2++;
   }//whilei

   vInput2.close() ; 
   vC3 = new TCanvas("vC3","SOR",0,0,800,600) ;
   TGraph2D *graph2 = new TGraph2D(); 
    for ( Int_t j=0;j<10000;j++)
        graph2 -> SetPoint(j,x2[j]*1.5/100.0,y2[j]*2.0/100.0,z2[j]);
    gStyle->SetPalette(1);
    //graph2->Draw("surf1"); 
    graph2->Draw("CONTZ");
    graph2->SetTitle( "Plot of #Phi(x,y) SOR ; x ; y ");
 
  //  vC1->BuildLegend();

// cleanup
   delete [] x2;
   delete [] y2;
   delete [] z2;
//------

  vC3->SaveAs("2SOR.png");

}
