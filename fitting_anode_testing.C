Double_t function(double *x, double *par);
void fitting_anode_testing() {

  int t=1, l=1;
  for (int i=1200; i<1300; i++) {
    int k=0;
    Bool_t fi = gSystem->AccessPathName(Form("/unix/dune/purity/np02/Filling/Run%d/PrM1_lifeInfo.root", i));
    if(fi){
      continue;
    }
    else {
      TFile *f = new TFile(Form("/unix/dune/purity/np02/Filling/Run%d/PrM1_lifeInfo.root", i), "read");
      TFile *tv = new TFile(Form("theoryvalues_Pr1/theoryvalues%d.root", i), "read");                                                        

      TTree *tree = (TTree*)tv->Get("Tree");
      double t2, t1, t3;
      tree->SetBranchAddress("t1", &t1);
      tree->SetBranchAddress("t2", &t2);
      tree->SetBranchAddress("t3", &t3);
      tree->GetEntry(0);

      //cout  << t2*0.8 << " " << t2*1.1 << endl;
      //cout  << t3*0.8 << " " << t3*1.1 << endl;

      TCanvas *canvas = new TCanvas("canvas");

      double RMSa;
      TTree *metatree =(TTree*)f->Get("metaTree");
      metatree->SetBranchAddress("rawVoltageRMSa", &RMSa);
      metatree->GetEntry(0);
      //cout << 0.001*RMSa << endl;

      //TGraph *ano_raw = (TGraph*)f->Get("gfin_ch5"); 
      TGraph *ano_raw = (TGraph*)f->Get("gfin_ch2");
      double error[152], x[152]={0}, y[152]={0};
      for (int s=0; s<152; s++) {
	//error[s] = TMath::Sqrt(TMath::Sqrt(RMSa));
	//error[s] = TMath::Sqrt(ano_raw->GetRMS());
	error[s] = TMath::Sqrt(RMSa*0.001);
	//cout << error[s] << endl;
	for (int r=s*100; r<(s+1)*100; r++) {
	  x[s] += ano_raw->GetX()[r];
	  y[s] += ano_raw->GetY()[r];
      }
	x[s]/=100;
	y[s]/=100;
	
      }

      //cout << ano_raw->GetRMS() << " " << endl;
      for (int q=1; q<2; q++) {
	//cout << x[q-1] << " " << x[q] << endl;
	cout << x[q]- x[q-1] << endl;  
      }

      TGraphErrors *ano = new TGraphErrors(152, x, y, 0, error);
      ano->SetLineColor(1);
      ano->SetTitle("Anode Data");
      ano->GetXaxis()->SetTitle("Time (s)");
      ano->GetXaxis()->SetTitleOffset( 1.2 );
      ano->GetYaxis()->SetTitle("Amplitude (mV)");
      ano->GetYaxis()->SetTitleOffset( 1.2 );
      ano->SetLineColor(1.0);

      ano->Draw();                                                                                              
      ano->SetMinimum(-70.);
      ano->SetMaximum(50.);
      TF1 *fun= new TF1("fun",function, 0.0001, 0.0011, 6);

      fun->SetParName(0, "G_0");
      fun->SetParName(0, "G_0");
      fun->SetParName(1, "Q_0");
      fun->SetParName(2, "t3");
      fun->SetParName(3, "taulife");
      fun->SetParName(4, "tauel");
      fun->SetParName(5, "t2");

      fun->FixParameter(1, 1.0);
      fun->FixParameter(3,0.001);
      //fun->FixParameter(4,0.0003);

      //t2 = 0.00038;
      //cout << t2 << endl;                                                  
      //fun->SetParameter(2, t2+t1);
      //fun->SetParLimits(2,(t1+t2)*0.9,(t1+t2)*1.1);
      fun->SetParameter(5, t2*2);
      //fun->SetParLimits(5,t2*2*0.8,t2*2*1.1);

      //fun->SetParameter(5, 5e-4);
      //fun->SetParLimits(5, 3e-4*0.7, 3e-4*1.3);

      fun->SetParameter(0, 35);
      //fun->SetParLimits(0, 20, 50);
      //fun->SetParameter(0, 120.);
      //fun->SetParLimits(0,40,130);
      //cout << t3 << endl;                                                  
      //fun->SetParameter(5,(t1+t2+t3));
      //fun->SetParLimits(5, (t1+t2+t3)*0.8, (t1+t2+t3)*1.2);
      //fun->SetParameter(2, t3+t2+t3);                                                             
      fun->SetParameter(2, t3*0.9);
      fun->SetParLimits(2,t3*0.8,t3*1.0);       
      //fun->SetParLimits(2,t3*0.5,t3*1.3); 

      fun->SetParameter(4, 0.00024);
      fun->SetParLimits(4, 0.00024*0.8, 0.00024*1.2);
      fun->Print();
      ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(-1);
      //ROOT::Math::MinimizerOptions::SetDefaultTolerance(0.01);
      //TVirtualFitter::SetMaxIterations(1000);
      TVirtualFitter::SetPrecision(200000);
      //cout << TVirtualFitter::GetPrecision() << endl;
      //ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(10000);
      ano->Fit(fun);
      fun->SetLineColor(kBlue);
      fun->Draw("same");
      canvas->Print(Form("anodefit_Pr1/anodefit_Run%d.png", i));
      
       f->Close();
     
      TFile *file = new TFile(Form("fittingvalues_Pr1/fitvalues%d_anode.root", i), "recreate");
       TTree *tree = new TTree("Tree", "Tree");

      G_0_err = fun->GetParError(0);
      t2_err = fun->GetParError(2);
      tauel_err = fun->GetParError(4);
      t3_err = fun->GetParError(5);

      
      int status = ano->Fit(fun);
      cout << status << endl;

       
      if (status != 0){
	t += 1;
        //cout << "failure" << endl;
      }

      double value0 = fun->GetParameter(0);
      double value2 = fun->GetParameter(5);
      double value4 = fun->GetParameter(4);
      double value5 = fun->GetParameter(2);
      double chi2 = fun->GetChisquare();
      double NDF = fun->GetNDF();
      //cout << chi2/NDF << endl;

      double value0_err = G_0_err;
      double value2_err = t2_err;
      double value4_err = tauel_err;
      double value5_err = t3_err;
      tree->Branch("G_0",&value0);
      tree->Branch("t2",&value2);
      tree->Branch("tauel",&value4);
      tree->Branch("t3",&value5);
      tree->Branch("G_0_err",&value0_err);
      tree->Branch("t2_err",&value2_err);
      tree->Branch("tauel_err",&value4_err);
      tree->Branch("t3_err",&value5_err);
      tree->Branch("chi2",&chi2);
      tree->Branch("NDF",&NDF);
      tree->Branch("Status", &status);

      tree->Fill();
      file->Write();
      file->Close();

      l+=1;

      cout << " " << endl;
      cout << " " << endl;
      cout << " " << endl;
      cout << " " << endl;
      
    }
  }
  cout << "failures" << " " << t-1 << endl;
  cout << "Number of files" << " " << l-1 << endl;
  //cout << "you're shit, try again idiot :)" << endl;
}


Double_t function(double *x, double *par){
  double G_0 = par[0];
  double Q_0 = par[1];
  //double Q_0 = par[1];                                                      \
                                                                               
  double t1 = par[2];
  //double t1 = par[2];                                                       \
                                                                               
  //double t1 = 2.48955553188e-05;                                            \
                                                                               
  double taulife = par[3];
  //double taulife = 0.00121985519281;                                        \
                                                                               
  double tauel = par[4];
  //double tauel = 0.000319;                                                  \
                                                                               

  double t_0 = par[5];

  double f1 = t1/(1/(1/taulife-1/tauel));
  double f2 = G_0*Q_0/f1;
  double f3 = -TMath::Exp((x[0]-t_0)/tauel)+TMath::Exp((x[0]-t_0)/taulife);
  double f4 = (TMath::Exp(-(x[0]-t_0)/tauel))*(TMath::Exp(-(x[0]-t_0)/taulife)\
					       );

  if (x[0]<t_0)
    return 0;
  if( x[0]<t1)
    return f2*f3*f4;
  f3 = -TMath::Exp(t1/tauel)+TMath::Exp(t1/taulife);
  f4 = (TMath::Exp(-x[0]/tauel))*(TMath::Exp(-t1/taulife));
  return f2*f3*f4;
}

