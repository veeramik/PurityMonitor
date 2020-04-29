void summaryplots_lifetime2(){

  TCanvas *canvas = new TCanvas("canvas");
  TChain *chain = new TChain("Tree");

  double x[428], y[428], t_1[428];
  //double x[106], y[106], t_1[106];
  int n, l;

  int k=0;
  for (int j=450; j<1200; j++) {
    //cout << Form("~/Documents/PurityMonitor/fitvalues%d_anode.root",j) << endl;                                          \              

    Bool_t f = gSystem->AccessPathName(Form("fittingvalues_Pr1/fitvalues%d.root",j));
    if(f){
      continue;
    }
    else {
      
      chain->Add(Form("fittingvalues_Pr1/fitvalues%d.root",j));
        x[k]=j;
	      
      double G_0;
      chain->SetBranchAddress("G_0", &G_0);


      auto entries = chain->GetEntries();
      //cout << entries << endl;                                                                                           \                   

      //double x[100], y[100];                                                                                             \                   
      //cout << entries << endl;
      int N = chain->GetEntries()-1;
      //n = N;                                                                                                             \                   

      for (int i=0; i<entries; i++){
        chain->GetEntry(i);
        y[k] = 0.8*G_0/10;
	//cout << y[k] << endl;                                                                                                                
        //x[i] = 700+i;                                                                                                    \                   
         }
      double t1;
      chain->SetBranchAddress("t1", &t1);
      for (int i=0; i<entries; i++){
        chain->GetEntry(i);
        t_1[k] = t1;
         }
      //}
      //cout << k << " " << j << endl;
      k+=1;
      }
  }

  double x_c[428], y_c[428], t_2[428], t_3[428];
  //double x_c[106], y_c[106], t_2[106], t_3[106];
  int n1;
  TChain *chain1 = new TChain("Tree");

  int k1=0;
  for (int j=450; j<1200; j++) {
    //cout << Form("~/Documents/PurityMonitor/fitvalues%d.root",j) << endl;                                                                    
    Bool_t f = gSystem->AccessPathName(Form("fittingvalues_Pr1/fitvalues%d_anode.root",j));
    if(f){
      //cout << "No file" << " " << j << endl;                   
      continue;
    }
    else {
      chain1->Add(Form("fittingvalues_Pr1/fitvalues%d_anode.root",j));
      
      int Status;
      //cout << Status << " " << j << endl;
      chain1->GetEntry(0);
      chain1->SetBranchAddress("Status", &Status);
      if(Status != 0){
        continue;
        //cout << "failure " << " " << j << endl;
      }
      else {
	//cout << "success " << " " << j << endl;      
 
      x_c[k1]=j;
      
      double G_0;
      chain1->SetBranchAddress("G_0", &G_0);

      auto entries1 = chain1->GetEntries();
      //cout << entries << endl;                                                                                           \                   

      //double x[100], y[100];                                                                                             \                   

      int N = chain1->GetEntries()-1;
      //n = N;                                                                                                             \                   

      for (int i=0; i<entries1; i++){
        chain1->GetEntry(i);
	y_c[k1] = 1.16*G_0;
	//cout << y_c[k1] << "  " << i << endl;
      }

	double t2;
	chain1->SetBranchAddress("t2", &t2);
	for (int i=0; i<entries1; i++){
	  chain1->GetEntry(i);
	  t_2[k1] = t2;
	  //cout << t_2[k1] << " " << i << endl;
	}

	double t3;
        chain1->SetBranchAddress("t3", &t3);
        for (int i=0; i<entries1; i++){
          chain1->GetEntry(i);
          t_3[k1] = t3;
	  //cout << t_3[k1] << " " << i << endl;
	  }
      }
      //}
      //cout << k1 << " " << j << endl;
      k1+=1;
    }
  }


  int n = 428;
  double lifetime[428], x_lifetime[428];                     
  //int n = 106;
  //double lifetime[106], x_lifetime[106];
  for (int p=0; p<428; p++){
    //cout << -y[p]/y_c[p] << endl;
    //cout << t_1[p] << endl;
    if(-y[p]/y_c[p]>1  || t_3[p] < 1e-7 || t_3[p] > 1e-4){
    continue;
      }
    else{
     //cout << -1/TMath::Log(-y[p]/y_c[p]) << endl;
      //cout << t_3[p] << " " << p << endl;
     lifetime[p] =  -1/TMath::Log(-y[p]/y_c[p])*((t_3[p]+t_1[p])/2+t_2[p]);
     x_lifetime[p] = x[p];
     cout << lifetime[p] << " " << p << endl;                                                                         
  }                           

  }
  TGraph* gr = new TGraph(n, x_lifetime,lifetime);
  gr->SetTitle("Summary of Lifetime");
  gr->SetMarkerColor(2);
  gr->SetMarkerStyle(21);
  gr->SetMarkerSize(0.8);

  xAxis = gr->GetXaxis();
  xAxis->SetTitle("Run number");
  xAxis->CenterTitle( kTRUE );
  xAxis->SetTitleOffset( 1.0 );
  xAxis->SetLimits(450, 920);                                                                                                              

  yAxis = gr->GetYaxis();
  yAxis->SetTitle("Lifetime error");
  yAxis->CenterTitle( kTRUE );
  yAxis->SetTitleOffset( 1.5 );
  gr->SetMaximum(6e-3);                                                             
                                                      
  gr->SetMinimum(1e-4);          
  
  gr->Draw("APL");
  canvas->Print("lifetime_summaryplot_450_1200.png");
  canvas->Close();

}
