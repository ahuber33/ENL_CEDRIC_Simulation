#include <iostream>
#include <fstream>

using namespace std;


TH1F* histo(const char* filename, const int nlines, int nstart, int nend)
{

  TH1F* histo = new TH1F(filename, filename, nlines, nstart, nend);
  ifstream file(filename);
  float E[nlines], N[nlines];
  float Sum=0;

  for (int i=0; i<nlines; i++)
    {
      file >> E[i] >> N[i];
      //      cout << E[i] << " " << N[i] << endl;
      histo->SetBinContent(i, N[i]);
      if(N[i] >0){Sum+=N[i];}
      }
  file.close();

  cout << "Sum [" << filename << "] = " << Sum << endl;
  
  return histo;
}


TGraph* graph(const char* filename, const int nlines, float factor_E, float factor_N)
{

  ifstream file(filename);
  float E[nlines], N[nlines];
  float Sum=0;

  for (int i=0; i<nlines; i++)
    {
      file >> E[i] >> N[i];
      E[i] = E[i]*factor_E;
      N[i] = N[i]*factor_N;
      Sum+=N[i];
            cout << E[i] << " " << N[i] << endl;
    }
  file.close();

  cout << "Sum =" << Sum << endl;

  TGraph* graph = new TGraph(nlines, E, N);

  return graph;
}

void Plot()
{

  const int nlines = 2500;
   TGraph* scan1 = graph("scan08_1_SPECTR.txt", nlines, 0.001, 1);
  TH1F* scan1_h = histo("scan08_1_SPECTR.txt", nlines, 556, 49513);
  //TGraph* scan2 = graph("scan08_2_SPECTR.txt", nlines, 0.001, 1);
  //  TGraph* scan5 = graph("scan08_5_SPECTR.txt", nlines, 1, 1);
  scan1->Draw();
  //scan1_h->Draw("same");
  //scan2->Draw("");
  //scan2->Scale(1./6.44505e+09);
  //scan5->Draw("same");
  scan1->SetLineColor(kBlue);
  //scan2->SetLineColor(kBlue);
  //scan5->SetLineColor(kBlack);
  //scan1_h->Rebin(4);

  TFile* file = new TFile("Gamma_Scan08_1_10M.root");
  //TFile* file = new TFile("Test.root");
  float E;
  TTree *Tree = (TTree*)file->Get("IP");
  Tree->SetBranchAddress("IncidentE", &E);
  const int Entries = Tree->GetEntries();

  float PosX[Entries];
  float PosY[Entries];
  TH1F* h = new TH1F("test", "test", 2500, 0.556, 49.513);

  for(int i=0; i<Entries; i++)
  {
    Tree->GetEntry(i);
    h->Fill(E);
  }

  h->Draw("same");
  h->SetLineColor(kCyan);
  h->Scale(5.92726e+09/h->Integral());

  auto legend1 = new TLegend(0.1,0.7,0.48,0.9);
  legend1->AddEntry(scan1,"Scan08_1 Data","pe");
  legend1->AddEntry(h,"Spectre simulation","pe");
  legend1->Draw();

  // ofstream ofile("Spectre_scan08_1.txt");
  // float a;

  // cout << "Nlines = " << scan1->GetN() << endl;
  
   //  for(int i =0; i<scan1->GetN(); i++)
   // {
      
   //   a= scan1->GetPointY(i);
   //   if (a<0){a=0.;}
   //   if (i%10 ==1 && i< 2400)
   //     {
   // 	 ofile <<scan1->GetPointX(i) << " " << a/5.92726e+09 << endl;
   //     }
   //   if (i>2400)
   //    ofile <<scan1->GetPointX(i) << " " << a/5.92726e+09 << endl;
   // }
  
}
