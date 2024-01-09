#include "Matrice_CEDRIC.hh"

void Matrice_CEDRIC()
{
  Init_Table_Chi2();
  FillMatriceHP();
  TFile file1("CEDRIC_MatriceHP_gamma.root", "RECREATE");
  MatriceHP->Write();

  FillMatrice();
  TFile file2("CEDRIC_Matrice_gamma.root", "RECREATE");
  Matrice->Write();
  
  TGraph* Table_Chi2 = Table_Chi2_995pc;
  const int ddl =6;
  REF = Histo_PSL("Data_Gamma_Exp/Exp_0.1MeV_10M.root");
  // TGraph* g;
  // g = Graph_Chi2_HP(REF);
  // g->Draw();
  
  
  new TCanvas;
  MatriceHP->Draw("colz");

  new TCanvas;
  Matrice->Draw("colz");

  // DrawIncidentE("Data_Gamma_Exp/Exp_1.0MeV_10M.root");
  // Histo_Exp(1.0);
  // Fit->Draw("same");
  // Fit->SetLineColor(kRed);
  // Fit->Scale(IncidentE->Integral()/Fit->Integral());
   


  //################################################################################
  //################################################################################
  //##############################PARTIE FIT MINUIT#################################
  //################################################################################
  //################################################################################
  float start_0 = 1e8;
  float step_0 = 1e7;
  float low_0 = 1e3;
  float up_0 = 1e12;
  
  float start_1 = 10;//10
  float step_1 = 0.1;
  float low_1 = 0; //-1
  float up_1 = 30; //30
  
  // FIT_MINUIT(start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1);

  
  new TCanvas;
  TGraphErrors* a = FOM_Spectro_FIT(0.1, 20, start_0, step_0, low_0, up_0, start_1, step_1, low_1, up_1);


  TPad *pad1;
  TPad *pad2;
  TCanvas *canvas1 = new TCanvas("FIT", "FIT", 0, 10, 1200, 800);
  canvas1->cd();
  pad1 = new TPad("pad1", "", 0, 0.34, 1, 1);
  pad2 = new TPad("pad2", "", 0., 0., 1, 0.33);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  float x[2] = {0, 20};
  float y[2] = {0, 20};
  auto line = new TGraph(2, x , y);
  a->SetFillColor(kRed);
  a->SetLineColor(kRed);
  a->SetLineWidth(3);
  a->SetFillStyle(3001);
  //a->Draw("a3");
  a->Draw("a3PL");
  line->Draw("Lsame");
  line->SetLineColor(kCyan);
  line->SetLineWidth(3);
  pad2->cd();

  int n = a->GetN();
  float ecart_x[n];
  float ecart_y[n];
  float e_ecart_x[n];
  float e_ecart_y[n];


  for (int i =0; i<n; i++)
    {
      ecart_x[i] = a->GetPointX(i);
      ecart_y[i] = (a->GetPointY(i) - a->GetPointX(i) ) / a->GetPointX(i);
      e_ecart_x[i] = 0.1/2;
      e_ecart_y[i] = a->GetErrorY(i) / a->GetPointX(i);
      
    }

  auto ega = new TGraphErrors(n, ecart_x, ecart_y, e_ecart_x, e_ecart_y);
  ega->Draw("a3PL");
  ega->SetFillColor(kRed);
  ega->SetLineColor(kRed);
  ega->SetLineWidth(3);
  ega->SetFillStyle(3001);
  float xx[2] = {0, 20};
  float yy[2] = {0, 0};
  auto line1 = new TGraph(2, xx , yy);
  line1->Draw("Lsame");
  line1->SetLineColor(kCyan);
  line1->SetLineWidth(3);
  

  
  // TGraphAsymmErrors* b = FOM_Spectro(Table_Chi2, ddl, 0.5, 20., 1);
  // //b->Draw("");
  // pad1->cd();
  // b->SetFillColor(kBlue);
  // b->SetLineColor(kBlue);
  // b->SetLineWidth(3);
  // b->SetFillStyle(3003);
  // b->Draw("same3");
  
}
