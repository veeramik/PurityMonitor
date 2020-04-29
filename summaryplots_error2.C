Double_t lifetime(double Q_A, double Q_K, double t1, double t2, double t3);

void summaryplots_error2(){

  TCanvas *canvas = new TCanvas("canvas");
  TChain *chain = new TChain("Tree");

  double x[106], y[106], y_err[106], t1tmp[106],t1_errtmp[106];
  
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
 double x_c[106], y_c[106], t2tmp[106], t3tmp[106], G_c_err[106], t2_errtmp[106], t3_errtmp[106];
 
 TChain *chain1 = new TChain("Tree");

  int k1=0;
  for (int j=695; j<919; j++) {
 
    Bool_t f = gSystem->AccessPathName(Form("fitvalues%d_anode.root",j));
    if(f){
      continue;
    }

    else {
      chain1->Add(Form("fitvalues%d_anode.root",j));
      int Status[106];
      int stat;
      
      auto entries1 = chain->GetEntries();
      chain1->SetBranchAddress("Status", &Status);
      for (int i=0; i<entries1; i++){
        chain1->GetEntry(i);
        Status[k1] = stat;
        //cout << Status[k1] << " " << j << endl; 
      }
      //cout << Status[k1] << " " << j << endl;
      if(Status[k1] != 0){
        continue;
        //cout << "failure " << " " << j << endl;                                                      
      }
      else {
        //cout << "success " << " " << j << endl;   

      x_c[k1]=j;

      //auto entries1 = chain->GetEntries();
      double G_0;
      chain1->SetBranchAddress("G_0", &G_0);
      //int entries1 = 114;                                                                                                                    
      //int N = chain1->GetEntries()-1;                                                                                                        
      //n1 = 106;                                                                                                                              
      for (int i=0; i<entries1; i++){
	chain1->GetEntry(i);
	y_c[k1] = 1.16*G_0;
	//cout << "G_0" << endl;                                                                                                                
      }
      double G_0_err;
      chain1->SetBranchAddress("G_0_err", &G_0_err);
      entries1 = chain1->GetEntries();
      for (int i=0; i<entries1; i++){
	chain1->GetEntry(i);
	G_c_err[k1] = G_0_err;                                                                                                    	
	//cout << "G_0_err" << endl;                                                                                                          
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
	//cout << "t3" << endl;                                                                                                              
      }

      double t3_err;
      chain1->SetBranchAddress("t3_err", &t3_err);
      entries1 = chain1->GetEntries();
      for (int i=0; i<entries1; i++){
	chain1->GetEntry(i);
	t3_errtmp[k1] = t3_err;
	//t3_errtmp[k] =0;                                                            
	//cout << "t3_err" << endl;                                                   
      }
      }
      k1+=1;
    }
  }

  double life_t[106], x_lifetime[106], err_tot[109], err_rel[106];
  double Q_A_err[106], Q_K_err[106], gain_err[106], t_1_err[106], t_2_err[106], t_3_err[106];  
  for (int p=0; p<107; p++){
    if(-y[p]/y_c[p]>=1 || -(y[p]+y_err[p])/y_c[p]>=1 || -(y[p])/(y_c[p]+G_c_err[p])>=1){
    continue;
    }
  else { 
    //if (t3_errtmp[p]>t3tmp[p]){
    //t3_errtmp[p]=t3tmp[p];
    //cout << t3_errtmp[p]/t3tmp[p] << endl;
    //cout << t3_errtmp[p] << " " << t3tmp[p] << " " << p << endl;
    // }
    //if (t2_errtmp[p]>t2tmp[p]){
      // cout << t2_errtmp[p] << " " << t2tmp[p] << " " << p <<  endl;
    //t2_errtmp[p]=t2tmp[p];
    //cout << t2_errtmp[p] << " " << t2tmp[p] << " " << p <<  endl;
    //}

    life_t[p] = lifetime(y[p], y_c[p], t1tmp[p], t2tmp[p], t3tmp[p]);
    Q_A_err[p] = lifetime(y[p]+y_err[p], y_c[p], t1tmp[p], t2tmp[p], t3tmp[p]);
    Q_K_err[p] = lifetime(y[p], y_c[p]+G_c_err[p], t1tmp[p], t2tmp[p], t3tmp[p]);
    t_1_err[p] = lifetime(y[p], y_c[p], t1tmp[p]+t1_errtmp[p], t2tmp[p], t3tmp[p]);
    t_2_err[p] = lifetime(y[p], y_c[p], t1tmp[p], t2tmp[p]+t2_errtmp[p], t3tmp[p]);
    t_3_err[p] = lifetime(y[p], y_c[p], t1tmp[p], t2tmp[p], t3tmp[p]+t3_errtmp[p]);
    gain_err[p] = lifetime(0.84*y[p]/0.8, y_c[p], t1tmp[p], t2tmp[p], t3tmp[p]);
    //cout << y[p]-0.84*y[p]/0.8 << " " << y[p]<< endl;
    //cout << Q_K_err[p] << " " << p << endl;  
  
    err_tot[p] = TMath::Sqrt((Q_A_err[p]-life_t[p])*(Q_A_err[p]-life_t[p])+(Q_K_err[p]-life_t[p])*(Q_K_err[p]-life_t[p])+(t_1_err[p]-life_t[p])*(t_1_err[p]-life_t[p])+(t_2_err[p]-life_t[p])*(t_2_err[p]-life_t[p])+(t_3_err[p]-life_t[p])*(t_3_err[p]-life_t[p])+(gain_err[p]-life_t[p])*(gain_err[p]-life_t[p]));
   
    err_rel[p] = err_tot[p]/life_t[p]; 
    cout << err_rel[p] << endl;   

    x_lifetime[p] = x[p];
    //cout << err_tot[p] << " " <<  p << endl;
  }
 }

 int n=106;
 TGraph* gr = new TGraph(n, x_lifetime, err_rel);
 gr->SetTitle("Relative error");
 gr->SetMarkerColor(2);
 gr->SetMarkerStyle(21);
 gr->SetMarkerSize(0.8);
 xAxis = gr->GetXaxis();
 xAxis->SetTitle("Run number");
 xAxis->CenterTitle( kTRUE );
 xAxis->SetTitleOffset( 1.0 );
 xAxis->SetLimits(694, 920);                                                                                                                                              
 yAxis = gr->GetYaxis();
 yAxis->SetTitle("Lifetime error");
 yAxis->CenterTitle( kTRUE );
 yAxis->SetTitleOffset( 1.5 );
 gr->SetMaximum(0.3);                                                                                                       

 gr->SetMinimum(0.02);

 gr->Draw();
 canvas->Print("lifetime_error_8failure_ratio.png");
 canvas->Close();

}

Double_t lifetime(double Q_A, double Q_K, double t1, double t2, double t3){
  
   return (-1/TMath::Log(-Q_A/Q_K))*(t2+(t3+t1)/2);
}
