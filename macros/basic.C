#include "Riostream.h"
void basic() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
//   see a variant of this macro in basic2.C
//Author: Rene Brun
      

// read file $ROOTSYS/tutorials/tree/basic.dat
// this file has 3 columns of float data
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("basic.C","");
   dir.ReplaceAll("/./","/");
   ifstream in;
   in.open(Form("%sbasic.dat",dir.Data()));

   Float_t x,y;
   Float_t x_array[50];
   Float_t y_array[50];
   Int_t nlines = 0;
//   TFile *f = new TFile("basic.root","RECREATE");
//   TH1F *h1 = new TH1F("h1","x distribution",100,-4,4);
//   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","x:y");

   while (1) {
      in >> x >> y ;
      if (!in.good()) break;
      if (nlines < 5) printf("x=%8f, y=%8f\n",x,y);
//      h1->Fill(x);
//      ntuple->Fill(x,y);
      x_array[nlines]=x;
      y_array[nlines]=y;
      
      printf("x[%f8]=%8f\n",nlines,x_array[nlines]);  
      printf("y[%f8]=%8f\n",nlines,y_array[nlines]);  
      
      nlines++;
   }
   printf(" found %d points\n",nlines);

   in.close();

//   f->Write();
}
