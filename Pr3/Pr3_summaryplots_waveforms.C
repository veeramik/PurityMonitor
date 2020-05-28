void Pr3_summaryplots_waveforms(){

  TCanvas *canvas = new TCanvas("canvas");
  TChain *chain = new TChain("Tree");
  TChain *chain2 = new TChain("Tree");

  double Q_k[1000], Q_a[1000], x[1000], x1[1000];
  int k=0;

   for (int j=0; j<1001; j++){

    Bool_t f = gSystem->AccessPathName(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_500.root", j));
     if (f){
      continue;
      }
      else{
	chain->Add(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_500.root", j));
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
     Bool_t f1 = gSystem->AccessPathName(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_500_anode.root", h));
     if (f1){
      continue;
     }
     else{
       chain2->Add(Form("silver/vacuum/waveforms/vacuum_10.3_waveform%d_500_anode.root", h));
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
       //cout << Q_a[k1]-Q_k[k1] << " " << h << endl;
       k1+=1;
     }
   }
   
   //for (int p=0, p<1001; p++){
   //  cout << Q_k[p]-Q_a[p] << " " << p << endl;  
   // }



   int n = 1000;
   TGraph* cat = new TGraph(n, x, Q_k);
   cat->SetMarkerColor(2);                                                                                   
   cat->SetMarkerStyle(21);
   cat->SetMarkerSize(0.8);
   cat->SetName("cathode");
   cat->SetTitle("cathode"); 
   cat->Draw("AP");
   cat->Fit("pol1");
   double slope_cat = cat->GetFunction("pol1")->GetParameter(1);

   TGraph* ano = new TGraph(n, x1, Q_a);
   ano->SetMarkerColor(4);
   ano->SetMarkerStyle(22);
   ano->SetMarkerSize(0.8);
   ano->SetName("anode");
   ano->SetTitle("anode"); 
   ano->Draw("AP");
   ano->Fit("pol1");
   double slope_ano = ano->GetFunction("pol1")->GetParameter(1);
 
   cout << slope_cat << " " << slope_ano << endl;

   TMultiGraph* gr = new TMultiGraph("Q_k and Q_a", "Q_k and Q_a for silver");
   gr->Add(cat);
   gr->Add(ano);

   gr->Draw("AP");
   canvas->BuildLegend();
   canvas->Print("silver_vacuum_10.3_waveforms_500averaging.png");
   canvas->Close();

}
