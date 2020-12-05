#include "Riostream.h"
#include "TGraph.h"
#include "TFile.h"//need?
#include "TCanvas.h"
#include "TMath.h"
#include "TString.h"
void p2root() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

TString dir = gSystem->UnixPathName(__FILE__);
   dir.ReplaceAll("p2root.cc","");
   dir.ReplaceAll("/./","/");
  // read file and add to fit object

   Double_t *x1 = new Double_t[50000000];
   Double_t *y1 = new Double_t[50000000];
  // Double_t *w = new Double_t[10000];   

   Double_t vX1, vY1;
   Int_t vNData1 = 0;
   ifstream vInput1;
   vInput1.open(Form("%sp2.dat",dir.Data()));
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
   graph1 = new TGraph(vNData1-2,x1,y1);
    graph1->SetMarkerStyle(kFullDotMedium);
    graph1->SetMarkerColor(kBlue);
    mg->Add(graph1);
  //  vC1->BuildLegend();

    mg->SetTitle("Potential vs Monte-Carlo step; Step  ; Potential ");
    mg->Draw("ap");
    TLine *l = new TLine(x1[vNData1-1] , y1[vNData1-1] ,100000,y1[vNData1-1] );
    l->SetLineColor(kRed);
    l->SetLineWidth(3);
    l->Draw();

    TLine *l1 = new TLine(5000, y1[vNData1-1]  , x1[vNData1-1] , y1[vNData1-1] );
    l1->SetLineColor(kRed);
    l1->SetLineStyle(7);
    l1->SetLineWidth(3);
    l1->Draw();
    
    vc2->SaveAs("2U.png");
// cleanup
   delete [] x1;
   delete [] y1;
///
   Double_t *x3 = new Double_t[1000000];
   Double_t *y3 = new Double_t[1000000];
   //Double_t *w1 = new Double_t[100000];   
  // Double_t *w2 = new Double_t[100000];   
   Double_t vX3, vY3;
   Int_t vNData3 = 0;
   ifstream vInput3;
   vInput3.open(Form("%sp2C.dat",dir.Data()));
   while (1 ) {
      vInput3 >> vX3 >> vY3;//>> vW>>vP;
      if (!vInput3.good()) break;
      x3[vNData3] = vX3; //w1[vNData3]=0;
      y3[vNData3] = vY3; //w2[vNData3]= 1.0/exp(0);
         vNData3++;
   }//whilei

   vInput3.close() ;
     vc3 = new TCanvas() ;
   TMultiGraph *mg2 = new TMultiGraph();
   graph3 = new TGraph(10000,x3,y3);
    graph3->GetXaxis()->SetRangeUser(0,10000);
    graph3->SetMarkerStyle(kFullDotMedium);
    graph3->SetMarkerColor(kRed);
    mg2->Add(graph3);
    mg2->SetTitle("Correlation function; number of step m ; C(m) ");
   // graph4 = new TGraph(vNData3,w1,w2);
   // mg2->Add(graph4);
    mg2->Draw("ap");
   // cout<<"the point "<< x3[vNData3-1]<< " " << y3[vNData3-1]<<endl ; 
    TLine *line = new TLine(x3[vNData3-1],-0.6,x3[vNData3-1],1);
  line->SetLineColor(kBlue);
  line->Draw();
// cleanup
   delete [] x3; 
   delete [] y3;
//------
  vc3->SaveAs("2cm.png");

   Double_t *x = new Double_t[10000];
   Double_t *y = new Double_t[10000];
   Double_t *z = new Double_t[10000];
  // Double_t *w = new Double_t[10000];   

   Double_t vX, vY, vZ;
   Int_t vNData = 0;
   ifstream vInput;
   vInput.open(Form("%sp2H.dat",dir.Data()));
   while (1) {
      vInput >> vX;//>> vW>>vP;
      if (!vInput.good()) break;
      x[vNData] = vX;//phi
         vNData++;
    }
  vInput.close() ;
    Int_t nbin=100;
    Double_t bin_size = 5.0/Double_t(nbin);
   vC1 = new TCanvas("vC1","GS",0,0,800,600) ;
  TH1D *h1 = new TH1D("h1", "histogram title", nbin, 0.,5.0);
    for ( Int_t j=0;j<vNData;j++)
    {
      h1->Fill(x[j] );
    }
    h1->Scale(1/(bin_size)/vNData); 
    h1->Fit("expo") ;
    TF1 *f = h1->GetFunction("expo");//get the fit function
    Double_t C = f->GetParameter(0); C= exp(C);//get the const 
    Double_t m = f->GetParameter(1);// get the slop
    TString fx("fit result f(x)="); //prepare to print
    fx +=Form("%.2f",C);//convert floating point double to string 
    fx +=" e^{";
    fx +=Form("%.2f",m); fx +="x}";
    
    gStyle->SetOptStat(0);//turn off stat box 
    gStyle->SetOptFit(0);//turn off fit box
    h1->SetFillColorAlpha(kBlue,0.15);
    h1->SetLineWidth(3);
    h1->Draw();
    h1->SetTitle( "Histogram of position and exponential fit ; x ; distribution ");
   TPaveText *pt = new TPaveText(3.2,1.4 ,5.5,1.6);
    pt->AddText(fx);//print out the fit function
    pt->Draw();
    delete [] x;
//------
  vC1->SaveAs("2H.png");
}
