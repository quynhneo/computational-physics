#include "Riostream.h"
#include "TGraph.h"
#include "TFile.h"//need?
#include "TCanvas.h"

void hw3_2() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

TString dir = gSystem->UnixPathName(__FILE__);
   dir.ReplaceAll("hw3_2.cc","");
   dir.ReplaceAll("/./","/");
  // read file and add to fit object
   Double_t *x = new Double_t[1000];
   Double_t *y = new Double_t[1000];
   Double_t *z = new Double_t[1000];
   Double_t *w = new Double_t[1000];   

   Double_t vX, vY, vZ,vW,vP;
   Int_t vNData = 0;
   ifstream vInput;
   vInput.open(Form("%sgauss1fft.dat",dir.Data()));
   while (1) {
      vInput >> vX >> vY;//>>vZ>> vW>>vP;
      if (!vInput.good()) break;
      x[vNData] = vX;//phi
      y[vNData] = vY;
 //     z[vNData] = vZ;
     // r[vNData] = 1/vZ;
   //   w[vNData] = vW;
      //ex[vNData]=TMath::Pi()/8.; //radius theta grid
      //ep[vNData] = 10000000;    //radius grid
 
      vNData++;
   }//whilei

   vInput.close();
   
   Double_t *t = new Double_t[1000];   

   Double_t *h = new Double_t[1000];   
   Double_t vH,vT;
   Int_t vNData2 = 0;
   ifstream vInput2;
   vInput2.open(Form("%sgauss2fft.dat",dir.Data()));
   while (1) {
      vInput2 >> vT >> vH;
      if (!vInput2.good()) break;
      t[vNData2] = vT;//phi
      h[vNData2] = vH;

      vNData2++;
   }//whilei
   vInput2.close();
  
   Int_t vNData3 = 0;
   ifstream vInput3;
   vInput3.open(Form("%sgauss3fft.dat",dir.Data()));
   while (1) {
      vInput3 >> vZ >> vW;
      if (!vInput3.good()) break;
      z[vNData3] = vZ;//phi
      w[vNData3] = vW;

      vNData3++;
   }//whilei
   vInput3.close();
 


// draw graph
   vC1 = new TCanvas() ;
   vC1->SetLogy();
   vC1->SetLogx();
  // vC1->Divide(1,3);
   TMultiGraph *mg = new TMultiGraph();
  // vC1->cd(1);
   graph = new TGraph(vNData,x,y); 
   
   graph->SetMarkerStyle(kPlus);
    graph->SetMarkerColor(kBlue);
    graph->SetLineColor(kBlue);
    graph->SetName("1");
//    graph -> SetTitle("temp");
    graph->DrawClone("APE");
       mg-> Add(graph);
    mg->SetTitle( "power spectrum of Gaussian field 1 ; k ; power ");
    mg->Draw("al");

    vC2 = new TCanvas() ;
   vC2->SetLogy();
   vC2->SetLogx();
 //vC2->Clear();
   //vC1->cd(2); 
   TMultiGraph *mg2 = new TMultiGraph();
   
   graph3 = new TGraph(vNData2,t,h); 
   
    graph3->SetMarkerStyle(kPlus);
    graph3->SetMarkerColor(kBlue);
    graph3->SetLineColor(kBlue);
    graph3->SetName("1");
 //   graph3 -> SetTitle("temp");
  //  graph3->DrawClone("APE");
    mg2-> Add(graph3);
    mg2->SetTitle( "power spectrum of Gaussian field 2 ; k ; power ");
    mg2->Draw("al");


   vC3 = new TCanvas() ;
   vC3->SetLogy();
   vC3->SetLogx();
  //vC3->Clear();
//vC1->cd(3);

   TMultiGraph *mg3 = new TMultiGraph();
   
   graph4 = new TGraph(vNData3,z,w); 
   
    graph4->SetMarkerStyle(kPlus);
    graph4->SetMarkerColor(kBlue);
    graph4->SetLineColor(kBlue);
    graph4->SetName("1");
    graph4 -> SetTitle("temp");
    graph4->DrawClone("APE");
    mg3-> Add(graph4);

    mg3->SetTitle( "power spectrum of Gaussian field 3 ; k ; power ");
    mg3->Draw("al");
 //create legend
 //  leg = new TLegend(0.1,0.7,0.48,0.9);
 //  leg->SetHeader("Legend");
 //  leg->AddEntry("1","Runga-Kutta","l");
 //  leg->AddEntry("2","Exact Newtonian solution","l");
  
   
  //  vC1->BuildLegend();

// cleanup
   delete [] x;
   delete [] y;
   delete [] z;
   delete [] w;
  delete [] t;
    delete [] h;
// delete graph;
   //delete graph2;
//   f->Write();


}
