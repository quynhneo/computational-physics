#include <TStyle.h>
#include <TCanvas.h>

void publishable()
{
gROOT->Reset();
TCanvas *Canvas = new TCanvas("Canvas_aa", "a well done histo",1374,679,700,400);
//Canvas->Divide(1,2);

TH1D* h1 = new TH1D("hist","My Final Results",100,-3,3);

//Canvas->cd(2);
h1->GetXaxis()->SetTitle("x[arbitrary unit]");
h1->GetXaxis()->CenterTitle();
h1->GetYaxis()->SetTitle("f(x)[arbitrary unit]");
h1->GetYaxis()->CenterTitle();


TAxis *axis = h1->GetYaxis();
axis->SetTitleOffset(offset = 1.5);

h1->FillRandom("gaus",100000);
h1->Draw("e1");
h1->Fit("gaus");

TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *text = ptstats->AddText("hist");
   text->SetTextSize(0.0184);
   text = ptstats->AddText("Entries = 100000 ");
   text = ptstats->AddText("Mean  = -0.004887");
   text = ptstats->AddText("RMS   =   0.99");
   text = ptstats->AddText("#chi^{2} / ndf = 103.9 / 97");
   text = ptstats->AddText("Constant =  2391 #pm 9.4 ");
   text = ptstats->AddText("Mean     = -0.005098 #pm 0.003217 ");
   text = ptstats->AddText("Sigma    = 1.003 #pm 0.002 ");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(1);
   ptstats->Draw();
   hist->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(hist);


}
