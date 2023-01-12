void Chi2()
{

  ifstream file("Table_Chi2.txt");
  int n=10;
  float ddl[n], Chi2_995[n], Chi2_990[n], Chi2_975[n], Chi2_950[n], Chi2_900[n], Chi2_750[n], Chi2_500[n], Chi2_250[n], Chi2_100[n];
  
  for (int i=0; i<=n; i++)
    {
      if(i==0)
	{
	  file >> ddl[i] >> Chi2_995[i] >> Chi2_990[i]>> Chi2_975[i]>> Chi2_950[i]>> Chi2_900[i]>> Chi2_750[i]>> Chi2_500[i]>> Chi2_250[i]>> Chi2_100[i];
	}
      
      if(i>0)
	{
	  file >> ddl[i-1] >> Chi2_995[i-1] >> Chi2_990[i-1]>> Chi2_975[i-1]>> Chi2_950[i-1]>> Chi2_900[i-1]>> Chi2_750[i-1]>> Chi2_500[i-1]>> Chi2_250[i-1]>> Chi2_100[i-1];

	  cout << ddl[i-1] << " " << Chi2_995[i-1] << " " << Chi2_990[i-1]<< " " << Chi2_975[i-1] << " " << Chi2_950[i-1] << " " << Chi2_900[i-1] << " " << Chi2_750[i-1] << " " << Chi2_500[i-1] << " " << Chi2_250[i-1] << " " << Chi2_100[i-1] << endl;
	}
    }
  file.close();
  
  TGraph* graph_995 = new TGraph(n-1, ddl, Chi2_995);
  TGraph* graph_990 = new TGraph(n-1, ddl, Chi2_990);
  TGraph* graph_975 = new TGraph(n-1, ddl, Chi2_975);
  TGraph* graph_950 = new TGraph(n-1, ddl, Chi2_950);
  TGraph* graph_900 = new TGraph(n-1, ddl, Chi2_900);
  TGraph* graph_750 = new TGraph(n-1, ddl, Chi2_750);
  TGraph* graph_500 = new TGraph(n-1, ddl, Chi2_500);
  TGraph* graph_250 = new TGraph(n-1, ddl, Chi2_250);
  TGraph* graph_100 = new TGraph(n-1, ddl, Chi2_100);


  TFile file_Chi2_995("Table_Chi2_995.root", "RECREATE");
  graph_995->Write();
  file_Chi2_995.Close();

  TFile file_Chi2_990("Table_Chi2_990.root", "RECREATE");
  graph_990->Write();
  file_Chi2_990.Close();
  
  TFile file_Chi2_975("Table_Chi2_975.root", "RECREATE");
  graph_975->Write();
  file_Chi2_975.Close();
  
  TFile file_Chi2_950("Table_Chi2_950.root", "RECREATE");
  graph_950->Write();
  file_Chi2_950.Close();
  
  TFile file_Chi2_900("Table_Chi2_900.root", "RECREATE");
  graph_900->Write();
  file_Chi2_900.Close();
  
  TFile file_Chi2_750("Table_Chi2_750.root", "RECREATE");
  graph_750->Write();
  file_Chi2_750.Close();
  
  TFile file_Chi2_500("Table_Chi2_500.root", "RECREATE");
  graph_500->Write();
  file_Chi2_500.Close();
  
  TFile file_Chi2_250("Table_Chi2_250.root", "RECREATE");
  graph_250->Write();
  file_Chi2_250.Close();
  
  TFile file_Chi2_100("Table_Chi2_100.root", "RECREATE");
  graph_100->Write();
  file_Chi2_100.Close();

}
