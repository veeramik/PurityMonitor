void Pr3_summaryplots_waveforms_slopes(){

  TCanvas *canvas = new TCanvas("canvas");
  TChain *chain = new TChain("Tree");
  TChain *chain2 = new TChain("Tree");
  TChain *chain3 = new TChain("Tree");

  double Q_k_200[1000], Q_k_500[1000], Q_k_100[1000], x_200[1000], x_500[1000], x_100[1000];

  int k1=0;
  for (int h=0; h<1001; h++){
    Bool_t f1 = gSystem->AccessPathName(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_200.root", h));
    if (f1){
      continue;
    }
    else{
      chain->Add(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_200.root", h));
      double max_cat, min_cat;
      chain->SetBranchAddress("max", &max_cat);
      chain->SetBranchAddress("min", &min_cat);
      auto entries = chain->GetEntries();
      for (int p=0; p<entries; p++){
	chain->GetEntry(p);
	Q_k_200[k1] = max_cat-min_cat;
	x_200[k1] = h;
      }
      k1+=1;
    }
  }

  int k2=0;
  for (int j=0; j<1001; j++){
    Bool_t f2 = gSystem->AccessPathName(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_500.root", j));
    if (f2){
      continue;
    }
    else{
      chain2->Add(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_500.root", j));
      double max, min;
      chain2->SetBranchAddress("max", &max);
      chain2->SetBranchAddress("min", &min);
      auto entries2 = chain2->GetEntries();
      for (int i=0; i<entries2; i++){
	chain2->GetEntry(i);
	Q_k_500[k2] = max-min;
	x_500[k2] = j;
      }
     k2+=1;
    }
  }

  int k3=0;
  for (int d=0; d<1001; d++){
    Bool_t f3 = gSystem->AccessPathName(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_100.root", d));
    if (f3){
      continue;
    }
    else{
      chain3->Add(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_100.root", d));
      double max2, min2;
      chain3->SetBranchAddress("max", &max2);
      chain3->SetBranchAddress("min", &min2);
      auto entries3 = chain3->GetEntries();
      for (int g=0; g<entries3; g++){
        chain3->GetEntry(g);
        Q_k_100[k3] = max2-min2;
        x_100[k3] = d;
      }
      k3+=1;
    }
  }

  int n = 1000;
  TGraph* cat200 = new TGraph(n, x_200, Q_k_200);
  cat200->SetMarkerColor(1);
  cat200->SetMarkerStyle(21);
  cat200->SetMarkerSize(0.8);
  cat200->SetName("silver 200");
  cat200->SetTitle("silver 200");
  cat200->Draw("AP");
  cat200->Fit("pol1");
  double slope200 = cat200->GetFunction("pol1")->GetParameter(1);

  TGraph* cat500 = new TGraph(n, x_500, Q_k_500);
  cat500->SetMarkerColor(4);
  cat500->SetMarkerStyle(22);
  cat500->SetMarkerSize(0.8);
  cat500->SetName("silver 500");
  cat500->SetTitle("silver 500");
  cat500->Draw("AP");
  cat500->Fit("pol1");
  double slope500 = cat500->GetFunction("pol1")->GetParameter(1);
  
  TGraph* cat100 = new TGraph(n, x_100, Q_k_100);
  cat100->SetMarkerColor(3);
  cat100->SetMarkerStyle(22);
  cat100->SetMarkerSize(0.8);
  cat100->SetName("silver 100");
  cat100->SetTitle("silver 100");
  cat100->Draw("AP");
  cat100->Fit("pol1");
  double slope100 = cat100->GetFunction("pol1")->GetParameter(1);

  cout << slope200 << " " << slope500 << " " << slope100 << endl;

  TMultiGraph* gr = new TMultiGraph("Q_k_200, Q_k_500, Q_k_100", "Q_k_200, Q_k_500 and Q_k_100 for silver");
  gr->Add(cat200);
  gr->Add(cat500);
  gr->Add(cat100)
  gr->Draw("AP");
  canvas->BuildLegend();
  canvas->Print("silver_vacuum_10.3_waveforms_slopes_200500100.png");
  canvas->Close();

}
