void waveforms() {

  TCanvas *canvas = new TCanvas("canvas");
 
  TFile *f = new TFile("/unix/dune/purity/np02/Filling/Run1252/PrM1_lifeInfo.root", "read");                                                                                                                         
        TCanvas *canvas = new TCanvas("canvas");
        TGraph *ano_raw = (TGraph*)f->Get("gfin_ch2");
	TGraph *cat_raw = (TGraph*)f->Get("gfin_ch1");
	TGraph *sum = (TGraph*)f->Get("gsum");

	double RMSa;
	TTree *metatree =(TTree*)f->Get("metaTree");
	metatree->SetBranchAddress("rawVoltageRMSa", &RMSa);
	metatree->GetEntry(0);

	double error[152], x[152]={0}, y[152]={0};
	for (int s=0; s<152; s++) {
	  //error[s] = 0;
	  //error[s] = TMath::Sqrt(RMSa*0.001);
	  //cout << error[s] << endl;                                                                                               
	  for (int r=s*100; r<(s+1)*100; r++) {
	    x[s] += gsum->GetX()[r];
	    y[s] += gsum->GetY()[r];
	  }
	  x[s]/=100;
	  y[s]/=100;
	}

	TGraph *wave = new TGraphErrors(152, x, y, 0, error);
	//TGraph *wave = new TGraph(ano_raw->GetN(), ano_raw->GetX(), ano_raw->GetY());
	wave->SetLineColor(1);
	wave->SetTitle("Anode Data");
	wave->GetXaxis()->SetTitle("Time (s)");
	wave->GetXaxis()->SetTitleOffset(1.2);
	wave->GetYaxis()->SetTitle("Amplitude (mV)");
	wave->GetYaxis()->SetTitleOffset( 1.2 );
	wave->Draw();
	canvas->Print("Run1252_sum_PrM1.png");

	double y_1[152];
	int k=0;
	for(int i=0; i<152; i++){
	  cout << y[i] << endl;
	  //cout << y[i] << " " << x[i] << " " << i << endl;
	  if (x[i]>0.0002){
	    y_1[k] = y[i];
	    //cout <<  y_1[k] << " " << k << endl;
	    k+=1;
	  }
       	}
	
	//double min = TMath::MinElement(wave->GetN(), y_1);
	//double max = TMath::MaxElement(wave->GetN(), y_1);  
	double min = TMath::MinElement(wave->GetN(), wave->GetY());
        double max = TMath::MaxElement(wave->GetN(), wave->GetY());
        cout << max << " "  << min << endl;
        cout << max-min << endl;

}
