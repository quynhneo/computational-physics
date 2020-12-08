
Double_t myfunction(Double_t *x, Double_t *par)
{
   Float_t xx =x[0];
   Double_t f = TMath::Abs(par[0]*sin(par[1]*xx)/xx);
   return f;
}
void myfunc()
{
   TF1 *f1 = new TF1("myfunc",myfunction,0,10,2);
   f1->SetParameters(2,1);
   f1->SetParNames("constant","coefficient");
   f1->Draw();
}
