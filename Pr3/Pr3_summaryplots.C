void Pr3_summaryplots(){

  TCanvas *canvas = new TCanvas("canvas");
  TChain *chain = new TChain("Tree");
  

  //double x[387], t_3[387], t_2[387], Q_a[387]; 
   double x[387], t_1[387], Q_k[387];
  int k=0;
  int p=0;

for (int l=0; l<24; l++){
 
  for (int s=0; s<60; s++){

    for (int j=0; j<10; j++){
  //cout << l << " " << s << " " << j << endl;
      Bool_t f = gSystem->AccessPathName(Form("gold/golden_average_%d.%d_fitvalues%d_PreAmpFunc_first24_gas_ar.root", l, s, j));
      if (f){
    //cout << "no file" << endl;
	continue;
      }
      else{
    //cout << l << " " << s << endl;                                                                        
    chain->Add(Form("gold/golden_average_%d.%d_fitvalues%d_PreAmpFunc_first24_gas_ar.root", l, s, j));
    
    //double Q, t3, t23;
    double Q, t1;
  int status;
  chain->SetBranchAddress("Q", &Q);
  //chain->SetBranchAddress("t3", &t3);
  //chain->SetBranchAddress("t23", &t23);
  chain->SetBranchAddress("t1", &t1);
  chain->SetBranchAddress("status", &status);
    
   auto entries = chain->GetEntries();
 
  for (int i=0; i<entries; i++){
     chain->GetEntry(i);
     if (status != 0){
       //cout << k << endl;
       //cout << status << " " << k << endl;
     continue;
     }
     else {
       //cout << k << endl;
       //cout << status << " " << k << endl;
       //Q_a[k] = Q;
       //t_2[k] = t23+t3;
       //t_3[k] = t3;
       t_1[k] = t1;
       Q_k[k] = Q;
       x[k]=l+s*0.01;

     }
 
   }
 
  //x[k]=l+s*0.01;
  //cout << x[k] << " " << t_2[k] << endl;
  k+=1;
  
 }

 }

 }

}

 cout << k << endl;
 //cout << q << " " << p <<  endl;


int n = 387;
TGraph* gr = new TGraph(n, x, t_1);
gr->SetTitle("t1 evolution over 24 hrs");
gr->SetMarkerColor(2);
gr->SetMarkerStyle(21);
gr->SetMarkerSize(0.8);

xAxis = gr->GetXaxis();
xAxis->SetTitle("time (hr.min)");
xAxis->CenterTitle( kTRUE );
xAxis->SetTitleOffset( 1.0 );
xAxis->SetLimits(0, 24.1);	       
                                                                                                

yAxis = gr->GetYaxis();
yAxis->SetTitle("t1 (s)");
yAxis->CenterTitle( kTRUE );
yAxis->SetTitleOffset( 1.5 );
//gr->SetMaximum(2e-5);

//gr->SetMinimum(1e-5);

gr->Draw();
//gr->Draw("APL");
//canvas->Print("t3_vs_time_gas_ar_first_third24.png");
canvas->Close();

}
