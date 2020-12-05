#include <iostream>

#include <TString.h>
#include <TStyle.h>
#include <TMath.h>
#include <TFile.h>
#include <TList.h>
#include <TH3.h>
#include <TF1.h>


void randWalkHist() {
    TCanvas *c1 = new TCanvas("c1");
    TH3F *h123 = new TH3F("legend"," RayLeigh-Levy random walk in real space",250,-125,125,250, -125, 125,250,-125,125);

    TString dir = gSystem->UnixPathName(__FILE__);
   dir.ReplaceAll("randWalkHist.cc","");
   dir.ReplaceAll("/./","/");
  // read file and add to fit object
//   Double_t *x = new Double_t[50000];
//   Double_t *y = new Double_t[50000];
//   Double_t *z = new Double_t[50000]; 
   Double_t vX, vY, vZ;
   Int_t vNData = 0;
   ifstream vInput;
   vInput.open(Form("%srandwalk.dat",dir.Data()));
   while (1) {
      vInput >> vX >> vY>>vZ;//>> vW>>vP;
      if (!vInput.good()) break;
//      x[vNData] = vX;//phi
//      y[vNData] = vY;
//      z[vNData]=vZ;
      vNData++;


   h123->Fill(vX,vY,vZ); 

   }//whilei
 gStyle->SetPalette(1);

   h123->SetMarkerColor(kBlue);
   h123->Draw("scat=1");      
  // h123->Draw("boxsame"); //   h123->Draw("COLZ");

   vInput.close();

}

