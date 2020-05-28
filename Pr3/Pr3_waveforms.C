void Pr3_waveforms() {

  TCanvas *canvas = new TCanvas("canvas");
  

      Bool_t f = gSystem->AccessPathName("/unix/dune/purity/abf/vacuum_10.03.2020/diamond/30.60.120Vcm.ch4.traces.root");

      if (f){
        continue;
      }

      else{
	TFile *f3 = new TFile("/unix/dune/purity/abf/vacuum_10.03.2020/diamond/30.60.120Vcm.ch4.traces.root"), "read");
      for (int i=1; i<1001; i++) {
          TCanvas *canvas = new TCanvas("canvas");
          TGraph *ano_raw = (TGraph*)f3->Get(Form("graph%d", i));
          double error[500], x[500]={0}, y[500]={0};
	  for (int s=0; s<500; s++) {
	    error[s] = TMath::Sqrt(ano_raw->GetRMS());
            for (int r=s*200; r<(s+1)*200; r++) {
              x[s] += ano_raw->GetX()[r];
              y[s] += ano_raw->GetY()[r];
            }
            x[s]/=200;
            y[s]/=200;
           }

	  //for (int j=0; j<1000; j++){
	  //if(y[j]>0){
	  //  y[j] = 0;
	  //  }
	    //cout << y[j] << endl;
	  // }

          TGraphErrors *ano = new TGraphErrors(500, x, y, 0, error);
          ano->Draw();
	  canvas->Print(Form("diamond/vacuum/waveforms/vacuum_10.3_waveform%d_200.pdf", i), "recreate");
	  
	  //double max TMath::MaxElement(n,ano->GetY());
	  //double max = ano->->GetHistogram()->GetMinimum(); 
	  //double max = ano->GetYaxis()->GetXMax();
	  //yAxis = ano->GetYaxis();	 
	  //double max = yAxis->GetXmax();
	  //double min = yAxis->GetXmin();
	  double min = TMath::MinElement(ano->GetN(),ano->GetY());
	  double max = TMath::MaxElement(ano->GetN(),ano->GetY());
	  cout << max << " "  << min << endl;
	  cout << max-min << endl;
	  TFile *file = new TFile(Form("diamond/vacuum/waveforms/vacuum_10.3_waveform%d_200.root", i), "recreate");
	  TTree *tree = new TTree("Tree", "Tree");
	  tree->Branch("max", &max);
	  tree->Branch("min", &min);
          tree->Fill();
          file->Write();
          file->Close();

	}
      }
}
