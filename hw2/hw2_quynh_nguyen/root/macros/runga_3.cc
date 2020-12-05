#include "Riostream.h"
#include "TGraph.h"
#include "TFile.h"//need?
#include "TCanvas.h"

void runga_3() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

TString dir = gSystem->UnixPathName(__FILE__);
   dir.ReplaceAll("runga_3.cc","");
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
   vInput.open(Form("%soutput3.dat",dir.Data()));
   while (1) {
      vInput >> vX >> vY>>vZ;//>> vW>>vP;
      if (!vInput.good()) break;
      x[vNData] = vX;//phi
      y[vNData] = vY;
      z[vNData] = vZ;
      //ex[vNData]=TMath::Pi()/8.; //radius theta grid
      //ep[vNData] = 10000000;    //radius grid
 
      vNData++;
   }

   vInput.close();
    
   Int_t vNData2 = 0;
   ifstream vInput2;
   vInput2.open(Form("%soutput3_newton.dat",dir.Data()));
   while (1) {
      vInput2 >> vP >> vR >> vW;//>> vW>>vP;
      if (!vInput2.good()) break;
        
      p[vNData2] =vP ;
      r[vNData2] = vR;
      w[vNData2] = vW;//radius 1/u
      vNData2++;
     }
    vInput2.close();

//whilei
// draw graph
   vC1 = new TCanvas() ;
   vC1->Divide(1,2);
   TMultiGraph *mg = new TMultiGraph();

   vC1->cd(1);

    graph = new TGraph(vNData,x,y); 
    graph->SetMarkerStyle(kPlus);
    graph->SetMarkerColor(kBlue);
    graph->SetLineColor(kBlue);
    graph->SetName("1");
    graph->DrawClone("APE");
    
    mg-> Add(graph);
    
   graph3 = new TGraph(vNData,p,r); 
    graph3->SetMarkerStyle(kPlus);
    graph3->SetMarkerColor(kRed);
    graph3->SetLineColor(kRed);
    graph3->SetName("3");
    graph3->DrawClone("APE");
    mg-> Add(graph3);

     
    
    mg->Draw("ap");
    mg-> SetTitle("Relativistic and Newtonian mass #hat{m} ");
   // mg->GetXaxis()->SetTitle("Radius (km)");
   // mg->GetYaxis()->SetTitle("Mass (solar mass)");   

   leg = new TLegend(0.1,0.7,0.25,0.9);
   leg->SetHeader("Legend");
   leg->AddEntry("1","Relativistic","l");
   leg->AddEntry("3","Newtonian","l");
   leg->Draw();
    


    vC1->cd(2);
    TMultiGraph *mg2 = new TMultiGraph();


    graph2 = new TGraph(vNData,x,z); 

    graph2->SetMarkerStyle(kPlus);
    graph2->SetMarkerColor(kBlue);
    graph2->SetLineColor(kBlue);
    graph2->SetName("2") ;
    graph2->DrawClone("APE");
    mg2->Add(graph2);

    graph4 = new TGraph(vNData,p,w); 

    graph4->SetMarkerStyle(kPlus);
    graph4->SetMarkerColor(kRed);
    graph4->SetLineColor(kRed);
    graph4->SetName("4") ;
    graph4->DrawClone("APE");
    mg2->Add(graph4);
  

    mg2 ->Draw("ap");
    mg2->SetTitle("Relativistic and Newtonian pressure #hat{p} ");


   leg2 = new TLegend(0.1,0.7,0.25,0.9);
   leg2->SetHeader("Legend");
   leg2->AddEntry("1","Relativistic","l");
   leg2->AddEntry("4","Newtonian","l");
   leg2->Draw();
  



    //mg-> Add(graph2);
    //mg->SetTitle("evolution of Mercury u=#frac{1}{r} in general relativity; #phi(rad) ; u (#frac{1}{m})");
  /* 
    graph3 = new TGraph(vNData,x,w);
    graph3->SetTitle(" the difference between Runga-Kutta and exact Newtonian solution");
//    gROOT->SetStyle("Plain");
    graph3->SetMarkerStyle(kOpenCross);
    graph3->SetMarkerColor(kGreen);
    graph3->SetLineColor(kGreen);
    mg->Add(graph3);
*/

 //create legend
 
   
   //vC1->BuildLegend();
   // vC1->cd(2);

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
   grPE->SetTitle(" Mercury orbit with modified graviational force by Runga-Kutta 4th order ");
   
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
//mg->Add(grPE);
   //mg->Draw("ap");
*/
// cleanup
   delete [] x;
   delete [] y;
   delete [] z;
   delete [] w;
    delete [] p;
  // delete graph;
  // delete graph2;

//   f->Write();
}
