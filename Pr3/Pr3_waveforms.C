void Pr3_waveforms() {

  TCanvas *canvas = new TCanvas("canvas");
  
      Bool_t f = gSystem->AccessPathName("/unix/dune/purity/abf/vacuum_10.03.2020/silver/30.60.120Vcm.ch3.traces.root");

      if (f){
        continue;
      }

      else{
      TFile *f3 = new TFile("/unix/dune/purity/abf/vacuum_10.03.2020/silver/30.60.120Vcm.ch3.traces.root"), "read");
      //for (int i=2; i<3; i++) {
      //    TCanvas *canvas = new TCanvas("canvas");
      //    TGraph *ano_raw = (TGraph*)f3->Get(Form("graph%d", i));
      //    double error[500], x[500]={0}, y[500]={0};
      //  for (int s=0; s<500; s++) {
      //    error[s] = TMath::Sqrt(ano_raw->GetRMS());
      //    for (int r=s*200; r<(s+1)*200; r++) {
      //      x[s] += ano_raw->GetX()[r];
      //      y[s] += ano_raw->GetY()[r];
	      //cout << y[s] << " " << s << endl;
      //     }
      //    x[s]/=200;
      //    y[s]/=200;
	    //cout << y[s] << " " << s << endl;
      //   }

	  double x_1[1000], y_1[1000], error_1[1000];
	  for (int j=500; j<501; j++) {                                                                                                 
	  TCanvas *canvas = new TCanvas("canvas");                                                                                 
	  TGraph *ano_raw = (TGraph*)f3->Get(Form("graph%d", j));
	  for(int d=0; d<1000; d++){
	    //cout << d << endl;
	    error_1[d] = TMath::Sqrt(ano_raw->GetRMS());
	    if (d==0){
	      for (int e=d; e<100; e++){
		y_1[d] += ano_raw->GetY()[e];
		x_1[d] += ano_raw->GetX()[e];
		//cout << y_1[d] << " " << d << endl;
	    }
	      y_1[d]/=100;
	      x_1[d]/=100;
	      //cout << y_1[d] << " " << d << endl; 
	    }
	     else{
	      for (int e=(d*100-1); e<(d+1)*100; e++){<
		y_1[d] += ano_raw->GetY()[e];
		x_1[d] += ano_raw->GetX()[e];
		//cout << y_1[d] << " " << d << endl;
	    }	   
	      y_1[d]/=100;
	      x_1[d]/=100;
	      //cout << y_1[d] << " " << d << endl; 
	     }
	  }

	  
	  //for (int j=1; j<2; j++) {
	  //TCanvas *canvas = new TCanvas("canvas");
	  //TGraph *ano_raw = (TGraph*)f3->Get(Form("graph%d", j));
	  //double error_1[100002],  x_1[100002]={0}, y_1[100002]={0}; 
	  //double CMA, CMA_y;
	  //CMA[0] = ano_raw->GetX()[0];
	  //for (int t=1; t<100001; t++) {
	  //error_1[t] = TMath::Sqrt(ano_raw->GetRMS());
	  // CMA += ano_raw->GetX()[t];
	  //x_1[t] = CMA/t;
	  //CMA_y += ano_raw->GetY()[t];
	  //y_1[t] = CMA_y/t;
	 
	  //}
	  
	  //}

          TGraphErrors *ano = new TGraphErrors(1000, x_1, y_1, 0, error_1);
	  //ano->GetXaxis()->SetLimits(-0.00001, 0.00005);
          //ano->SetMaximum(-3);
	  //ano->SetMinimum(-4.2);
	  ano->Draw();
	  canvas->Print(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_rollingaverage_anode.png", j), "recreate");
	  
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
	  TFile *file = new TFile(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_rollingaverage_anode.root", j), "recreate");
	  TTree *tree = new TTree("Tree", "Tree");
	  tree->Branch("max", &max);
	  tree->Branch("min", &min);
          tree->Fill();
          file->Write();
          file->Close();

	}
      }
}
