#include "Riostream.h"
#include "TGraph.h"
#include "TFile.h"//need?
#include "TCanvas.h"

void hw3_1c() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

TString dir = gSystem->UnixPathName(__FILE__);
   dir.ReplaceAll("hw3_1c.cc","");
   dir.ReplaceAll("/./","/");
  // read file and add to fit object
   Double_t *x = new Double_t[1000];
   Double_t *y = new Double_t[1000];
   Double_t *z = new Double_t[1000];
   Double_t *w = new Double_t[1000];   
   Double_t *p = new Double_t[1000];

   Double_t vX, vY, vZ,vW,vP;
   Int_t vNData = 0;
   ifstream vInput;
   vInput.open(Form("%sifft.dat",dir.Data()));
   while (1) {
      vInput >> vX >> vY>>vZ>> vW>>vP;
      if (!vInput.good()) break;
      x[vNData] = vX;//phi
      y[vNData] = vY;
      z[vNData] = vZ;
     // r[vNData] = 1/vZ;
      w[vNData] = vW;
      p[vNData] = vP;//radius 1/u
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
   vInput2.open(Form("%sTandH.dat",dir.Data()));
   while (1) {
      vInput2 >> vT >> vH;
      if (!vInput2.good()) break;
      t[vNData2] = vT-23.3635;//phi
      h[vNData2] = vH-41.0962;

      vNData2++;
   }//whilei
   vInput2.close();
 

// draw graph
   vC1 = new TCanvas() ;
   vC1->Divide(1,2);
   TMultiGraph *mg = new TMultiGraph();

   vC1->cd(1);
   graph = new TGraph(vNData,x,t); 
   
    graph->SetMarkerStyle(kPlus);
    graph->SetMarkerColor(kBlue);
    graph->SetLineColor(kBlue);
    graph->SetName("1");
    graph -> SetTitle("temp");
    graph->DrawClone("APE");
    mg-> Add(graph);
   
    graph2 = new TGraph(vNData,x,w); 

    graph2->SetMarkerStyle(kPlus);
    graph2->SetMarkerColor(kRed);
    graph2->SetLineColor(kRed);
    graph2->SetName("2") ;
    graph2->SetTitle("Newtonian exact");
    mg-> Add(graph2);
    mg->SetTitle( " fluctuation in temperature before (BLUE) and after (RED) removing seasonal variation   ; time (week) ; T ");
 

    mg->Draw("al");

   
   TMultiGraph *mg2 = new TMultiGraph();
    vC1->cd(2);
   
   graph3 = new TGraph(vNData,x,h); 
   
    graph3->SetMarkerStyle(kPlus);
    graph3->SetMarkerColor(kBlue);
    graph3->SetLineColor(kBlue);
    graph3->SetName("1");
    graph3 -> SetTitle("temp");
    graph3->DrawClone("APE");
    mg2-> Add(graph3);
   
    graph4 = new TGraph(vNData,x,p); 

    graph4->SetMarkerStyle(kPlus);
    graph4->SetMarkerColor(kRed);
    graph4->SetLineColor(kRed);
    graph4->SetName("2") ;
    graph4->SetTitle("Newtonian exact");
    mg2-> Add(graph4);
    mg2->SetTitle( "  fluctuation in humidity before (BLUE) and after (RED) removing seasonal variation; time (week) ; H ");

  
    mg2->Draw("al");


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
    delete [] p;
  // delete graph;
   //delete graph2;

//   f->Write();


}
