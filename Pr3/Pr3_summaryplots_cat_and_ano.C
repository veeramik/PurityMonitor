void Pr3_summaryplots_cat_and_ano(){

  TCanvas *canvas = new TCanvas("canvas");
  TChain *chain = new TChain("Tree");
  TChain *chain2 = new TChain("Tree");
  //TChain *timechain = new TChain("Timetree");

  double x[360], t_3[360], t_2[360], Q_a[360];
  double x_2[360], t_1[360], Q_k[360];
  double time_min[500], time_hours[500], tot_time[500];
  int k=0;
  //int p=0;

  for (int l=0; l<24; l++){

    for (int s=0; s<60; s++){

      for (int j=0; j<10; j++){
	Bool_t f = gSystem->AccessPathName(Form("gold/gold_average_%d.%d_fitvalues%d_PreAmpFunc_first24_gas_ar_anode.root", l, s, j));
	if (f){
	  continue;
	}
	else{
	  
	  chain->Add(Form("gold/gold_average_%d.%d_fitvalues%d_PreAmpFunc_first24_gas_ar_anode.root", l, s, j));
	  //chain->Add(Form("gold/golden_average_%d.%d_fitvalues%d_PreAmpFunc_first24_gas_ar.root", l, s, j));
	  double Q, t3, t23;
	  double Qk, t1;
	  int status;
	  
	  //chain->SetBranchAddress("Q", &Qk);
	  chain->SetBranchAddress("Q", &Q);
	  chain->SetBranchAddress("t3", &t3);
	  chain->SetBranchAddress("t23", &t23);
	  chain->SetBranchAddress("status", &status);
	  auto entries = chain->GetEntries();
	  for (int i=0; i<entries; i++){
	    chain->GetEntry(i);
	    if (status != 0){
	      l+=1;
	      cout << l << endl;
	      //cout << "fail" << " " << i << endl;
	      continue;
	    }
	    else {
	      //cout << k << endl;                                                                            
	      //cout << status << " " << k << endl;                                                           
	      Q_a[k] = Q;
	      t_2[k] = t23+t3;
	      t_3[k] = t3;
	      //t_1[k] = t1;                                                                                  
	      //Q_k[k] = Qk;                                                                                   
	      x[k]=l+s*0.01;
	      
	    }

	  }
	  
	  //cout <<  t_2[k] << " "<< t_3[k] << " " << endl;
	  k+=1;

	}

      }

     }

  }



  int k1=0;

  for (int d=0; d<24; d++){

    for (int e=0; e<60; e++){

      for (int h=0; h<10; h++){
        //cout << l << " " << s << " " << j << endl;                                                                                                       
        Bool_t f = gSystem->AccessPathName(Form("gold/golden_average_%d.%d_fitvalues%d_PreAmpFunc_first24_gas_ar.root", d, e, h));
        if (f){
          //cout << "no file" << endl;                                                                                              
          continue;
        }
        else{
          chain2->Add(Form("gold/golden_average_%d.%d_fitvalues%d_PreAmpFunc_first24_gas_ar.root", d, e, h));               
          double Qk, t1;
          int status2;
          chain2->SetBranchAddress("Q", &Qk);
          chain2->SetBranchAddress("t1", &t1);                                                                              
          chain2->SetBranchAddress("status", &status2);

          auto entries = chain2->GetEntries();

          for (int n=0; n<entries; n++){
            chain2->GetEntry(n);
            if (status2 != 0){
	      l+=1;
	      //cout << l << endl;
	      //cout << "fail" << " " << n << endl;
              continue;
            }
            else {
              //cout << t1 << endl;                                                                                                                                  
              //cout << status << " " << k << endl;                                                                                                                 
               t_1[k1] = t1;                                                                                                                                        
              Q_k[k1] = Qk;                                                                                                                                        
              x_2[k1]=d+e*0.01;

            }

          }
	  //cout << k1 << endl;
	  //cout << t_1[k1] << endl;
          k1+=1;

        }

      }

    }

  }

  int k2=0;
  for (int a=0; a<24; a++){

   for (int b=0; b<60; b++){
     Bool_t f2 = gSystem->AccessPathName(Form("gold/times/gold_average_%d.%d_fitvalues0_PreAmpFunc_first24_gas_ar_anode_times.root", a, b));
     if (f2){
       continue;
     }
     else{
     double min, hours;
     cout << a << " " << b << endl;
     TFile *f3 = new TFile(Form("gold/times/gold_average_%d.%d_fitvalues0_PreAmpFunc_first24_gas_ar_anode_times.root", a, b), "read");
     TTree *timechain = (TTree*)f3->("Timetree");
     //timechain->Add(Form("gold/times/gold_average_%d.%d_fitvalues0_PreAmpFunc_first24_gas_ar_anode_times.root", a, b));
     timechain->SetBranchAddress("hours", &hours);
     timechain->SetBranchAddress("min", &min);
     auto entries2 = timechain->GetEntries();
     //auto  entries2 = 9;
     for (int v=0; v<entries2; v++){
     timechain->GetEntry(v);
     time_min[k2] = min;
     time_hours[k2] = hours;
     //cout << time_hours[k2] << " " << time_min[k2] << " " << k2 << endl;
     if ((hours+16)<25){
       tot_time[k2] = (hours+16)+0.01*min;
       cout << tot_time[k2] << " " << k2 << endl;
       k2+=1;         
     }
     else{
       tot_time[k2] = (hours-9)+0.01*min;
       cout << tot_time[k2] << " " << k2 << endl;
       k2+=1;  
     } 
     

     }
     
    
     }
          
    }
     
  }
  

  double d1=0.01823;
  double d2=0.16424;
  double d3=0.00958;
  double vdrift_1[360], vdrift_2[360], vdrift_3[360];
  for (int w=0; w<361; w++){
    if (t_1[w] == 0 || t_2[w] == 0 || t_3[w] == 0){
      continue;}
    else{
    vdrift_1[w] = d1/t_1[w];
    vdrift_2[w] = d2/t_2[w];
    vdrift_3[w] = d3/t_3[w];
    //cout << vdrift_2[w]  << " " << tot_time[w] <<endl;
    //cout << vdrift_1[w] << " " << vdrift_2[w] << " " << vdrift_3[w] << endl;
  }
    //cout << w << endl;
  }

  int n = 360;
  TGraph* gr = new TGraph(n, tot_time, vdrift_2);
  gr->Draw();
  gr->SetTitle("V_drift evolution over 24 hrs");
  gr->SetMarkerColor(2);
  gr->SetMarkerStyle(21);
  gr->SetMarkerSize(0.8);
  xAxis = gr->GetXaxis();
  xAxis->SetTitle("time, 27.2.2020");
  xAxis->CenterTitle( kTRUE );
  xAxis->SetTitleOffset( 1.0 );
  //xAxis->SetLimits(0, 24.1);
  //xAxis->SetTimeFormat("%H");
  xAxis->SetTimeDisplay(1);
  //xAxis->SetTimeFormat("%H:%M");
  //xAxis->SetTimeOffset(0, "GMT");

  yAxis = gr->GetYaxis();
  yAxis->SetTitle("V_drift (m/s)");
  yAxis->CenterTitle( kTRUE );
  yAxis->SetTitleOffset( 1.5 );
  //gr->SetMaximum(3500);                                                                                

  //gr->SetMinimum(2500);                                                                                

  gr->Draw();
  //gr->Draw("APL");                                                                                     
  canvas->Print("vdrift_vs_time_gas_ar_first24.png");
  canvas->Close();

}

