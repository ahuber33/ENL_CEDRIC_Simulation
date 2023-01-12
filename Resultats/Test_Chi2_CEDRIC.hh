TGraph* Table_Chi2_01pc;
TGraph* Table_Chi2_1pc;
TGraph* Table_Chi2_2pc;
TGraph* Table_Chi2_5pc;
TGraph* Table_Chi2_10pc;
TGraph* Table_Chi2_20pc;
TGraph* Table_Chi2_30pc;
TGraph* Table_Chi2_50pc;
TGraph* Table_Chi2_90pc;
TH1D* h;
TFile* file;
TH1F* Init = new TH1F("Init", "Init", 1001, 0, 2000);
TH1F* P1= new TH1F("Plaque1", "Plaque1", 1001, 0, 2000);
TH1F* P2= new TH1F("Plaque2", "Plaque2", 1001, 0, 2000);
TH1F* P3= new TH1F("Plaque3", "Plaque3", 1001, 0, 2000);
TH1F* P4= new TH1F("Plaque4", "Plaque4", 1001, 0, 2000);
TH1F* P5= new TH1F("Plaque5", "Plaque5", 1001, 0, 2000);
TH1F* P6= new TH1F("Plaque6", "Plaque6", 1001, 0, 2000);
TH1F* P7= new TH1F("Plaque7", "Plaque7", 1001, 0, 2000);


void Reset()
{
  Init->Reset();
  P1->Reset();
  P2->Reset();
  P3->Reset();
  P4->Reset();
  P5->Reset();
  P6->Reset();
  P7->Reset();
}


void Init_Table_Chi2()
{
  TFile* file = new TFile("Table_Chi2_0.001.root");
  Table_Chi2_01pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_0.01.root");
  Table_Chi2_1pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_0.02.root");
  Table_Chi2_2pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_0.05.root");
  Table_Chi2_5pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_0.1.root");
  Table_Chi2_10pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_0.2.root");
  Table_Chi2_20pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_0.3.root");
  Table_Chi2_30pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_0.5.root");
  Table_Chi2_50pc = (TGraph*)file->Get("Graph");

  file = new TFile("Table_Chi2_0.9.root");
  Table_Chi2_90pc = (TGraph*)file->Get("Graph");

}

TH1D* Histo_PSL(const char* filename)
{
  file = new TFile(filename, "update");
  h = (TH1D*)file->Get("PSL vs IP");

  int n = h->GetNbinsX();

  //delete file;

  // for (int i=1; i<=n; i++)
  //   {
  //     h->SetBinError(i, sqrt(h->GetBinContent(i)));
  //   }

  h->SetDirectory(nullptr);
  file->Close();
  //delete file;

  return h;

}


double Chi2(TH1D* a, TH1D* b, bool b_Chi2)
{
  double Chi2, res[7];
  int ndf, igood;

  double p = a->Chi2TestX(b, Chi2, ndf, igood, "WW P", res);

  cout << "p = " << p << endl;
  cout << "Chi2 = " << Chi2 << endl;

  if(b_Chi2 == true) return Chi2;
  
  else return p;
}

float Calcul_Chi2(TH1D* O, TH1D* C, vector<float> v, double norm)
{
  int n = C->GetNbinsX();
  //  cout << "n = " << n << endl;


  float Chi2=0;
  float sigma=0;

  for (int i=1; i<=n; i++)
    {
      sigma = v.at(i-1);
      cout << "O[" << i << "] = " << O->GetBinContent(i) << endl;
      cout << "C[" << i << "] = " << C->GetBinContent(i)/norm << endl;
      cout << "sigma[" << i << "] = " << sigma << endl; 
      Chi2+= ((O->GetBinContent(i) - C->GetBinContent(i)/norm) * (O->GetBinContent(i) - C->GetBinContent(i)/norm)) / (C->GetBinContent(i)/norm + (sigma*sigma));
      //Chi2+= ((O->GetBinContent(i) - C->GetBinContent(i)/norm) * (O->GetBinContent(i) - C->GetBinContent(i)/norm)) / (C->GetBinContent(i)/norm + O->GetBinContent(i)); //O->GetBinContent(i) = sqrt(O->..)*sqrt(O->..) [sigma²]
    }


  return Chi2;


}



vector<float> Calcul_Sigma(vector <TH1F*> O)
{

  vector<float> Sigma;
  Sigma.clear();

  for (int i=1; i<=7; i++)
    {
      cout << "sigma[" << i << "] = " << O[i]->GetStdDev() << endl; 
      Sigma.push_back(O[i]->GetStdDev());
    }

  return Sigma;


}


vector <TH1F*> Remplissage_Observable_Plaque(const char* name, int n)
{
  Reset();
  TH1D* h[n];
  vector<TH1F*> P;
  P.clear();
  char filename[100];
  
  P.push_back(Init);
  P.push_back(P1);
  P.push_back(P2);
  P.push_back(P3);
  P.push_back(P4);
  P.push_back(P5);
  P.push_back(P6);
  P.push_back(P7);

    for (int i=1; i<=n; i++)
    {
      sprintf(filename, name, i);
      //cout << "filename = " << filename << endl;
      h[i]= Histo_PSL(filename);
      if(i==1) h[i]->Draw();
      else h[i]->Draw("same");
      //cout << h[i]->GetBinContent(1) << endl;
      P[1]->Fill(h[i]->GetBinContent(1));
      P[2]->Fill(h[i]->GetBinContent(2));
      P[3]->Fill(h[i]->GetBinContent(3));
      P[4]->Fill(h[i]->GetBinContent(4));
      P[5]->Fill(h[i]->GetBinContent(5));
      P[6]->Fill(h[i]->GetBinContent(6));
      P[7]->Fill(h[i]->GetBinContent(7));
    }

    return P;

}



TGraph* Graph_Chi2(vector<TH1F*> P, vector<float> sigma, float Emin, float Emax, float step, float norm)
{
  int npoints = ((Emax - Emin)/step)+1;
  float E[npoints];
  float Chi2[npoints];
  float num = Emin;
  char filename[100];
  TH1D* h[npoints];
  TH1D* hh;;

    for (int i=0; i<npoints; i++)
    {
      sprintf(filename,"Exp_%0.1fMeV_10M.root", num);
      cout << "filename = " << filename << endl;
      h[i]= Histo_PSL(filename);
      hh=Histo_PSL("5MeV_Incert_PSL_files_10M/a_10.root");
      E[i] = num;
      Chi2[i] = Calcul_Chi2(hh, h[i], sigma, norm);
      cout << "Chi2[" << num << "MeV] = " << Chi2[i] << endl;      
      num+=0.1;
     }

    TGraph* g = new TGraph(npoints, E, Chi2);

    return g;
}



void Plot_Horizontale_Line(int ddl, TGraph* alpha, float Emin, float Emax, EColor Color)
{
  float Value = alpha->Eval(ddl);
  cout << "Value = " << Value << endl;
  
  TLine* l1 = new TLine(Emin, Value, Emax, Value);
  l1->SetLineColor(Color);
  l1->SetLineWidth(3);
  l1->Draw("same");
  
}


void Interval_Temperature_Chi2(float E[], TGraph* g, float Value_Chi2, float Emin, float Emax)
{
  bool flag1 = false;
  bool flag2 = false;

    for (float i=Emin; i <= Emax; i+=0.01)
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

      return E;
  
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



void Plot_Vertical_Line(TGraph* g, int ddl, TGraph* alpha, float Emin, float Emax, EColor Color)
{
  float E[2];
  float Value = alpha->Eval(ddl);
  Interval_Temperature_Chi2(E, g, Value, Emin, Emax);


  TLine* l1b = new TLine(E[0], 0, E[0], Value);
  l1b->SetLineColor(Color);
  l1b->SetLineWidth(3);
  l1b->Draw("same");

  TLine* l1t = new TLine(E[1], 0, E[1], Value);
  l1t->SetLineColor(Color);
  l1t->SetLineWidth(3);
  l1t->Draw("same");
}


float Largeur_puits_Chi2(TGraph* g, int ddl, TGraph* alpha, float Emin, float Emax)
{
  float Value = alpha->Eval(ddl);
  float E[2];
  Interval_Temperature_Chi2(E, g, Value, Emin, Emax);
  float Largeur = E[1] - E[0];

  cout << "Largeur puits = " << Largeur << endl;

  return Largeur;

}


TGraph* Graph_Evolution_Chi2(const char* filename, int n, float Emin , float Emax, float step, float norm)
{
  vector<TH1F*> P = Remplissage_Observable_Plaque(filename, n);
  vector<float> sigma = Calcul_Sigma(P);

  TGraph* g = Graph_Chi2(P, sigma, Emin, Emax, step, norm);
  float a = GetMinimumChi2Value(g);

  return g;
}


void Plot_Graph_Evolution_Chi2(TGraph* g, int ddl, TGraph* alpha, float Emin, float Emax, EColor Color)
{
  new TCanvas;
  g->Draw();
  g->SetMarkerStyle(20);

  Plot_Horizontale_Line(ddl, alpha, Emin, Emax, Color);
  Plot_Vertical_Line(g, ddl, alpha, Emin, Emax, Color);
}



