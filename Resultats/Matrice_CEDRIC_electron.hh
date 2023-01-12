TH1D* PSL_REF;
TH1D* Edep_REF;
TH1D* h;
TFile* file;
TH2F* Matrice = new TH2F("matrice", "matrice", 7, 0.5, 7.5, 100, 0, 100);
TH2F* MatriceHP = new TH2F("matriceHP", "matriceHP", 7, 0.5, 7.5, 100, 0, 10);
TH1F* IncidentE = new TH1F("IncidentE", "IncidentE", 100, 0, 100);
TH1D* PSL_Rec = new TH1D ("PSL_Rec", "PSL_Rec", 7, 0.5, 7.5);
TH1F *Fit = new TH1F("fit", "fit", 200, 0, 200);
TH1F *FitHP = new TH1F("fitHP", "fitHP", 100, 0, 10);
TH1D* REF;
float Chi2=0;
float Chi2_store=0;
float Chi2_HP_store=0;
float Chi2_HPbis_store=0;
double A=0;
double err_A=0;
double E0=0;
double err_E0=0;
double NEvents=0;
TGraph* Table_Chi2_995pc;
TGraph* Table_Chi2_990pc;
TGraph* Table_Chi2_975pc;
TGraph* Table_Chi2_950pc;
TGraph* Table_Chi2_900pc;
TGraph* Table_Chi2_750pc;
TGraph* Table_Chi2_500pc;
TGraph* Table_Chi2_250pc;
TGraph* Table_Chi2_100pc;


void Init_Table_Chi2()
{
  TFile* file = new TFile("Table_Chi2_995.root");
  Table_Chi2_995pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_990.root");
  Table_Chi2_990pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_975.root");
  Table_Chi2_975pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_950.root");
  Table_Chi2_950pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_900.root");
  Table_Chi2_900pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_750.root");
  Table_Chi2_750pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_500.root");
  Table_Chi2_500pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_250.root");
  Table_Chi2_250pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_100.root");
  Table_Chi2_100pc = (TGraph*)file->Get("Graph");

}

double NumberOfEntries(const char* filename)
{
  TFile* file = new TFile(filename);
  TTree* Tree = (TTree*)file->Get("IP");
  int Entries = Tree->GetEntries();

  file->Close();

  return Entries;
}



TH1D* Histo_PSL(const char* filename)
{
  file = new TFile(filename, "update");
  PSL_REF = (TH1D*)file->Get("PSL vs IP");
  Edep_REF = (TH1D*)file->Get("edep_totale_eff");
  Edep_REF->Scale(0.001);
  PSL_REF->Scale(1/(3.1415927*7*7));

  int n = PSL_REF->GetNbinsX();
  NEvents = NumberOfEntries(filename);
  double Integral = Edep_REF->Integral();
  double Error_Edep=0;
  double Error_PSL=0;
  double Coef_PSL = 6.95E-1;

   for (int i=1; i<=n; i++)
     {
       Error_Edep = sqrt((Edep_REF->Integral(i,i)*Integral)/NEvents); //si graph Edep
       Error_PSL = (Error_Edep*Coef_PSL)/(3.1415927*7*7); // si graph PSL
       Edep_REF->SetBinError(i, Error_Edep);
       PSL_REF->SetBinError(i, Error_PSL);
     }


  PSL_REF->SetDirectory(nullptr);
  Edep_REF->SetDirectory(nullptr);
  file->Close();
  //delete file;

  //return PSL_REF;
  return Edep_REF;

}


void FillMatriceLine(TH2F* Matrice, TH1D* PSL, int E)
{
  for (int i=1; i<=7; i++)
    {
      Matrice->SetBinContent(i, E, PSL->GetBinContent(i));
    }
}

bool Test_Fichier(const char* filename)
{

  bool fichier=true;
  file = TFile::Open(filename);
  if(!file)
    {
      fichier=false;
      //cout << "Fichier [" << filename << "] non présent" << endl;
    }
  
  return fichier;
}
  

void FillMatrice()
{
  char filename[100];

  TH1D* PSL;
  float Entries=0;
  TFile* file;
  Matrice->Reset();
  float Rapport_Surface = 1; 

  for (int i=0; i<=100; i++)
    {
      sprintf(filename,"Data_Electron_Uniform/Electron_Uniform_%d_MeV_100M.root", i);
      Entries = 100000000.;
      if(Test_Fichier(filename) == false)
	{
	  sprintf(filename,"Data_Electron_Uniform/Electron_Uniform_%d_MeV_10M.root", i);
	  Entries = 10000000.;
	  if(Test_Fichier(filename) == false)
	    {
	      sprintf(filename,"Data_Electron_Uniform/Electron_Uniform_%d_MeV_1M.root", i);
	      Entries = 1000000.;
	      if(Test_Fichier(filename) == false) continue;
	    }
	}
      //      Entries = NumberOfEntries(filename);
      cout << "Entries [" << filename << "] = " << Entries << endl;
      PSL = Histo_PSL(filename);
      //PSL->Scale(Rapport_Surface/Entries);
      PSL->Scale(Rapport_Surface/Entries);
      FillMatriceLine(Matrice, PSL, i+1);
      PSL->Reset();
    }
}


void FillMatriceHP()
{
  char filename[100];

  TH1D* PSL;
  float Entries=0;
  TFile* file;
  MatriceHP->Reset();
  float a;
  float Rapport_Surface = 1; 

  for (float i=0; i<=100; i++)
    {
      a=i/10;
      sprintf(filename,"Data_Electron_Uniform_HP/Electron_Uniform_HP_%.1f_MeV_100M.root", a);
      Entries = 100000000.;
      cout << filename << endl;
      if(Test_Fichier(filename) == false)
	{
	  sprintf(filename,"Data_Electron_Uniform_HP/Electron_Uniform_HP_%.1f_MeV_10M.root", a);
	  Entries = 10000000.;
	  if(Test_Fichier(filename) == false) continue;
	}
      //      Entries = NumberOfEntries(filename);
      cout << "Entries [" << filename << "] = " << Entries << endl;
      PSL = Histo_PSL(filename);
      PSL->Scale(Rapport_Surface/Entries);
      FillMatriceLine(MatriceHP, PSL, i+1);
      PSL->Reset();
    }
}


void DrawIncidentE(const char* filename)
{
  IncidentE->Reset();
  TFile* file = new TFile(filename);
  TTree* Tree = (TTree*)file->Get("IP");
  int Entries = Tree->GetEntries();
  cout << "Entries [" << filename << "] = " << Entries << endl;
  float E=0;
  Tree->SetBranchAddress("IncidentE", &E);

  for (int i=0; i<Entries; i++)
    {
      Tree->GetEntry(i);
      IncidentE->Fill(E);
    }

  new TCanvas;
  IncidentE->Draw();
}



void Calcul_Chi2(TH1D* O, TH1D* C)
{
  Chi2=0;
  int n = C->GetNbinsX();
  //  cout << "n = " << n << endl;

  //O->Scale(C->Integral()/O->Integral());

  float sigma=0;

  for (int i=1; i<=n; i++)
    {
      sigma = C->GetBinError(i);
      //Chi2+= ((O->GetBinContent(i) - C->GetBinContent(i)) * (O->GetBinContent(i) - C->GetBinContent(i)) / (C->GetBinContent(i)));
      if(C->GetBinContent(i) !=0 && sigma !=0)
	{
	  Chi2+= ((O->GetBinContent(i) - C->GetBinContent(i)) * (O->GetBinContent(i) - C->GetBinContent(i))) / (C->GetBinContent(i)+ (sigma*sigma));

	}

      // cout << "\nO[" << i << "] = " << O->GetBinContent(i) << endl;
      // cout << "C[" << i << "] = " << C->GetBinContent(i) << endl;
      // cout << "sigma[" << i << "] = " << sigma << endl;
      // cout << "Chi 2 = " << Chi2 << endl;
    }

}


void Calcul_Chi2_norm(TH1D* O, TH1D* C)
{
  Chi2=0;
  int n = C->GetNbinsX();
  //  cout << "n = " << n << endl;

  O->Scale(C->Integral()/O->Integral());

  float sigma=0;

  for (int i=1; i<=n; i++)
    {
      //cout << "O[" << i << "] = " << O->GetBinContent(i) << endl;
      //cout << "C[" << i << "] = " << C->GetBinContent(i) << endl;
      sigma = C->GetBinError(i);
      //cout << "sigma = " << sigma << endl;
      //Chi2+= ((O->GetBinContent(i) - C->GetBinContent(i)) * (O->GetBinContent(i) - C->GetBinContent(i)) / (C->GetBinContent(i)));
      if(C->GetBinContent(i) !=0 && sigma !=0)
	{
	  Chi2+= ((O->GetBinContent(i) - C->GetBinContent(i)) * (O->GetBinContent(i) - C->GetBinContent(i))) / (C->GetBinContent(i) + (sigma*sigma));
	  //cout << "Chi2 = " << Chi2 << endl;
	}

    }

}



void Histo_Exp(float E)
{
  TF1* f1 = new TF1("f1", "exp(-x/[0])", 0, 100);
  f1->SetParameter(0, E);
  Fit->Reset();

  for(int i=0; i<1000000; i++)
    {
      Fit->Fill(f1->GetRandom());
    }


}



void Histo_Exp_HP(float E)
{
  TF1* f1 = new TF1("f1", "exp(-x/[0])", 0, 100);
  f1->SetParameter(0, E);
  FitHP->Reset();

  for(int i=0; i<1000000; i++)
    {
      FitHP->Fill(f1->GetRandom());
    }


}



void Histo_Exp_test(float A, float E)
{
  TF1* f1 = new TF1("f1", "sqrt([1])*x*exp([0]-x/[1])", 0, 100);
  f1->SetParameter(0, A);
  f1->SetParameter(1, E);
  Fit->Reset();

  f1->Draw("same");
  f1->SetLineColor(kRed);


}


void Reconstruction_PSL()
{
  PSL_Rec->Reset();
  
  PSL_Rec->SetLineColor(kRed);

  for (int i=1; i<100; i++)
    {
      for (int j=1; j<=7; j++)
	{
	  PSL_Rec->SetBinContent(j, PSL_Rec->GetBinContent(j) + Fit->GetBinContent(i)*Matrice->GetBinContent(j, i));
	}
    }

}


void Reconstruction_PSL_HP()
{
  PSL_Rec->Reset();
  
  PSL_Rec->SetLineColor(kRed);

  for (int i=1; i<100; i++)
    {
      for (int j=1; j<=7; j++)
	{
	  PSL_Rec->SetBinContent(j, PSL_Rec->GetBinContent(j) + FitHP->GetBinContent(i)*MatriceHP->GetBinContent(j, i));
	}
    }

}


TGraph* Graph_Chi2(TH1D* REF)
{
  int npoints=0;
  float E[300];
  float tabChi2[300];

    for (float i=0.1; i<30; i+=0.2)
    {
      Histo_Exp(i);
      Reconstruction_PSL();
      Calcul_Chi2_norm(PSL_Rec, REF);
      E[npoints] = i;
      tabChi2[npoints] = Chi2;
      //cout << "Chi2[" << i << "MeV] = " << tabChi2[npoints] << endl;      
      npoints++;
     }

    TGraph* g = new TGraph(npoints, E, tabChi2);

    return g;
}


TGraph* Graph_Chi2_HP(TH1D* REF)
{
  int npoints=0;
  float E[300];
  float tabChi2[300];

    for (float i=0.00001; i<10; i+=0.1)
    {
      Histo_Exp_HP(i);
      Reconstruction_PSL_HP();
      Calcul_Chi2_norm(PSL_Rec, REF);
      E[npoints] = i/1;
      tabChi2[npoints] = Chi2;
      cout << "\nChi2[" << i << "MeV] = " << tabChi2[npoints] << endl;
      npoints++;
     }

    TGraph* g = new TGraph(npoints, E, tabChi2);

    return g;
}



void Interval_Temperature_Chi2(float E[], TGraph* g, float Value_Chi2)
{
  bool flag1 = false;
  bool flag2 = false;

    for (float i=1; i <= 30; i+=0.1)
    {
      if(g->Eval(i) < Value_Chi2 && flag1 ==false)
	{
	  E[0] = (i-0.01);
	  flag1=true;
	  cout << "E1 = " << E[0] << endl;
	}

      if (g->Eval(i) > Value_Chi2 && flag1 ==true && flag2==false)
	{
	  E[1] = i;
	  flag2 =true;
	  cout << "E2 = " << E[1] << endl;
	}
    }
  
}



void Plot_Vertical_Line(TGraph* g, int ddl, TGraph* alpha, EColor Color)
{
  float E[2];
  float Value = alpha->Eval(ddl);
  Interval_Temperature_Chi2(E, g, Value);


  TLine* l1b = new TLine(E[0], 0, E[0], Value);
  l1b->SetLineColor(Color);
  l1b->SetLineWidth(3);
  l1b->Draw("same");

  TLine* l1t = new TLine(E[1], 0, E[1], Value);
  l1t->SetLineColor(Color);
  l1t->SetLineWidth(3);
  l1t->Draw("same");
}


void Plot_Horizontale_Line(int ddl, TGraph* alpha, EColor Color)
{
  float Value = alpha->Eval(ddl);
  cout << "Value = " << Value << endl;
  
  TLine* l1 = new TLine(1, Value, 30, Value);
  l1->SetLineColor(Color);
  l1->SetLineWidth(3);
  l1->Draw("same");
  
}


void Plot_Graph_Evolution_Chi2(TGraph* g, int ddl, TGraph* alpha, EColor Color)
{
  new TCanvas;
  g->Draw();
  g->SetMarkerStyle(20);

  Plot_Horizontale_Line(ddl, alpha, Color);
  Plot_Vertical_Line(g, ddl, alpha, Color);
}



vector<float> Largeur_puits_Chi2(TGraph* g, int ddl, TGraph* alpha)
{
  float Value = alpha->Eval(ddl);
  float E[2];
  vector<float>Interval;
  Interval_Temperature_Chi2(E, g, Value);
  //float Largeur = E[1] - E[0];

  //cout << "Largeur puits = " << Largeur << endl;
  cout << "Interval puits = [" << E[0] << " ; " << E[1] << "] " << endl;
  Interval.push_back(E[0]);
  Interval.push_back(E[1]);
  

  //return Largeur;
  return Interval;

}


float GetMinimumChi2Value(TGraph* g)
{
  float Value = 10000;
  
  for (int i=0; i<g->GetN(); i++)
    {
      if(g->GetPointY(i)< Value) Value = g->GetPointY(i);
    }


  cout << "Value Min = " << Value << endl; 

  return Value;

}



float GetEnergieMinimumChi2Value(TGraph* g)
{
  float Value = 100000;
  float E=0;
  
  for (int i=0; i<g->GetN(); i++)
    {
      if(g->GetPointY(i)< Value)
	{
	  Value = g->GetPointY(i);
	  E = g->GetPointX(i);
	}
    }


  cout << "Energie Value Min = " << E << endl; 

  return E;

}



TGraphAsymmErrors* FOM_Spectro(TGraph* alpha, int ddl, float Emin, float Emax, float step)
{
  char filename[100];
  int npoints = ((Emax - Emin)/step)+1;
  float x[npoints];
  float ex_low[npoints];
  float ex_up[npoints];
  float y[npoints];
  float ey_low[npoints];
  float ey_up[npoints];
  float num = Emin;
  TH1D* REF;
  TGraph* g;
  float Min=0;
  vector<float>Largeur;


    for (int i=0; i<npoints; i++)
    {
      sprintf(filename,"Data_Electron_Exp/Electron_Exp_%0.1fMeV_10M.root", num);
      if(Test_Fichier(filename) == false)
	{
	  sprintf(filename,"Data_Electron_Exp/Electron_Exp_%0.1fMeV_10M.root", num);
	}
      cout << "\nfilename = " << filename << endl;
      REF = Histo_PSL(filename);
      g = Graph_Chi2(REF);
      Largeur.clear();
      Largeur = Largeur_puits_Chi2(g, ddl, alpha);
      x[i] = num;
      ex_low[i] = step/2;
      ex_up[i] = step/2;
      y[i] = GetEnergieMinimumChi2Value(g);
      ey_low[i] = y[i] - Largeur.at(0);
      ey_up[i] = Largeur.at(1) - y[i];
      
      num+=step;
     }

    auto ga = new TGraphAsymmErrors(npoints, x, y, ex_low, ex_up, ey_low, ey_up);

    return ga;
  
}


Double_t fitFunc(float x, Double_t* par)
{
  Double_t PDF =0.0;
  PDF = exp(par[0]-(x/1)/par[1]);
  // cout << "x = " << x << endl;
  // cout << "par 0 =" << par[0] << endl;
  // cout << "par 1 =" << par[1] << endl;
  // cout << "PDF = " << PDF << endl;

  return PDF;

}


Double_t fitFuncHP(float x, Double_t* par)
{
  Double_t PDF =0.0;
  PDF = exp(par[0]-(x/10)/par[1]);
  // cout << "x = " << x << endl;
  // cout << "par 0 =" << par[0] << endl;
  // cout << "par 1 =" << par[1] << endl;
  // cout << "PDF = " << PDF << endl;

  return PDF;

}



void fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
  PSL_Rec->Reset();
  
  for (int i=1; i<=100; i++)
    {
      for (int j=1; j<=7; j++)
	{
	  PSL_Rec->SetBinContent(j, PSL_Rec->GetBinContent(j) + fitFunc(i-0.5, par)*Matrice->GetBinContent(j, i));
	}
    }



  Calcul_Chi2(PSL_Rec, REF);
  f = Chi2;
  //cout << "A = " << par[0] << endl;
  //cout << "E0 = " << par[1] << endl;
  //cout << "Chi2 = " << Chi2 << endl;

}


void fcnHP(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
  PSL_Rec->Reset();
  
  for (int i=1; i<=100; i++)
    {
      for (int j=1; j<=7; j++)
	{
	  PSL_Rec->SetBinContent(j, PSL_Rec->GetBinContent(j) + fitFuncHP(i-0.5, par)*MatriceHP->GetBinContent(j, i));
	}
    }



  Calcul_Chi2(PSL_Rec, REF);
  f = Chi2;
  //cout << "A = " << par[0] << endl;
  //cout << "E0 = " << par[1] << endl;
  //cout << "Chi2 = " << Chi2 << endl;

}



void FIT_MINUIT(float start_0, float step_0, float low_0, float up_0, float start_1, float step_1, float low_1, float up_1)
{
  TMinuit *gMinuit = new TMinuit(2);  //initialize TMinuit with a maximum of 4 params
  gMinuit->SetFCN(fcn);

  Double_t arglist[10];
  Int_t ierflg = 0;
  
  arglist[0] = 1;
  gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);
  
  // Set starting values and step sizes for parameters
  static Double_t vstart[2] = {100, 1};
  static Double_t step[2] = {10.0 , 0.1};
  gMinuit->mnparm(0, "A", start_0, step_0, low_0, up_0, ierflg);
  gMinuit->mnparm(1, "E0", start_1, step_1, low_1, up_1, ierflg);
  
  // Now ready for minimization step
  arglist[0] = 500;
  arglist[1] = 1.;

  //  gMinuit->mnexcm("CALL FCN", arglist ,1,ierflg);
  gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);
  
  // Print results
  Double_t amin,edm,errdef;
  Int_t nvpar,nparx,icstat;
  gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);


  //  new TCanvas;
  PSL_Rec->Draw();
  REF->Draw("same");
  REF->SetLineColor(kBlack);
  PSL_Rec->SetLineColor(kRed);

  gMinuit->GetParameter(0, A, err_A);
  gMinuit->GetParameter(1, E0, err_E0);
  cout << "A = " << A << " +- " << err_A << endl;
  cout << "E0 = " << E0 << " +- " << err_E0 << endl;
  cout << "Chi2 = " << Chi2 << endl;
  cout << "Fit status = " << gMinuit->GetStatus() << endl;
}


void FIT_MINUIT_HP(float start_0, float step_0, float low_0, float up_0, float start_1, float step_1, float low_1, float up_1)
{
  TMinuit *gMinuit = new TMinuit(2);  //initialize TMinuit with a maximum of 4 params
  gMinuit->SetFCN(fcnHP);

  Double_t arglist[10];
  Int_t ierflg = 0;
  
  arglist[0] = 1;
  gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);
  
  // Set starting values and step sizes for parameters
  static Double_t vstart[2] = {100, 1};
  static Double_t step[2] = {10.0 , 0.1};
  gMinuit->mnparm(0, "A", start_0, step_0, low_0, up_0, ierflg);
  gMinuit->mnparm(1, "E0", start_1, step_1, low_1, up_1, ierflg);
  
  // Now ready for minimization step
  arglist[0] = 500;
  arglist[1] = 1.;

  //  gMinuit->mnexcm("CALL FCN", arglist ,1,ierflg);
  gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);
  
  // Print results
  Double_t amin,edm,errdef;
  Int_t nvpar,nparx,icstat;
  gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);


  //new TCanvas;
  PSL_Rec->Draw();
  REF->Draw("same");
  REF->SetLineColor(kBlack);
  PSL_Rec->SetLineColor(kRed);

  gMinuit->GetParameter(0, A, err_A);
  gMinuit->GetParameter(1, E0, err_E0);
  cout << "A = " << A << " +- " << err_A << endl;
  cout << "E0 = " << E0 << " +- " << err_E0 << endl;
  cout << "Chi2 = " << Chi2 << endl;
  cout << "Fit status = " << gMinuit->GetStatus() << endl;
}



TGraphErrors* FOM_Spectro_FIT(float Emin, float Emax, float start_0, float step_0, float low_0, float up_0, float start_1, float step_1, float low_1, float up_1)
{
  char filename[100];
  int npoints = ((Emax - Emin)/0.1)+1;
  float x[npoints];
  float ex[npoints];
  float y[npoints];
  float ey[npoints];
  float num = Emin;



    for (int i=0; i<npoints; i++)
    {
      sprintf(filename,"Data_Electron_Exp/Electron_Exp_%0.1fMeV_100M.root", num);
      if(Test_Fichier(filename) == false)
	{
	  sprintf(filename,"Data_Electron_Exp/Electron_Exp_%0.1fMeV_10M.root", num);
	}
      
      cout << "filename = " << filename << endl;
      REF = Histo_PSL(filename);
      FIT_MINUIT(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1);
      //if(Chi2<0.5)Chi2=10000;
      Chi2_store=Chi2;
      FIT_MINUIT_HP(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1);
      if(Chi2<0.5)Chi2=10000;
      Chi2_HP_store=Chi2;
      FIT_MINUIT_HP(start_0, step_0, low_0, up_0, 0.5, step_1, low_1, 1.5);
      //if(Chi2<0.5)Chi2=10000;
      Chi2_HPbis_store=Chi2;

      if(Chi2_store < Chi2_HP_store && Chi2_store < Chi2_HPbis_store) FIT_MINUIT(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1);
      if(Chi2_HP_store < Chi2_store && Chi2_HP_store < Chi2_HPbis_store) FIT_MINUIT_HP(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1);
      if(Chi2_HPbis_store < Chi2_store && Chi2_HPbis_store < Chi2_HP_store) FIT_MINUIT_HP(start_0, step_0, low_0, up_0, 0.5, step_1, low_1, 1.5);
      x[i] = num;
      ex[i] = 0.1/2;
      y[i] = E0;
      ey[i] = err_E0;
      
      num+=0.1;
     }

    auto ga = new TGraphErrors(npoints, x, y, ex, ey);

    return ga;
  
}
