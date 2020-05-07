void Pr3_summaryplots(){

  TCanvas *canvas = new TCanvas("canvas");
  TChain *chain = new TChain("Tree");
  
  double x[1000], tpeak_tot[1000], tstart_tot[1000], Q_a[1000];
  //double x[1000], t_3[1000], t_2[1000], Q_a[1000]; 
  //double x[1000], t_1[1000], Q_k[1000];
  double ex[1000], ey[1000];
  int k=0;
  int p=0;

for (int l=0; l<1; l++){
 
  for (int s=0; s<1; s++){

    for (int j=0; j<1001; j++){
      Bool_t f = gSystem->AccessPathName(Form("silver/vacuum/vacuum_10.3_fitvalues%d_stefano.root", j)); 
  //cout << l << " " << s << " " << j << endl;
      //Bool_t f = gSystem->AccessPathName(Form("gold/gold_%d.%d_fitvalues%d_testafter71_gas_ar.root", l, s, j));
      if (f){

	continue;
      }
      else{
	cout << j << endl;
	chain->Add(Form("silver/vacuum/vacuum_10.3_fitvalues%d_stefano.root", j));
    
	//double Q, t3, t23;
	//double Q, t1;
	int status;
	double Q, tpeak, tstart;

	//chain->SetBranchAddress("Q", &Q);
	//chain->SetBranchAddress("t3", &t3);
	//chain->SetBranchAddress("t23", &t23);
	//chain->SetBranchAddress("t1", &t1);
	chain->SetBranchAddress("status", &status);
	chain->SetBranchAddress("Q", &Q);
	chain->SetBranchAddress("tpeak", &tpeak);
	chain->SetBranchAddress("tstart", &tstart);

	auto entries = chain->GetEntries();
 
  for (int i=0; i<entries; i++){
     chain->GetEntry(i);
     if (status != 0 || Q>1){
       //cout << k << endl;
       //cout << status << " " << k << endl;
     continue;
     }
     else {
       //cout << k << endl;
       //cout << status << " " << k << endl;
       Q_a[k] = Q;
       //t_2[k] = t23+t3;
       //t_3[k] = t3;
       tpeak_tot[k] = tpeak;
       tstart_tot[k] = tstart;
       ex[k] = 0;
       ey[k] = 0.0;
       //t_1[k] = t1;
       //Q_k[k] = Q;
       x[k] = j;
       //cout << i << endl;
       //x[k]=l+s*0.01;

     }
 
   }
 
  //x[k]=l+s*0.01;
  cout << x[k] << " " << Q_a[k] << endl;
  k+=1;
  
 }

 }

 }

}

//cout << k << endl;
 //cout << q << " " << p <<  endl;


int n = 1000;
TGraph* gr = new TGraphErrors(n, x, Q_a, ex, ey);
gr->SetTitle("Qa");
gr->SetMarkerColor(2);
gr->SetMarkerStyle(21);
gr->SetMarkerSize(0.8);

xAxis = gr->GetXaxis();
//xAxis->SetTitle("time (hr.min)");
xAxis->CenterTitle( kTRUE );
xAxis->SetTitleOffset( 1.0 );
xAxis->SetLimits(0, 1001);	       
                                                                                                

yAxis = gr->GetYaxis();
yAxis->SetTitle("Qa (V)");
yAxis->CenterTitle( kTRUE );
yAxis->SetTitleOffset( 1.5 );
//gr->SetMaximum(-2.8);

//gr->SetMinimum(-4);

//gr->Draw();
gr->Draw("APL");
canvas->Print("Qa_silver_vacuum_10.3_stefano_noerror.png");
canvas->Close();

}
