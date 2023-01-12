#include "Test_Chi2_CEDRIC.hh"

void Test_Chi2_CEDRIC()
{
  Init_Table_Chi2();
  TGraph* Table_Chi2 = Table_Chi2_01pc;
  const int ddl =6;

  int n =20;
  float step =0.1;
  float Emin = 2.9;
  float Emax = 10;


  TGraph* g_5MeV = Graph_Evolution_Chi2("5MeV_Incert_PSL_files_10M/a_%d.root", n, Emin, Emax, step, 1);
  float Largeur_5MeV = Largeur_puits_Chi2(g_5MeV, ddl, Table_Chi2, Emin, Emax);
  Plot_Graph_Evolution_Chi2(g_5MeV, ddl, Table_Chi2, Emin, Emax, kRed);

  // TGraph* f;
  // float L[30];
  // float X[30];
  // int k=0;

  // for (int i=1; i<=n; i++)
  //   {
  //     f = Graph_Evolution_Chi2("5MeV_Incert_PSL_files_1M/a_%d.root", i, Emin, Emax, step, 10.);

  //     if(i>1)
  // 	{
  // 	  L[k] = Largeur_puits_Chi2(f, ddl, Table_Chi2, Emin, Emax);
  // 	  //L[k] = GetMinimumChi2Value(f);
  // 	  X[k] = i;
  // 	  k++;
  // 	  cout << "i = " << i << endl;
  // 	}
  //   }


  // TGraph* g_1M = new TGraph(k, X, L);

  // k=0;

  //   for (int i=1; i<=n; i++)
  //   {
  //     f = Graph_Evolution_Chi2("5MeV_Incert_PSL_files_2M/a_%d.root", i, Emin, Emax, step, 5.);
      
  //     if(i>1)
  // 	{
  // 	  //L[k] = Largeur_puits_Chi2(f, ddl, Table_Chi2, Emin, Emax);
  // 	  L[k] = GetMinimumChi2Value(f);
  // 	  X[k] = i;
  // 	  k++;
  // 	  cout << "i = " << i << endl;
  // 	}
  //   }

  //   TGraph* g_2M = new TGraph(k, X, L);



    // k=0;
    
    // for (int i=1; i<=n; i++)
    //   {
    //   f = Graph_Evolution_Chi2("5MeV_Incert_PSL_files_500k/a_%d.root", i, Emin, Emax, step, 20.);
      
    //   if(i>1)
    // 	{
    // 	  //L[k] = Largeur_puits_Chi2(f, ddl, Table_Chi2, Emin, Emax);
    // 	  L[k] = GetMinimumChi2Value(f);
    // 	  X[k] = i;
    // 	  k++;
    // 	  cout << "i = " << i << endl;
    // 	}
    // }

    // TGraph* g_500k = new TGraph(k, X, L);



    // k=0;
    
    // for (int i=1; i<=n; i++)
    //   {
    //   f = Graph_Evolution_Chi2("5MeV_Incert_PSL_files_100k/a_%d.root", i, Emin, Emax, step, 100.);
      
    //   if(i>1)
    // 	{
    // 	  //L[k] = Largeur_puits_Chi2(f, ddl, Table_Chi2, Emin, Emax);
    // 	  L[k] = GetMinimumChi2Value(f);
    // 	  X[k] = i;
    // 	  k++;
    // 	  cout << "i = " << i << endl;
    // 	}
    // }

    // TGraph* g_100k = new TGraph(k, X, L);



    // k=0;
    
    // for (int i=1; i<=n; i++)
    //   {
    //   f = Graph_Evolution_Chi2("5MeV_Incert_PSL_files_5M/a_%d.root", i, Emin, Emax, step, 2.);
      
    //   if(i>1)
    // 	{
    // 	  //L[k] = Largeur_puits_Chi2(f, ddl, Table_Chi2, Emin, Emax);
    // 	  L[k] = GetMinimumChi2Value(f);
    // 	  X[k] = i;
    // 	  k++;
    // 	  cout << "i = " << i << endl;
    // 	}
    // }

    // TGraph* g_5M = new TGraph(k, X, L);



    // k=0;
    
    // for (int i=1; i<=n; i++)
    //   {
    //   f = Graph_Evolution_Chi2("5MeV_Incert_PSL_files_10M/a_%d.root", i, Emin, Emax, step, 1.);
      
    //   if(i>1)
    // 	{
    // 	  //L[k] = Largeur_puits_Chi2(f, ddl, Table_Chi2, Emin, Emax);
    // 	  L[k] = GetMinimumChi2Value(f);
    // 	  X[k] = i;
    // 	  k++;
    // 	  cout << "i = " << i << endl;
    // 	}
    // }

    // TGraph* g_10M = new TGraph(k, X, L);


    

    // new TCanvas;

    // g_1M->Draw("");
    // g_1M->SetLineColor(kRed);
    // g_1M->Draw("same");
    // g_1M->SetLineColor(kCyan);
    // g_5M->Draw("same");
    // g_5M->SetLineColor(kGreen);
    // g_10M->Draw("same");
    // g_10M->SetLineColor(kGreen);
    // g_500k->Draw("same");
    // g_500k->SetLineColor(kBlue);
    // g_100k->Draw("same");
    // g_100k->SetLineColor(kBlack);
    
}
