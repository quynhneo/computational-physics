#include <iostream>

#include <TString.h>
#include <TStyle.h>
#include <TMath.h>
#include <TFile.h>
#include <TList.h>
#include <TH3.h>
#include <TF1.h>


void randWalkFFTHist() {
    Int_t size=5;
    TCanvas *c1 = new TCanvas("c1");

//    c1->SetLogx(); c1->SetLogy(); c1->SetLogz();

    TH3F *h123 = new TH3F(""," ",size,-3.14,3.14,size, -3.14, 3.14,size,-3.14,3.14);

    TString dir = gSystem->UnixPathName(__FILE__);
   dir.ReplaceAll("randWalkFFTHist.cc","");
   dir.ReplaceAll("/./","/");
  // read file and add to fit object
  // Double_t *x = new Double_t[64000000];
  // Double_t *y = new Double_t[64000000];
  // Double_t *z = new Double_t[64000000]; 
 //  Double_t *w = new Double_t[64000000];
    Double_t vX, vY, vZ,vW;
   Int_t vNData = 0;
   ifstream vInput;
   vInput.open(Form("%sFft3DOut.dat",dir.Data()));
   while (1) {
      vInput >> vX >> vY>>vZ>>vW;//>> vW>>vP;
      if (!vInput.good()) break;
     // x[vNData] = vX;//phi
     // y[vNData] = vY;
     // z[vNData]=vZ;
     // w[vNData]=vW;

   h123->Fill(log10(abs(vX)),log10(abs(vY)),log10(abs(vZ)),log10(vW)); 

      vNData++;
   }//whilei
  gStyle->SetPalette(1);
  h123->GetXaxis()->SetTitle("Kx");
  h123->GetYaxis()->SetTitle("Ky");
  h123->GetZaxis()->SetTitle("Kz");

   h123->SetMarkerColor(kRed);
   //h123->Draw("box");      
   //h123->Draw("boxsame"); //
   //    h123->Draw("COLZ");
    h123->Draw();
   vInput.close();

}

