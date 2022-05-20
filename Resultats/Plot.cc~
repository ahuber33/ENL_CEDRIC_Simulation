void Plot()
{

  TFile* file1 = new TFile("Mono_10MeV.root");
  TH1F* fe = (TH1F*)file1->Get("edep_electrons");
  TH1F* fg = (TH1F*)file1->Get("edep_gammas");
  TH1F* ft = (TH1F*)file1->Get("edep_totale");
  fe->SetLineColor(kRed);
  fg->SetLineColor(kGreen);
  ft->SetLineColor(kBlack);
  ft->Draw();
  fg->Draw("same");
  fe->Draw("same");


  float E1=0;
  float E2=0;
  float E3=0;
  float E4=0;
  float E5=0;
  float E6=0;
  float E7=0;
  float Sum1=0;
  float Sum2=0;
  float Sum3=0;
  float Sum4=0;
  float Sum5=0;
  float Sum6=0;
  float Sum7=0;
  TTree *Tree = (TTree*)file1->Get("IP");
  Tree->SetBranchAddress("DepositE_Elec_Stack1", &E1);
  Tree->SetBranchAddress("DepositE_Elec_Stack2", &E2);
  Tree->SetBranchAddress("DepositE_Elec_Stack3", &E3);
  Tree->SetBranchAddress("DepositE_Elec_Stack4", &E4);
  Tree->SetBranchAddress("DepositE_Elec_Stack5", &E5);
  Tree->SetBranchAddress("DepositE_Elec_Stack6", &E6);
  Tree->SetBranchAddress("DepositE_Elec_Stack7", &E7);
  const int Entries = Tree->GetEntries();

  TH1F* test = new TH1F("test", "test", 7, 0.5, 7.5);
  
  for(int i=0; i<Entries; i++)
    {
      Tree->GetEntry(i);
      Sum1+=E1;
      Sum2+=E2;
      Sum3+=E3;
      Sum4+=E4;
      Sum5+=E5;
      Sum6+=E6;
      Sum7+=E7;
    }

  test->SetBinContent(1, Sum1);
  test->SetBinContent(2, Sum2);
  test->SetBinContent(3, Sum3);
  test->SetBinContent(4, Sum4);
  test->SetBinContent(5, Sum5);
  test->SetBinContent(6, Sum6);
  test->SetBinContent(7, Sum7);

  test->SetLineColor(kCyan);
  test->Draw("same");
}
