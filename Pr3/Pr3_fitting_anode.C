Double_t funcPreamp2(Double_t *x, Double_t *par), function(double *x, double *par), stefano(double *x, double *par);

void Pr3_fitting_anode() {

  TCanvas *canvas = new TCanvas("canvas");
  int t=0, l=0;

  for (int u=1; u<2; u++){

    for (int v=1; v<2; v++){

      //Bool_t f = gSystem->AccessPathName(Form("/unix/dune/purity/stefano/gas_ar/silver/second_24_hours/Field_60.120.240Vcm_FibreIn_0%d.0%d.ch3.traces.root", u, v));
      Bool_t f = gSystem->AccessPathName(Form("/unix/dune/purity/abf/vacuum_10.03.2020/silver/30.60.120Vcm.ch3.traces.root", u, v));
      //Bool_t f = gSystem->AccessPathName(Form("/unix/dune/purity/stefano/gas_ar/gold/test_after_48h/gold_recovery.ch3.traces.root", u, v)); 
      if (f){
	continue;
      }

      else{
	cout << u << " " << v << endl;
	//TFile *f3 = new TFile(Form("/unix/dune/purity/stefano/gas_ar/silver/second_24_hours/Field_60.120.240Vcm_FibreIn_0%d.0%d.ch3.traces.root", u, v), "read");
	//TFile *f3 = new TFile(Form("/unix/dune/purity/stefano/gas_ar/gold/test_after_48h/gold_recovery.ch3.traces.root", u, v), "read"); 

	TFile *f3 = new TFile(Form("/unix/dune/purity/abf/vacuum_10.03.2020/silver/30.60.120Vcm.ch3.traces.root", u, v), "read");

      //creating file for the times

      //TFile *f1 = new TFile(Form("silver/times/silver_average_%d.%d_fitvalues%d_PreAmpFunc_second24_gas_ar_anode_times.root", u, v), "recreate");

      //TFile *f1 = new TFile(Form("gold/times/gold_average_%d.%d_fitvalues%d_PreAmpFunc_testafter48_gas_ar_anode_times.root", u, v), "recreate"); 
      TFile *f1 = new TFile(Form("silver/vacuum/vacuum_10.3_times_stefano", u, v), "recreate");

      TTree *timetree = new TTree("Timetree", "Timetree");
      
      //timetree->ReadFile(Form("/unix/dune/purity/stefano/gas_ar/gold/test_after_48h/gold_recovery.ch3.traces.times", u, v), "nro1/C:min/D:hours/D:day/D:month/D:year/D:nro2/C",  ',');

      timetree->ReadFile(Form("/unix/dune/purity/stefano/gas_ar/abf/silver/30.60.120Vcm.ch3.traces.times", u, v), "nro1/C:min/D:hours/D:\day/D:month/D:year/D:nro2/C",  ','); 

      timetree->Fill();
      f1->Write();
      f1->Close();
      
      for (int i=1; i<100; i++) {
	  TCanvas *canvas = new TCanvas("canvas");
	  TGraph *ano_raw = (TGraph*)f3->Get(Form("graph%d", i));
	  double error[200], x[200]={0}, y[200]={0};
	 for (int s=0; s<200; s++) {
	   error[s] = TMath::Sqrt(ano_raw->GetRMS());
	    for (int r=s*500; r<(s+1)*500; r++) {
	      x[s] += ano_raw->GetX()[r];
	      y[s] += ano_raw->GetY()[r];
	    }
	    x[s]/=500;
	    y[s]/=500;

	  }

	  TGraphErrors *ano = new TGraphErrors(200, x, y, 0, error);
	  ano->Draw();
	  //TF1 *fun= new TF1("fun", function, -0.00005, 0.0005, 6);
	  //TF1 *fun= new TF1("fun", funcPreamp2, -0.00005, 0.0005, 6);
	  TF1 *fun= new TF1("fun", stefano, -0.00005, 0.0005, 6);
	 
	   //fun->SetParName(0, "Baseline");
	   //fun->SetParName(1, "Q");
	   //fun->SetParName(2, "t3");
	   //fun->SetParName(3, "delta_T10");
	   //fun->SetParName(4, "riseTime");
	   //fun->SetParName(5, "lifeTime");

	   fun->SetParName(0, "Q"); 
	   fun->SetParName(1, "tpeak"); 
	   fun->SetParName(2, "tstart"); 
	   fun->SetParName(3, "taulife"); 
	   fun->SetParName(4, "tauel"); 
	   fun->SetParName(5, "baseline");
	  
	   //fun->FixParameter(5, 0.00012);
	   //fun->SetParameter(0, -1);
	  
          //fun->SetParameter(0, -0.2);
	  //fun->SetParameter(1, 0.8);
	  //fun->SetParameter(2, 8e-6);
	  //fun->SetParameter(3, 4.5e-7);
	  //fun->SetParameter(4, 1e-4);
	  
	  //fun->SetParLimits(1, 5, 10);
	  //fun->SetParLimits(2, 5e-6, 5e-5);
	  //fun->SetParLimits(3, 1e-8, 8e-6);
	  //fun->SetParLimits(4, 8e-5, 5e-3);
	  
	   fun->FixParameter(3, 0.00012);

	   //fun->SetParameter(0, 1.2);
	   fun->SetParameter(0, 4);
	   //fun->SetParLimits(0, 3, 5);
	   //fun->SetParLimits(0, 0.7, 1.5);
	   fun->SetParameter(1, 5e-6);
	   fun->SetParLimits(1, 5e-7, 5e-4);
	   fun->SetParameter(2, 1e-5); 
	   fun->SetParLimits(2, 8e-6, 1.2e-5);
	   fun->SetParameter(4, 1.3e-4);  
	   
	   

	  TVirtualFitter::SetPrecision(10000);
	  int status = ano->Fit(fun);
	  cout << status << endl;
	  fun->SetLineColor(kBlue);
	  fun->Draw("same");
	  //cout << u << " " << v << endl;
	  //canvas->Print(Form("gold/gold_average_%d.%d_graph%d_PreAmpFunc_testafter48_gas_ar_anode.png", u, v, i));
	  canvas->Print(Form("silver/vacuum/vacuum_10.3_fitvalues%d_stefano.png", i), "recreate");

	  if (status != 0){
	    t += 1;
	  }

	  
	  l+=1;

	  TFile *file = new TFile(Form("silver/vacuum/vacuum_10.3_fitvalues%d_stefano.root", i), "recreate");
	  //TFile *file = new TFile(Form("gold/gold_average_%d.%d_fitvalues%d_PreAmpFunc_testafter48_gas_ar_anode.root", u, v, i), "recreate");
	  TTree *tree = new TTree("Tree", "Tree");

	  //G_0_err = fun->GetParError(0);
	  //t1_err = fun->GetParError(2);
	  //tauel_err = fun->GetParError(4);
	  
	  double value0 = fun->GetParameter(0);

	  double value1 = fun->GetParameter(1);
	  double value2 = fun->GetParameter(2);
	  double value3 = fun->GetParameter(3);
	  double value4 = fun->GetParameter(4);
	  double chi2 = fun->GetChisquare();
	  double NDF = fun->GetNDF();
	  //cout << chi2/NDF << endl;                                                                  
	  //Q_err = fun->GetParError(1);
	  //t3_err = fun->GetParError(2);
	  //t10_err = fun->GetParError(3);
	  //taurise_err = fun->GetParError(4);  
	  
	  double Q_err = fun->GetParError(0);
	  double tpeak_err = fun->GetParError(1);
	  double tstart_err = fun->GetParError(2);
	  double taulife_err = fun->GetParError(3);
	  double tauel_err = fun->GetParError(4);
	  
	  //double value1_err = Q_err;
	  //double value2_err = t3_err;
	  //double value3_err = t10_err;
	  //double value4_err = taurise_err;
	  
	  
	  //tree->Branch("Q",&value1);
	  //tree->Branch("t3", &value2);
	  //tree->Branch("t23",&value3);
	  //tree->Branch("taurise",&value4);

	  //tree->Branch("Q_err",&value1_err);
	  //tree->Branch("t3_err", &value2_err);
	  //tree->Branch("t23_err",&value3_err);
	  //tree->Branch("taurise_err",&value4_err);
	  tree->Branch("chi2",&chi2);
	  tree->Branch("NDF",&NDF);

	  tree->Branch("status", &status);

	  tree->Branch("Q",&value0);
	  tree->Branch("tpeak",&value1);
	  tree->Branch("tstart",&value2);
	  tree->Branch("taulife",&value3);
	  tree->Branch("tauel",&value4);
	  
	  tree->Branch("Q_err",&Q_err);
	  tree->Branch("tpeak_err",&tpeak_err);
	  tree->Branch("tstart_err",&tstart_err);
	  tree->Branch("taulife_err",&taulife_err);
	  tree->Branch("tauel_err",&tauel_err); 

	  tree->Fill();
	  file->Write();
	  file->Close();
	  
	}
	
	//l+=1;
      }
      cout << "failures" << " " << t << endl;
      cout << "Number of files" << " " << l << endl;
    }

  }
}

Double_t funcPreamp2(Double_t *x, Double_t *par) {
  Double_t baseline=par[0];
  Double_t Q=par[1]*1e3;
  Double_t t0=par[2];
  Double_t deltaT10=par[3];
  Double_t t1=t0+deltaT10;
  Double_t riseTime=par[4];
  Double_t lifeTime=par[5];
  Double_t tauEff=1.0/(1.0/riseTime - 1.0/lifeTime);
  Double_t norm=1e3*1.6e-19/(0.15e-12*(t1-t0));

   if(x[0]<t0) return baseline;
   if(x[0]<t1) return  baseline+Q*tauEff*TMath::Exp(-(x[0]-t0)/lifeTime)*(1-TMath::Exp(-(x[0]-t0)/tauEff))*norm;
   return  baseline+Q*tauEff*(TMath::Exp(-(x[0]-t1)/riseTime)*TMath::Exp(-(t1-t0)/lifeTime)-TMath::Exp(-(x[0]-t0)/riseTime))*norm;
      }

Double_t function(double *x, double *par){
  double G_0 = par[0];
  double Q_0 = par[1];
  double t1 = par[2];
  double taulife = par[3];
  double tauel = par[4];
  double t0 = par[5];
  double t3 = par[6];

  double f1 = t1/(1/(1/taulife-1/tauel));
  double f2 = G_0*Q_0/f1;
  double f3 = -TMath::Exp(x[0]-t3/tauel)+TMath::Exp(x[0]-t3/taulife);
  double f4 = (TMath::Exp(-x[0]-t3/tauel))*(TMath::Exp(-x[0]-t3/taulife));

  if (x[0]<0.00001)
    return t0;
  if( x[0]<t1)
    return f2*f3*f4;
  f3 = -TMath::Exp(t1/tauel)+TMath::Exp(t1/taulife);
  f4 = (TMath::Exp(-x[0]/tauel))*(TMath::Exp(-t1/taulife));
  return f2*f3*f4;
}


Double_t stefano(double *x, double *par){
  double Q = par[0];
  double tpeak = par[1];
  double tstart = par[2];
  double taulife = par[3];
  double tauel = par[4];
  double baseline = par[5];

  double f1 = Q/((1/taulife-1/tauel)*(tpeak-tstart));
  double f2 = TMath::Exp((x[0]-tstart)/tauel)-TMath::Exp((x[0]-tstart)/taulife);
  double f3 = TMath::Exp(-(x[0]-tstart)/tauel)*(1-TMath::Exp(-(tpeak-tstart)*(1/taulife-1/tauel)));

  if (x[0]<tstart)
    return baseline;
  if (tstart<x[0]<tpeak)
    return f1*f2;
  if (x[0]>=tpeak)
    return f1*f3;

}
