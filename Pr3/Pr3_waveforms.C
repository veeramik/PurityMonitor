void Pr3_waveforms() {

  TCanvas *canvas = new TCanvas("canvas");
  
      Bool_t f = gSystem->AccessPathName("/unix/dune/purity/abf/vacuum_10.03.2020/silver/30.60.120Vcm.ch4.traces.root");

      if (f){
        continue;
      }

      else{
      TFile *f3 = new TFile("/unix/dune/purity/abf/vacuum_10.03.2020/silver/30.60.120Vcm.ch4.traces.root"), "read");
      for (int i=5; i<6; i++) {
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
	    //cout << x[s] << endl;
           }

	  for (int j=5; j<6; j++) {
	  TCanvas *canvas = new TCanvas("canvas");
	  TGraph *ano_raw = (TGraph*)f3->Get(Form("graph%d", j));
	  double error_1[100002], x_1[100002]={0}, y_1[100002]={0};
	  //double CMA[100002];
	  for (int p=0; p<100002; p++) {
	    error_1[p] = TMath::Sqrt(ano_raw->GetRMS());
	    }

	  //auto entries= ano_raw->GetN();
	  //cout << entries << endl;
	  double CMA, CMA_y;
	 //CMA[0] = ano_raw->GetX()[0];
	  for (int t=1; t<100002; t++) {
	      CMA += ano_raw->GetX()[t];
	      x_1[t] = CMA/t;
	      CMA_y += ano_raw->GetY()[t];
              y_1[t] = CMA_y/t;
	      //cout << x_1[t] << " " << CMA << " " << t << endl;
	      //cout << ano_raw->GetX()[t] <<  " "  << CMA << " " << t << endl;
	      }
	  
	  }

          TGraphErrors *ano = new TGraphErrors(100002, x_1, y_1, 0, error_1);
	  //ano->GetXaxis()->SetLimits(-0.00001, 0.00005);
          //ano->SetMaximum(-3);
	  //ano->SetMinimum(-4.2);
	  ano->Draw();
	  canvas->Print(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_rollingaverage.png", j), "recreate");
	  
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
	  TFile *file = new TFile(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_rollingaverage.root", j), "recreate");
	  TTree *tree = new TTree("Tree", "Tree");
	  tree->Branch("max", &max);
	  tree->Branch("min", &min);
          tree->Fill();
          file->Write();
          file->Close();

	}
      }
}
