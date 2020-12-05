#include "Riostream.h"
#include "TGraph.h"
#include "TFile.h"//need?
#include "TCanvas.h"
#include "TMath.h"
Double_t f(Double_t *x, Double_t *par)
{

    Double_t fitval=0;// - par[0+41]*sin(0.0*x[0]) ;
    Double_t* k= new Double_t[21];
    for (i=0;i<21;i++)
        { 
        Int_t n_k; 
        n_k= i;
        k[i]= double(n_k)*M_PI/40.0;// cout <<i<<" "<<k[i]<<endl;
        if (i==0) fitval = fitval+ par[i];
        else fitval =fitval+ 2.0* par[i]*cos(k[i]*x[0]) -2.0* par[i+20]*sin(k[i]*x[0]) ;
        }
   return fitval;
}


void prob4root() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

TString dir = gSystem->UnixPathName(__FILE__);
   dir.ReplaceAll("prob4root.cc","");
   dir.ReplaceAll("/./","/");
   Double_t *x1 = new Double_t[200];
   Double_t *y1 = new Double_t[200];
   Double_t *x0 = new Double_t[200];   

   Double_t *a = new Double_t[200];
   Double_t *b = new Double_t[200];
   Double_t *c = new Double_t[200];

    Double_t vX0,vX1, vY1,vA,vB;
   Int_t vNData1 = 0;
   ifstream vInput1;
   vInput1.open(Form("%sprob4.powSpect.dat",dir.Data()));
   while (1) {
      vInput1 >> vX0 >> vX1 >> vY1>>vA>>vB;//>> vW>>vP;
      if (!vInput1.good()) break;
     x0[vNData1]=vX0;
      x1[vNData1] = vX1;//phi
        if (vNData1==0)      y1[vNData1] = vY1;
        else y1[vNData1] = 2*vY1;
     a[vNData1]=vA; c[vNData1]=vA; cout<< "c: "<<vNData1<<" " << c[vNData1]<<" ";
     b[vNData1]=vB; c[vNData1+20]=vB; cout << "c: "<<vNData1+20<<" " <<c[vNData1+20]<<endl;
         vNData1++;
   }//whilei
    std::cout<<"num of line"<<vNData1<<endl;
   vInput1.close() ; 
   vc2 = new TCanvas() ; vc2->Divide(2);
   vc2->cd(1);
   graph1 = new TGraph(vNData1,x1,y1);

    graph1->SetMarkerStyle(kFullDotMedium);
    graph1->SetLineColor(kBlue);
    graph1->SetTitle("Power spectrum");
    graph1->GetXaxis()->SetRangeUser(0,1.6);
  //  vC1->BuildLegend();

//---
    graph1->Draw("AL");
  //  vC1->BuildLegend();

// cleanup
//   delete [] x3;
//   delete [] y3;
//------
vc2->cd(2);
  // TCanvas *c1 = new TCanvas("c1","the fit canvas",500,400);
  // Creates a Root function based on function fitf above
     TF1 *func = new TF1("KdV solution t=200 and #alpha=0.001",f,-40,40,41);
  
  // Sets initial values and parameter names
     
    func->SetParameters(c);
     func->Draw();
vc2->SaveAs("4.alpha.png");
// cleanupv
   delete [] x1;
   delete [] y1;delete [] x0; delete [] a; delete [] b; delete [] c;
}
