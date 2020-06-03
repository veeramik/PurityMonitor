void Pr3_waveforms_ft() {

  TCanvas *canvas = new TCanvas("canvas");

  Bool_t f = gSystem->AccessPathName("/unix/dune/purity/abf/vacuum_10.03.2020/silver/30.60.120Vcm.ch4.traces.root");

  if (f){
    continue;
  }

  else{
    TFile *f3 = new TFile("/unix/dune/purity/abf/vacuum_10.03.2020/silver/30.60.120Vcm.ch4.traces.root"), "read");
  for (int i=1; i<1001; i++) {
    TCanvas *canvas = new TCanvas("canvas");
    TGraph *ano_raw = (TGraph*)f3->Get(Form("graph%d", i));
    double error[1000], x[1000], y[1000];
    for (int s=0; s<1000; s++) {
      error[s] = TMath::Sqrt(ano_raw->GetRMS());
       x[s] = ano_raw->GetX()*TMath::Exp(-2*(TMath::Pi)/(s+1));
       y[s] = ano_raw->GetY()*TMath::Exp(-2*(TMath::Pi)/(s+1));
      cout << x[s] << endl;
     
    }
  

    TGraphErrors *ano = new TGraphErrors(1000, x, y, 0, error);

    //canvas->Print(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_100_max0.pdf", i), "recreate");

    double min = TMath::MinElement(ano->GetN(),ano->GetY());
    double max = TMath::MaxElement(ano->GetN(),ano->GetY());
    cout << max << " "  << min << endl;
    cout << max-min << endl;
    //TFile *file = new TFile(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_100_max0.root", i), "recreate");
    //TTree *tree = new TTree("Tree", "Tree");
    //tree->Branch("max", &max);
    // tree->Branch("min", &min);
    //tree->Fill();
    //file->Write();
    //file->Close();

  }
}
}
