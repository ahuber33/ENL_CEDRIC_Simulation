void Fit_Temperature_elec_to_photons()
{
  gStyle->SetOptFit(1011);
  
  TFile* file = new TFile("Electrons_Exp_10MeV_Tantale_ELFIE.root");
  TTree* Tree = (TTree*)file->Get("IP");
  int Entries = Tree->GetEntries();
  std::vector<float>* E=0;
  Tree->SetBranchAddress("EBremExit", &E);
  TH1F* Brem = new TH1F("Brem", "Brem", 500, 0, 100);

  TF1* fit = new TF1("fit", "[0]*exp(-x/[1])+[2]*exp(-x/[3])", 1, 100);
  fit->SetParameter(0, 1e5);
  fit->SetParameter(1, 0.6);
  fit->SetParameter(2, 1e3);
  fit->SetParameter(3, 1.3);

  for (int i=0; i<Entries; i++)
    {
      Tree->GetEntry(i);
      for (int j=0; j<E->size(); j++)
	{
	  Brem->Fill(E->at(j));
	}
    }

  Brem->Draw();
  Brem->Fit("fit");
  
  float x[6]={1.02, 1.73, 1.96, 2.24, 2.49, 6.34};
  float ex[6]={0.04, 0.03, 0.02, 0.02, 0.02, 0.05};
  float y[6]={1, 2, 2.5, 3, 3.5, 10};
  float ey[6]={0, 0, 0, 0, 0, 0};

  TGraphErrors* g = new TGraphErrors(6, x,y,ex,ey);

  new TCanvas;
  g->Draw();
  g->Fit("pol1");

  
  
}
