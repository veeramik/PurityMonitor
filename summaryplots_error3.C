Double_t lifetime(double Q_A, double Q_K, double t1, double t2, double t3);

void summaryplots_error3(){

  TCanvas *canvas = new TCanvas("canvas");
  TChain *chain = new TChain("Tree");

  double x[114], y[114], y_err[114], t1tmp[114],t1_errtmp[114];
  double chi2_cat[114], NDF_cat[114];
  int k=0;
  for (int j=695; j<919; j++) {
    Bool_t f = gSystem->AccessPathName(Form("fitvalues%d.root",j));
    if(f){
      continue;
    }
    else {

      chain->Add(Form("fitvalues%d.root",j));

      x[k]=j;


      double G_0;
      chain->SetBranchAddress("G_0", &G_0);

      auto entries = chain->GetEntries();

      for (int i=0; i<entries; i++){
        chain->GetEntry(i);
        y[k] = 0.8*G_0/10;

      }

      double G_0_err;
      chain->SetBranchAddress("G_0_err", &G_0_err);
      entries = chain->GetEntries();
      for (int i=0; i<entries; i++){
        chain->GetEntry(i);
        y_err[k] = 0.8*G_0_err/10;

      }

      double t1;

      chain->SetBranchAddress("t1", &t1);
      entries = chain->GetEntries();
      for (int i=0; i<entries; i++){
        chain->GetEntry(i);
        t1tmp[k] = t1;

      }
      double chi2;
      chain->SetBranchAddress("chi2", &chi2);
      entries = chain->GetEntries();
      for (int i=0; i<entries; i++){
        chain->GetEntry(i);
        chi2_cat[k] = chi2;
        //cout << chi2_cat[k] << endl;
      }
      double NDF;
      chain->SetBranchAddress("NDF", &NDF);
      entries = chain->GetEntries();
      for (int i=0; i<entries; i++){
        chain->GetEntry(i);
        NDF_cat[k] = NDF;
	//cout << NDF_cat[k] << endl;
      }

      double t1_err;

      chain->SetBranchAddress("t1_err", &t1_err);
      entries = chain->GetEntries();
      for (int i=0; i<entries; i++){
        chain->GetEntry(i);
        t1_errtmp[k] = t1_err;

      }
      //cout << j << " " << k << endl;                                                                                 
      k+=1;
    }
  }
  double x_c[114], y_c[114], t2tmp[114], t3tmp[114], G_c_err[114], t2_errtmp[114], t3_errtmp[114];
  double NDF_ano[114], chi2_ano[114];
  TChain *chain1 = new TChain("Tree");

  int k1=0;
  for (int j=695; j<919; j++) {
    Bool_t f = gSystem->AccessPathName(Form("fitvalues%d_anode.root",j));
    if(f){
      continue;
    }

    else {
      chain1->Add(Form("fitvalues%d_anode.root",j));

      x_c[k1]=j;

      auto entries1 = chain->GetEntries();
      double G_0;
      chain1->SetBranchAddress("G_0", &G_0);
                                                                                                                            
      for (int i=0; i<entries1; i++){
        chain1->GetEntry(i);
        y_c[k1] = G_0;
       
       }
	double G_0_err;
	chain1->SetBranchAddress("G_0_err", &G_0_err);
	entries1 = chain1->GetEntries();
	for (int i=0; i<entries1; i++){
	  chain1->GetEntry(i);
	  G_c_err[k1] = G_0_err;                                                                                      
	}

	double t2;
	chain1->SetBranchAddress("t2", &t2);
	entries1 = chain1->GetEntries();
	for (int i=0; i<entries1; i++){
	  chain1->GetEntry(i);
	  t2tmp[k1] = t2;
	  //cout << "t2" << endl;                                                                                        
	}
        double t2_err;
        chain1->SetBranchAddress("t2_err", &t2_err);
        entries1 = chain1->GetEntries();
	for (int i=0; i<entries1; i++){
          chain1->GetEntry(i);
          t2_errtmp[k1] = t2_err;                                                                                   

	}
	double t3;
	chain1->SetBranchAddress("t3", &t3);
	entries1 = chain1->GetEntries();
	for (int i=0; i<entries1; i++){
	  chain1->GetEntry(i);
	  t3tmp[k1] = t3;
	}
	double NDF;
        chain1->SetBranchAddress("NDF", &NDF);
        entries1 = chain1->GetEntries();
        for (int i=0; i<entries1; i++){
          chain1->GetEntry(i);
          NDF_ano[k1] = NDF;
	  //cout << NDF_val[k1] << endl;
        }

	double chi2;
        chain1->SetBranchAddress("chi2", &chi2);
        entries1 = chain1->GetEntries();
        for (int i=0; i<entries1; i++){
          chain1->GetEntry(i);
          chi2_ano[k1] = chi2;
        }

	double t3_err;
	chain1->SetBranchAddress("t3_err", &t3_err);
	entries1 = chain1->GetEntries();
	for (int i=0; i<entries1; i++){
	  chain1->GetEntry(i);
	  t3_errtmp[k1] = t3_err;
	  	}
	k1+=1;
    }
  }

  double t2_th[120], x_th[120], t3_th[114], t1_th[120];
  TChain *chain2 = new TChain("Tree");

  int k2=0;
  for (int j=695; j<919; j++) {
    Bool_t f = gSystem->AccessPathName(Form("theoryvalues%d.root",j));
    if(f){
      continue;
      }

    else {
      chain2->Add(Form("theoryvalues%d.root",j));
      x_th[k2]=j;

      double t1;
      chain2->SetBranchAddress("t1", &t1);
      entries2 = chain2->GetEntries();
      for (int i=0; i<entries2; i++){
        chain->GetEntry(i);
        t1_th[k2] = t1;
	//cout << t1_th[k2] << endl;
      }

      double t2;
      chain2->SetBranchAddress("t2", &t2);
      for (int i=0; i<entries2; i++){
        chain->GetEntry(i);
        t2_th[k2] = t2;
	//cout <<t2_th[k2] << endl;
      }

      double t3;
      chain2->SetBranchAddress("t3", &t3);
      for (int i=0; i<entries2; i++){
        chain->GetEntry(i);
        t3_th[k2] = t3;
	//cout << t3_th[k2] << endl;
      }
      k2+=1;
  }
}   
  double chi2_red_ano[114], chi2_red_cat[114], lifet_theory[114];
  double life_t[114], x_lifetime[114], err_tot[114], ratio[114];
  double Q_A_err[114], Q_K_err[114], gain_err[114], t_1_err[114], t_2_err[114], t_3_err[114];
  
  for (int p=0; p<115; p++){
    if(-y[p]/y_c[p]>=1 || -(y[p]+y_err[p])/y_c[p]>=1 || -(y[p])/(y_c[p]+G_c_err[p])>=1){
      continue;
    }
    else {
      //if (t3_errtmp[p]>t3tmp[p]){
      //t3_errtmp[p]=t3tmp[p];
	//cout << t3_errtmp[p] << " " << t3tmp[p] << " " << p << endl;                                                   
      //}
      //if (t2_errtmp[p]>t2tmp[p]){
      //t2_errtmp[p]=t2tmp[p];
	//cout << t2_errtmp[p] << " " << t2tmp[p] << " " << p <<  endl;                                                  
      //}
      //if (t1_errtmp[p]>t1tmp[p]){
      //t1_errtmp[p]=t1tmp[p];
      //cout << t1_errtmp[p] << " " << t1tmp[p] << " " << p << endl;
      // }
     
      if (t3_errtmp[p]>t3tmp[p] || t2_errtmp[p]>t2tmp[p]){

	life_t[p] = lifetime(y[p], y_c[p], t1tmp[p], t2tmp[p], t3tmp[p]);
	Q_A_err[p] = lifetime(y[p]+y_err[p], y_c[p], t1tmp[p], t2tmp[p], t3tmp[p]);
	Q_K_err[p] = lifetime(y[p], y_c[p]+G_c_err[p], t1tmp[p], t2tmp[p], t3tmp[p]);
	t_1_err[p] = lifetime(y[p], y_c[p], t1tmp[p]+t1_errtmp[p], t2tmp[p], t3tmp[p]);
	t_2_err[p] = lifetime(y[p], y_c[p], t1tmp[p], t2tmp[p]+t2_errtmp[p], t3tmp[p]);
	t_3_err[p] = lifetime(y[p], y_c[p], t1tmp[p], t2tmp[p], t3tmp[p]+t3_errtmp[p]);
	gain_err[p] = lifetime(0.84*y[p]/0.8, y_c[p], t1tmp[p], t2tmp[p], t3tmp[p]);

	lifet_theory[p] = lifetime(y[p], y_c[p], t1_th[p], t2_th[p], t3_th[p]);
	//cout << lifet_theory[p] << " " << life_t[p] << endl;
        ratio[p] = life_t[p]/lifet_theory[p];       
        cout << ratio[p] << " " << p << endl; 

         err_tot[p] = TMath::Sqrt((Q_A_err[p]-life_t[p])*(Q_A_err[p]-life_t[p])+(Q_K_err[p]-life_t[p])*(Q_K_err[p]-life_t[p])+(t_1_err[p]-life_t[p])*(t_1_err[p]-life_t[p])+(t_2_err[p]-life_t[p])*(t_2_err[p]-life_t[p])+(t_3_err[p]-life_t[p])*(t_3_err[p]-life_t[p])+(gain_err[p]-life_t[p])*(gain_err[p]-life_t[p]));
      x_lifetime[p] = x[p];
      //cout << err_tot[p] << " " << p << endl;
      }
    }
  }

  int n=114;
  int n1=37;
  TGraph* gr = new TGraph(n1, x_lifetime, ratio);
  gr->SetTitle("Data vs. theory");
  gr->SetMarkerColor(2);
  gr->SetMarkerStyle(21);
  gr->SetMarkerSize(0.8);
  xAxis = gr->GetXaxis();
  xAxis->SetTitle("Run number");
  xAxis->CenterTitle( kTRUE );
  xAxis->SetTitleOffset( 1.0 );
  xAxis->SetLimits(694, 920);                                                                                        

  yAxis = gr->GetYaxis();
  yAxis->SetTitle("Ratio");
  yAxis->CenterTitle( kTRUE );
  yAxis->SetTitleOffset( 1.5 );
  gr->SetMaximum(1.3);                                                                                              


  gr->SetMinimum(0.9);                                                                                              

  gr->Draw("ap");
  canvas->Print("data_vs_theory_ratio_25failure.png");
  canvas->Close();

}
Double_t lifetime(double Q_A, double Q_K, double t1, double t2, double t3){

  return (-1/TMath::Log(-Q_A/Q_K))*(t2+(t3+t1)/2);
}
