#include "Riostream.h"
#include "TGraph.h"
#include "TFile.h"//need?
#include "TCanvas.h"

void hw3_2c() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

TString dir = gSystem->UnixPathName(__FILE__);
   dir.ReplaceAll("hw3_2c.cc","");
   dir.ReplaceAll("/./","/");
  // read file and add to fit object
   Double_t *x = new Double_t[1000];
   Double_t *y = new Double_t[1000];
   
   Double_t vX, vY;// vZ,vW;
   Int_t vNData = 0;
   ifstream vInput;
   vInput.open(Form("%sgauss1fft_coarse.dat",dir.Data()));
   while (1) {
      vInput >> vX >> vY;//>>vZ>> vW>>vP;
      if (!vInput.good()) break;
      x[vNData] = vX;//phi
      y[vNData] = vY;
      vNData++;
   }//whilei

   vInput.close();
  
   Double_t *x5 = new Double_t[1000];
   Double_t *y5 = new Double_t[1000];
   Double_t vX5, vY5;
   Int_t vNData5 = 0;
   ifstream vInput5;
   vInput5.open(Form("%sgauss1fft.dat",dir.Data()));
   while (1) {
      vInput5 >> vX5 >> vY5;//>>vZ>> vW>>vP;
      if (!vInput5.good()) break;
      x5[vNData5] = vX5;//phi
      y5[vNData5] = vY5;
      vNData5++;
   }//whilei

   vInput5.close();

   Double_t *t = new Double_t[1000];   
   Double_t *h = new Double_t[1000];   
   Double_t vH,vT;
   Int_t vNData2 = 0;
   ifstream vInput2;
   vInput2.open(Form("%sgauss2fft_coarse.dat",dir.Data()));
   while (1) {
      vInput2 >> vT >> vH;
      if (!vInput2.good()) break;
      t[vNData2] = vT;//phi
      h[vNData2] = vH;
      vNData2++;
   }//whilei
   vInput2.close();


   Double_t *t5 = new Double_t[1000];   
   Double_t *h5 = new Double_t[1000];   
   Double_t vH5,vT5;
   Int_t vNData25 = 0;
   ifstream vInput25;
   vInput25.open(Form("%sgauss2fft.dat",dir.Data()));
   while (1) {
      vInput25 >> vT5 >> vH5;
      if (!vInput25.good()) break;
      t5[vNData25] = vT5;//phi
      h5[vNData25] = vH5;
      vNData25++;
   }//whilei
   vInput25.close();
 
   Double_t *z = new Double_t[1000];
   Double_t *w = new Double_t[1000];   
   Double_t vZ, vW; 
   Int_t vNData3 = 0;
   ifstream vInput3;
   vInput3.open(Form("%sgauss3fft_coarse.dat",dir.Data()));
   while (1) {
      vInput3 >> vZ >> vW;
      if (!vInput3.good()) break;
      z[vNData3] = vZ;//phi
      w[vNData3] = vW;
      vNData3++;
   }//whilei
   vInput3.close();
 

   Double_t *z5 = new Double_t[1000];
   Double_t *w5 = new Double_t[1000];   
   Double_t vZ5,vW5;
   Int_t vNData35 = 0;
   ifstream vInput35;
   vInput35.open(Form("%sgauss3fft.dat",dir.Data()));
   while (1) {
      vInput35 >> vZ5 >> vW5;
      if (!vInput35.good()) break;
      z5[vNData35] = vZ5;//phi
      w5[vNData35] = vW5;
      vNData35++;
   }//whilei
   vInput35.close();

// draw graph
   vC1 = new TCanvas() ;
   vC1->SetLogy();
   vC1->SetLogx();
   TMultiGraph *mg = new TMultiGraph();
   
    graph = new TGraph(vNData,x,y); 
    graph->SetLineColor(kRed);
    mg-> Add(graph);
   
    graph5 = new TGraph(vNData5,x5,y5); 
    graph5->SetLineColor(kBlue);
    mg-> Add(graph5);
    
    mg->SetTitle( "power spectrum of original (blue) 2x coarser (red) Gaussian field 1 ; k ; power ");
    mg->Draw("al");

    vC2 = new TCanvas() ;
    vC2->SetLogy();
    vC2->SetLogx();
    TMultiGraph *mg2 = new TMultiGraph();
   
    graph3 = new TGraph(vNData2,t,h); 
    graph3->SetLineColor(kRed);
    mg2-> Add(graph3);

    graph35 = new TGraph(vNData25,t5,h5); 
    graph35->SetLineColor(kBlue);
    mg2-> Add(graph35);
    
    mg2->SetTitle( "power spectrum of original (blue) and 2x coarser (red) Gaussian field 2 ; k ; power ");
    mg2->Draw("al");


   vC3 = new TCanvas() ;
   vC3->SetLogy();
   vC3->SetLogx();
   TMultiGraph *mg3 = new TMultiGraph();
   
   graph4 = new TGraph(vNData3,z,w); 
    graph4->SetLineColor(kRed);
    mg3-> Add(graph4);
    
   graph45 = new TGraph(vNData35,z5,w5); 
   graph45->SetLineColor(kBlue);
    mg3-> Add(graph45);

    mg3->SetTitle( "power spectrum of original (blue) and 2x coarser (red) Gaussian field 3 ; k ; power ");
    mg3->Draw("al");
  
  
   delete [] x; delete [] x5;
   delete [] y; delete [] y5;
  
 delete [] z; delete [] z5;
   delete [] w; delete [] w5;

  delete [] t; delete [] t5;
    delete [] h; delete [] h5;


}
