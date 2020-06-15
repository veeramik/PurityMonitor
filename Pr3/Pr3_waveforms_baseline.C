void Pr3_waveforms_baseline() {

  TCanvas *canvas = new TCanvas("canvas");
  TFile *f3 = new TFile("/unix/dune/purity/abf/vacuum_10.03.2020/silver/30.60.120Vcm.ch3.traces.root", "read");

  double error_1[666], x_1[666], y_1[666];
  for (int j=1; j<2; j++) {
    TCanvas *canvas = new TCanvas("canvas");                                                              
    TGraph *ano_raw = (TGraph*)f3->Get(Form("graph%d", j));
    for(int d=0; d<666; d++){
      error_1[d] = 0;
      //error_1[d] = TMath::Sqrt(ano_raw->GetRMS());
      if (d==0){
	for (int e=d; e<150; e++){
	  y_1[d] += ano_raw->GetY()[e];
	  x_1[d] += ano_raw->GetX()[e];
	}
	y_1[d]/=150;
	x_1[d]/=150;
      }
      else{
	for (int e=(d*150-1); e<(d+1)*150; e++){
	  y_1[d] += ano_raw->GetY()[e];
	  x_1[d] += ano_raw->GetX()[e];
	}
	y_1[d]/=150;
	x_1[d]/=150;
      }
  }

    double x_roll[50], y_roll[50];
    for(int g=0; g<666; g++){
      if (x_1[g]<=0){
	x_roll[g] = x_1[g];
	y_roll[g] = y_1[g];
	//cout << y_1[g] << " " << g << endl;
      }
    }

    double  x_2[200], y_2[200];
    for(int h=0; h<200; h++){
      if (h==0){
        for (int m=h; m<500; m++){
          y_2[h] += ano_raw->GetY()[m];
          x_2[h] += ano_raw->GetX()[m];
        }
        y_2[h]/=500;
        x_2[h]/=500;
      }
      else{
        for (int m=(h*500-1); m<(h+1)*500; m++){
          y_2[h] += ano_raw->GetY()[m];
          x_2[h] += ano_raw->GetX()[m];
        }
        y_2[h]/=500;
        x_2[h]/=500;
      }
    }

    double x_roll2[14], y_roll2[14];
    for(int n=0; n<200; n++){
      if (x_2[n]<=0){
        x_roll2[n] = x_2[n];
        y_roll2[n] = y_2[n];
        //cout << y_2[n] << " " << n << endl;                                                                                                         
      }
    }

    double  x_3[10000], y_3[10000];
    for(int o=0; o<10000; o++){
      if (o==0){
        for (int p=o; o<10; o++){
          y_3[o] += ano_raw->GetY()[o];
          x_3[o] += ano_raw->GetX()[o];
        }
        y_3[o]/=10;
        x_3[o]/=10;
      }
      else{
        for (int p=(o*10-1); p<(o+1)*10; p++){
          y_3[o] += ano_raw->GetY()[p];
          x_3[o] += ano_raw->GetX()[p];
        }
        y_3[o]/=10;
        x_3[o]/=10;
      }
    }

    double x_roll3[759], y_roll3[759];
    for(int q=0; q<10000; q++){
      if (x_3[q]<=0){
        x_roll3[q] = x_3[q];
        y_roll3[q] = y_3[q];
        //cout << y_3[q] << " " << q << endl;
      }
    }

    double error[666], x[666]={0}, y[666]={0};                                                                       
    for (int s=0; s<666; s++) {                                                                                        
      error[s] = TMath::Sqrt(ano_raw->GetRMS());                                                                      
      for (int r=s*150; r<(s+1)*150; r++) {                                                                            
        x[s] += ano_raw->GetX()[r];                                                                                    
        y[s] += ano_raw->GetY()[r];                                                                                    
          }                                                                                                               
      x[s]/=150;                                                                                                       
      y[s]/=150;                                                                                                       
        }            

    double x_box[50], y_box[50];
    for(int i=0; i<666; i++){
      if(x[i]<=0){
	x_box[i] = x[i];
	y_box[i] = y[i];
        //cout << y[i] << " " << i << endl;
      }
    }

     double x_raw[7600], y_raw[7600]; 
    for(int k=0; k<100002; k++){
      //cout << ano_raw->GetX()[k]<< endl;
      if(ano_raw->GetX()[k]<=0){
        x_raw[k] = ano_raw->GetX()[k];
        y_raw[k] = ano_raw->GetY()[k];
	//cout << ano_raw->GetY()[k] << " " << k << endl;
        }
    }

    TGraph *ano_roll = new TGraph(50, x_roll, y_roll);
    ano_roll->SetLineColor(2);
    ano_roll->SetLineWidth(3);
    ano_roll->SetName("Rolling average 150");
    ano_roll->SetTitle("Rolling average 150");
    //ano_roll->Draw();

    TGraph *ano_box = new TGraph(50, x_roll, y_roll);
    ano_box->SetLineColor(6);
    ano_box->SetLineWidth(3);
    ano_box->SetName("Boxcar average");
    ano_box->SetTitle("Boxcar average");
    //ano_box->Draw();

    TGraph *ano_raw1 = new TGraph(7600, x_raw, y_raw);
    ano_raw1->SetLineColor(33);
    ano_raw1->SetLineWidth(0.1);
    ano_raw1->SetName("Raw");
    ano_raw1->SetTitle("Raw");
    //ano_raw1->Draw();    

    TGraph *ano_roll2 = new TGraph(14, x_roll2, y_roll2);
    ano_roll2->SetLineColor(7);
    ano_roll2->SetLineWidth(3);
    ano_roll2->SetName("Rolling average 500");
    ano_roll2->SetTitle("Rolling average 500");
    //ano_roll->Draw();   

    TGraph *ano_roll3 = new TGraph(759, x_roll3, y_roll3);
    ano_roll3->SetLineColor(3);
    ano_roll3->SetLineWidth(3);
    ano_roll3->SetName("Rolling average 10");
    ano_roll3->SetTitle("Rolling average 10");
    //ano_roll->Draw();     
    
    TMultiGraph* gr = new TMultiGraph("Baseline for different averaging", "Baseline for different averaging");
    gr->Add(ano_raw1);
    gr->Add(ano_roll);
    gr->Add(ano_roll2);
    gr->Add(ano_roll3);
    gr->Add(ano_box);

    gr->SetMinimum(-40e-6);
    gr->SetMaximum(-30e-6);

    gr->Draw("APL");
    canvas->BuildLegend();
    //canvas->Print(Form("silver_vacuum_10.3_waveform%d_baseline.png", j));
    //canvas->Close();

    //canvas->Print(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_baseline.png", j));
    
  }

}

