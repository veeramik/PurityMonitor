double function(double *x, double *par); 

void fitting_macro2() {

  for (int i=1180; i<1200; i++) {
    Bool_t fi = gSystem->AccessPathName(Form("/unix/dune/purity/np02/Filling/Run%d/PrM1_lifeInfo.root", i));
    if(fi){
      continue;
    }
    else {

      //for (int i=695; i<700; i++){
   TFile *f = new TFile(Form("/unix/dune/purity/np02/Filling/Run%d/PrM1_lifeInfo.root", i), "read");

   TCanvas *canvas = new TCanvas("canvas");


   //cathode
   //TGraph *cattemp = (TGraph*)f->Get("gfin_ch4");                                                                            
   TGraph *cattemp = (TGraph*)f->Get("gfin_ch1");
   TGraph *cat = new TGraph(cattemp->GetN(),cattemp->GetX(),cattemp->GetY());
   //TGraph *cat =(TGraph*)f->Get("gfin_ch1");                                                                     
   TList *listtemp = (TList*)cat->GetListOfFunctions();

   TList *list = new TList(listtemp);
   cat->SetTitle("Cathode Data");
   cat->GetXaxis()->SetTitle("Time (s)");
   cat->GetYaxis()->SetTitle("Amplitude (mV)");
   cat->SetLineColor(1);
   cat->Draw();
   cat->GetYaxis()->SetRangeUser(-70, 30);
   
   TF1 *fun= new TF1("fun", function, -0.001, 0.0011, 5);

   fun->SetParName(0, "G_0");
   fun->SetParName(1, "Q_0");
   fun->SetParName(2, "t1");
   fun->SetParName(3, "taulife");
   fun->SetParName(4, "tauel");

   fun->FixParameter(1, 0.1);
   fun->FixParameter(3,0.00121985519281);
   //fun->FixParameter(3, 0.0013);

   fun->SetParameter(0,-420.0);
   fun->SetParameter(2,3e-5 );
   fun->SetParameter(4,0.0003);


   cat->Fit(fun);
   fun->SetLineColor(kBlue);
   fun->Draw("same");
   canvas->Print(Form("cathodefit_Pr1/cathodefit_Run%d.png", i));

   f->Close();
   TFile *file = new TFile(Form("fittingvalues_Pr1/fitvalues%d.root", i), "recreate");
   TTree *tree = new TTree("Tree", "Tree");

   G_0_err = fun->GetParError(0);
   t1_err = fun->GetParError(2);
   tauel_err = fun->GetParError(4);

   double value0 = fun->GetParameter(0);
   double value2 = fun->GetParameter(2);
   double value4 = fun->GetParameter(4);
   double chi2 = fun->GetChisquare();
   double NDF = fun->GetNDF();
   cout << chi2/NDF << endl;

   double value0_err = G_0_err;
   double value2_err = t1_err;
   double value4_err = tauel_err;

   tree->Branch("G_0",&value0);
   tree->Branch("t1",&value2);
   tree->Branch("tauel",&value4);

   tree->Branch("G_0_err",&value0_err);
   tree->Branch("t1_err",&value2_err);
   tree->Branch("tauel_err",&value4_err);

   tree->Branch("chi2",&chi2);
   tree->Branch("NDF",&NDF);

   tree->Fill();
   file->Write();
   file->Close();

   //}

    }
  }
}

Double_t function(double *x, double *par){
  double G_0 = par[0];
  double Q_0 = par[1];
  //double Q_0 = par[1];                                                                                          
  double t1 = par[2];
  //double t1 = 2.48955553188e-05;                                                                                
  double taulife = par[3];
  //double taulife = 0.00121985519281;                                                                            
  double tauel = par[4];
  //double tauel = 0.000319;                                                                                      
  double f1 = t1/(1/(1/taulife-1/tauel));
  double f2 = G_0*Q_0/f1;
  double f3 = -TMath::Exp(x[0]/tauel)+TMath::Exp(x[0]/taulife);
  double f4 = (TMath::Exp(-x[0]/tauel))*(TMath::Exp(-x[0]/taulife));

  if (x[0]<0)
    return 0;
  if( x[0]<t1)
    return f2*f3*f4;
  f3 = -TMath::Exp(t1/tauel)+TMath::Exp(t1/taulife);
  f4 = (TMath::Exp(-x[0]/tauel))*(TMath::Exp(-t1/taulife));
  return f2*f3*f4;
}
