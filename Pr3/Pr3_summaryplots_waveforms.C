void Pr3_summaryplots_waveforms(){

  TCanvas *canvas = new TCanvas("canvas");
  TChain *chain = new TChain("Tree");
  TChain *chain2 = new TChain("Tree");

  double Q_k[1000], Q_a[1000], x[1000], x1[1000];
  int k=0;

   for (int j=0; j<1001; j++){

    Bool_t f = gSystem->AccessPathName(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_cathode.root", j));
     if (f){
      continue;
      }
      else{
	chain->Add(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_cathode.root", j));
	double max, min, status;
	chain->SetBranchAddress("max", &max);
	chain->SetBranchAddress("min", &min);
	auto entries = chain->GetEntries();
	for (int i=0; i<entries; i++){
	  chain->GetEntry(i);
	    Q_k[k] = max-min;
	    x[k] = j;
	
	}
	//cout << Q_k[k] << " " << j << endl;
	k+=1;
      }
   }


   int k1=0;
   for (int h=0; h<1001; h++){
     Bool_t f1 = gSystem->AccessPathName(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d.root", h));
     if (f1){
      continue;
     }
     else{
       chain2->Add(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d.root", h));
       double max_cat, min_cat;
       chain2->SetBranchAddress("max", &max_cat);
       chain2->SetBranchAddress("min", &min_cat);
       auto entries2 = chain2->GetEntries();
       for (int p=0; p<entries2; p++){
	 chain2->GetEntry(p);
	 //cout << max_cat << endl;
	 Q_a[k1] = max_cat-min_cat;
	 x1[k1] = h;
       }
       //cout << Q_a[k1] << " " << h << endl;
       k1+=1;
     }
   }


   int n = 1000;
   TGraph* cat = new TGraph(n, x, Q_k);
   cat->SetMarkerColor(2);                                                                                                        
   cat->SetMarkerStyle(21);                                                                                                      
   cat->SetMarkerSize(0.8);
   cat->SetName("cathode");
   cat->SetTitle("cathode"); 
   TGraph* ano = new TGraph(n, x1, Q_a);
   ano->SetMarkerColor(4);
   ano->SetMarkerStyle(22);
   ano->SetMarkerSize(0.8);
   ano->SetName("anode");
   ano->SetTitle("anode");
   TMultiGraph* gr = new TMultiGraph("Q_k and Q_a", "Q_k and Q_a for silver");
   gr->Add(cat);
   gr->Add(ano);
   //gr->SetTitle("Reduced chi2 for cathode");
   //gr->SetMarkerColor(2);
   //gr->SetMarkerStyle(21);
   //gr->SetMarkerSize(0.8);

   //xAxis = gr->GetXaxis();
   //xAxis->SetTitle("time (hr.min)");                                                                                            
   //xAxis->CenterTitle( kTRUE );
   //xAxis->SetTitleOffset( 1.0 );
   //xAxis->SetLimits(0, 1001);


   //yAxis = gr->GetYaxis();
   //yAxis->SetTitle("Voltage");
   //yAxis->CenterTitle( kTRUE );
   //yAxis->SetTitleOffset( 1.5 );

   //gr->SetMaximum(-2.5);                                                                                                        
   //gr->SetMinimum(-4);

   //ano->Draw("ALP");
                                                                                             
   gr->Draw("AP");
   canvas->BuildLegend();
   canvas->Print("silver_vacuum_10.3_waveforms.png");
   canvas->Close();

}
