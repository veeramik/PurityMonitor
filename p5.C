Double_t p5_polynomial(double x), argonMobilityFunc(Double_t *x, Double_t *par), argonDriftVelocity(Double_t E);

void p5(){
  int k=0;
  double E_1[158], E_2[158], E_3[158], run_number[158];
  double QK[158], QA[158], lifetime[158];
  double t1[158], t2[158], t3[158], t[158], v_drift1[158], v_drift2[158], v_drift3[158];
  double d1=18.23;
  double d2=164.24;
  double d3=9.85;
  TChain *chain = new TChain("metaTree");
  TChain *chain2 = new TChain("lifeTree");
  //TCanvas *canvas = new TCanvas("canvas"); 

  for (int j=1100; j<1200; j++) {
  Bool_t fi = gSystem->AccessPathName(Form("/unix/dune/purity/np02/Filling/Run%d/PrM1_lifeInfo.root", j));
  if(fi){
    continue;
  }
  else {
   chain->Add(Form("/unix/dune/purity/np02/Filling/Run%d/PrM1_lifeInfo.root", j));
   chain2->Add(Form("/unix/dune/purity/np02/Filling/Run%d/PrM1_lifeInfo.root", j));
   double fields[3];
   chain->SetBranchAddress("fields[3]", &fields);
    int entries = chain->GetEntries();                                                                               
   for (int i=0; i<entries; i++){                                                                                     
     chain->GetEntry(i);
     //cout << fields[0] << endl;
     if (fields[0] == 50){
       //E_1[k] = fields[0];
       //E_2[k] = fields[1];
       //E_3[k] = fields[2];
       E_1[k] = 90;
       E_2[k] = 90;
       E_3[k] = 275;
   }

   if (fields[0] == 60){
    E_1[k] = 109;
    E_2[k] = 109;
    E_3[k] = 331;
  }
   cout << E_1[k] << " " << E_2[k] << " " << E_3[k] << endl; 
     v_drift1[k] = argonDriftVelocity(E_1[k]);
     v_drift2[k] = argonDriftVelocity(E_2[k]);
     v_drift3[k] = argonDriftVelocity(E_3[k]);
     //cout << v_drift1[k] << " " << v_drift2[k] << " " << v_drift3[k] << endl;
     t1[k] = d1*0.1/v_drift1[k]*10e-6;
     t2[k] = d2*0.1/v_drift2[k]*10e-6;
     t3[k] = d3*0.1/v_drift3[k]*10e-6;
     cout << t1[k] << " " << t2[k] << " " << t3[k] << endl;
     t[k] = t2[k]+(t1[k]+t3[k])/2;
     run_number[k] = j;
     //cout << run_number[k] << endl;
     }
   
   //cout << t[k] << " " << run_number[k] << endl;
   TFile *file = new TFile(Form("theoryvalues_Pr1/theoryvalues%d.root", j), "recreate");
   TTree *tree = new TTree("Tree", "Tree");

  
   tree->Branch("t1",&t1[k]);
   tree->Branch("t2",&t2[k]);
   tree->Branch("t3",&t3[k]);
   tree->Branch("run_number", &run_number[k]);

   tree->Fill();
   file->Write();
   file->Close();

   //lifetime[k] = (1/TMath::Log(-QA/QK))*t[k];
   //cout << lifetime[k] << endl;
   //cout << QK[k] << " " << QA[k] << endl;
  }
 k+=1;
 }

}

double p5_polynomial(double x){
  double a = -0.0141149;
  double b = 5.90807;
  double c =  -8.96014;
  double d = 9.2264;
  double e = -5.8124;
  double f = 1.6976;
  
  return a*x*x*x*x*x+b*x*x*x*x+c*x*x*x+d*x*x+e*x+f;
  //return 0.125*(15*x-70*x*x*x+63*x*x*x*x*x);
   }
double argonMobilityFunc(Double_t *x, Double_t *par) {
  //Taken from eqn 21 arXiv:1508.07059v2 [physics.ins-det] 30 Jan 2016
  Double_t E=x[0];
  Double_t a0=551.6;
  Double_t a1=7953.7;
  Double_t a2=4440.43;
  Double_t a3=4.29;
  Double_t a4=43.63;
  Double_t a5=0.2053;
  Double_t T0=89;
  Double_t T=par[0];
  Double_t sqrtE=TMath::Sqrt(E);
  Double_t top=a0+a1*E+a2*E*sqrtE+a3*E*E*sqrtE;
  Double_t bottom=1+(a1/a0)*E+a4*E*E+a5*E*E*E;
  return (top/bottom)*TMath::Power(T/T0,-1.5);
}
Double_t argonDriftVelocity(Double_t E) {
  //Argon mobility \mu=W/E , E is electric field, W is drift velocity
  //Returns in cm/microsec
  double par[1] = {89};
  return argonMobilityFunc(&E,par)*E*1e3/1e6;  //1e3 kV->V and 1e6 is s->microsec
}
