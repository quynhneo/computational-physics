{
   gROOT->Reset();
   #include "Riostream.h"
   #include "conversione.h"
   #include <string>
   #include <sstream>
   #include <algorithm>

   TCanvas *c1 = new TCanvas("c1","Visualizzazione",10,10,1000,500);
   gStyle->SetOptStat(0);

   TFile *f = new TFile("visualizzazione.root","RECREATE");

   TH2C *h100 = new TH2C("h100","Visualizzazione",32,0.,32.,64,0.,64.);

   h100->GetXaxis()->SetNdivisions(32);
   h100->GetYaxis()->SetNdivisions(16); 
   h100->SetFillColor(3);
//   h100->Draw();

   TPad *grid = new TPad("grid","",0,0,1,1);
   grid->Draw();
   grid->cd();
   grid->SetGrid();
   grid->SetFillStyle(4000);

   TH2C *hgrid = new TH2C("hgrid","",32,0.,32.,64,0.,64.);
   hgrid->GetXaxis()->SetNdivisions(32);
   hgrid->GetYaxis()->SetNdivisions(64);
   hgrid->GetYaxis()->SetLabelOffset(999.);
   hgrid->GetXaxis()->SetLabelOffset(999.); 
   hgrid->Draw();


   ifstream roads_file;
   roads_file.open("MATsec8lh0pj0add3_0.th2.prog");

   string info;
   string maj_reg;

   char thr[11][24];
   char thr1[23][25];
   char stringa_esa_new[11][17];
   char stringa_esa_new_1[23][17];
   char stringa_esa_vera[33][17];

   // prima riga
 
   roads_file >> info >> maj_reg;
 
   // prima parte

   for (int w=1; w<11; w++)
     {
       for (int r=0; r<23; r++)
         {
	   roads_file >> thr[w-1][r];
	 }   
       
       for (int s=24; s<40; s++)
	 {
	   roads_file >> stringa_esa_new[w-1][s-24];
	 }
     }


    // seconda parte

    for (int w=12; w<34; w++)
      {
	for (int r=0; r<24; r++)
	  {
	    roads_file >> thr1[w-12][r];
	  } 
	
	for (int s=25; s<41; s++)
	  {
	    roads_file >> stringa_esa_new_1[w-12][s-25];
	  }
      }


    for (int index1=0; index1<11; index1++)
      {
       for (int index2=0; index2<17; index2++)
	 {
	   stringa_esa_vera[index1][index2]= stringa_esa_new[index1][index2];
	 }
      }

    for (int index1=0; index1<23; index1++)
      {
	for (int index2=0; index2<17; index2++)
	  {
	    stringa_esa_vera[index1+10][index2]= stringa_esa_new_1[index1][index2];
	  }
      }


    // inizio conversione

    char stringa_bin[65];
    char stringa_bin_inv[65];
    string stringa_bin_in;

    for (int index=0; index<32; index++)
      {
	memset(stringa_bin,'\0',64);
	stringa_bin_in=converti(stringa_esa_vera[index][0]);
	
	for(int k=1; k<16; k++)
	  {
	    stringa_bin_in = stringa_bin_in + converti(stringa_esa_vera[index][k]);
	  }
	
	stringa_bin_in.copy(stringa_bin,64);
	
	char a='1';
	int pp=64;

	for (int j=0; j<64; j++)
	  {
	    stringa_bin_inv[j] = stringa_bin[pp];
	    pp--;
	  }
	
	
	for (int i=0; i<64; i++)
	  {
	    if (stringa_bin_inv[i]==a)
	      {
		h100->Fill(index,i,stringa_bin_inv[i]);
	      }
	  }
      }


    h100->Draw("BOX");
//    hgrid->Draw();

    f->Write();

}
