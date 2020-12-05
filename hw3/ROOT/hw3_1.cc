#include "Riostream.h"
#include "TGraph.h"
#include "TFile.h"//need?
#include "TCanvas.h"

void hw3_1() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

TString dir = gSystem->UnixPathName(__FILE__);
   dir.ReplaceAll("hw3_1.cc","");
   dir.ReplaceAll("/./","/");
  // read file and add to fit object
   Double_t *x = new Double_t[10000000];
   Double_t *y = new Double_t[10000000];
   Double_t *z = new Double_t[10000000];
   Double_t *w = new Double_t[10000000];   
   Double_t *p = new Double_t[10000000];
//Double_t *ex = new Double_t[10000000];
   Double_t *r = new Double_t[10000000];   

   Double_t vX, vY, vZ,vW,vP,vR;
   Int_t vNData = 0;
   ifstream vInput;
   vInput.open(Form("%s1a.dat",dir.Data()));
   while (1) {
      vInput >> vX >> vY>>vZ>> vW>>vP>>vR;
      if (!vInput.good()) break;
      x[vNData] = vX;//phi
      y[vNData] = vY;
      z[vNData] = vZ;
     // r[vNData] = 1/vZ;
      w[vNData] = vW;
      p[vNData] = vP;//radius 1/u
      r[vNData] = vR;
      //ex[vNData]=TMath::Pi()/8.; //radius theta grid
      //ep[vNData] = 10000000;    //radius grid
 
      vNData++;
   }//whilei
// draw graph
   vC1 = new TCanvas() ;
   vC1->Divide(1,3);
   TMultiGraph *mg = new TMultiGraph();

   vInput.close();
   vC1->cd(1);
   graph = new TGraph(vNData,x,y); 
   
    graph->SetMarkerStyle(kPlus);
    graph->SetMarkerColor(kBlue);
    graph->SetLineColor(kBlue);
    graph->SetName("1");
    graph -> SetTitle("temp");
    graph->DrawClone("APE");
    mg-> Add(graph);
   
    graph2 = new TGraph(vNData,x,z); 

    graph2->SetMarkerStyle(kPlus);
    graph2->SetMarkerColor(kRed);
    graph2->SetLineColor(kRed);
    graph2->SetName("2") ;
    graph2->SetTitle("Newtonian exact");
    mg-> Add(graph2);
    mg->SetTitle("t and h; time (week) ; T/H ");

  
    mg->Draw("ap");

    
    vC1->cd(2);

    graph3 = new TGraph(vNData/2,w,p);
    graph3->SetTitle(" Power strectrum of temperature; frequency x #frac{ 2#Pi}{104} #frac{1}{week}; power  ");
//    gROOT->SetStyle("Plain");
    graph3->SetMarkerStyle(kOpenCross);
    graph3->SetMarkerColor(kBlue);
    graph3->SetLineColor(kBlue);
    graph3->Draw("AL*");

    vC1->cd(3);

    graph4 = new TGraph(vNData/2,w,r);
    graph4->SetTitle(" Power spectrum of humidity; frequency x  #frac{ 2#Pi}{104} #frac{1}{week}; power  ");
//    gROOT->SetStyle("Plain");
    graph4->SetMarkerStyle(kOpenCross);
    graph4->SetMarkerColor(kRed);
    graph4->SetLineColor(kRed);
    graph4->Draw("AL*");

 //create legend:w

 //  leg = new TLegend(0.1,0.7,0.48,0.9);
 //  leg->SetHeader("Legend");
 //  leg->AddEntry("1","Runga-Kutta","l");
 //  leg->AddEntry("2","Exact Newtonian solution","l");
  
   
  //  vC1->BuildLegend();

//polar grahp
  
 
/*

TGraphPolar * grPE = new TGraphPolar(1000,x,p);//,ex,ep);
   grPE->SetMarkerStyle(29);
   grPE->SetMarkerSize(1.5);
   grPE->SetMarkerColor(4);
   grPE->SetLineColor(4);
   grPE->SetLineWidth(2);
   grPE->Draw("ap");
   vC1->Update();
   grPE->GetPolargram()->SetTextSize(0.06);
   grPE->GetPolargram()->SetTwoPi();
   grPE->GetPolargram()->SetToRadian();
   grPE->SetTitle(" Mercury orbit w/o relativistic by Runga-Kutta 4th order ");
   
TGraphPolar * grPE2 = new TGraphPolar(1000,x,r);//,ex,ep);
   grPE2->SetMarkerStyle(4);
   grPE2->SetMarkerSize(1.5);
   grPE2->SetMarkerColor(2);
   grPE2->SetLineColor(2);
   grPE2->SetLineWidth(2);
   grPE2->Draw("ap");
   vC1->Update();
   grPE2->GetPolargram()->SetTextSize(0.06);
   grPE2->GetPolargram()->SetTwoPi();
   grPE2->GetPolargram()->SetToRadian();
 
   grPE2->SetTitle(" Mercury orbit described by Newtonian solution ");
    vC1->BuildLegend();
*/
//mg->Add(grPE);
   //mg->Draw("ap");

// cleanup
   delete [] x;
   delete [] y;
   delete [] z;
   delete [] w;
    delete [] p;
  // delete graph;
   //delete graph2;

//   f->Write();
}
