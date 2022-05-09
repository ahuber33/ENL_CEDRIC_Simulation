/// ENLCEDRICSimRunAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLCEDRICSimRunAction.hh"
#include "Randomize.hh"
#include <time.h>
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "TFile.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH2I.h"
#include "TH1D.h"
#include "TAxis.h"
#include <fstream>
#include <iostream>


ENLCEDRICSimRunAction::ENLCEDRICSimRunAction(char* suff):suffixe(suff){}
ENLCEDRICSimRunAction::~ENLCEDRICSimRunAction(){}


//-----------------------------------------------------
//  BeginOfRunAction:  used to calculate the start time and
//  to set up information in the run tree.
//-----------------------------------------------------
void ENLCEDRICSimRunAction::BeginOfRunAction(const G4Run* aRun){

  //gROOT->ProcessLine("#include <vector>");

  G4String fileName = suffixe+".root";
  f = new TFile(fileName,"RECREATE");
  //f = new TFile("test.root","UPDATE");

  start = time(NULL);     //start the timer clock to calculate run times

  theRunTree = new TTree("theRunTree","Tree_Information");

  // create the branch for each event.
  // Be careful of the data structure here!  /F is a float  /I is an integer
  RunBranch = theRunTree->Branch("IncidentE", &Stats.IncidentE, "IncidentE/F");
  RunBranch = theRunTree->Branch("IncidentE_Elec_Stack1", &Stats.IncidentE_Elec_Stack1, "IncidentE_Elec_Stack1/F");
  RunBranch = theRunTree->Branch("DepositE_Elec_Stack1", &Stats.DepositE_Elec_Stack1, "DepositE_Elec_Stack1/F");
  RunBranch = theRunTree->Branch("IncidentE_Gamma_Stack1", "vector<float>", &Stats.IncidentE_Gamma_Stack1);
  RunBranch = theRunTree->Branch("DepositE_Gamma_Stack1", &Stats.DepositE_Gamma_Stack1, "DepositE_Gamma_Stack1/F");
  RunBranch = theRunTree->Branch("IncidentE_Elec_Stack2", &Stats.IncidentE_Elec_Stack2, "IncidentE_Elec_Stack2/F");
  RunBranch = theRunTree->Branch("DepositE_Elec_Stack2", &Stats.DepositE_Elec_Stack2, "DepositE_Elec_Stack2/F");
  RunBranch = theRunTree->Branch("IncidentE_Gamma_Stack2", "vector<float>", &Stats.IncidentE_Gamma_Stack2);
  RunBranch = theRunTree->Branch("DepositE_Gamma_Stack2", &Stats.DepositE_Gamma_Stack2, "DepositE_Gamma_Stack2/F");
  RunBranch = theRunTree->Branch("IncidentE_Elec_Stack3", &Stats.IncidentE_Elec_Stack3, "IncidentE_Elec_Stack3/F");
  RunBranch = theRunTree->Branch("DepositE_Elec_Stack3", &Stats.DepositE_Elec_Stack3, "DepositE_Elec_Stack3/F");
  RunBranch = theRunTree->Branch("IncidentE_Gamma_Stack3", "vector<float>", &Stats.IncidentE_Gamma_Stack3);
  RunBranch = theRunTree->Branch("DepositE_Gamma_Stack3", &Stats.DepositE_Gamma_Stack3, "DepositE_Gamma_Stack3/F");
  RunBranch = theRunTree->Branch("IncidentE_Elec_Stack4", &Stats.IncidentE_Elec_Stack4, "IncidentE_Elec_Stack4/F");
  RunBranch = theRunTree->Branch("DepositE_Elec_Stack4", &Stats.DepositE_Elec_Stack4, "DepositE_Elec_Stack4/F");
  RunBranch = theRunTree->Branch("IncidentE_Gamma_Stack4", "vector<float>", &Stats.IncidentE_Gamma_Stack4);
  RunBranch = theRunTree->Branch("DepositE_Gamma_Stack4", &Stats.DepositE_Gamma_Stack4, "DepositE_Gamma_Stack4/F");
  RunBranch = theRunTree->Branch("IncidentE_Elec_Stack5", &Stats.IncidentE_Elec_Stack5, "IncidentE_Elec_Stack5/F");
  RunBranch = theRunTree->Branch("DepositE_Elec_Stack5", &Stats.DepositE_Elec_Stack5, "DepositE_Elec_Stack5/F");
  RunBranch = theRunTree->Branch("IncidentE_Gamma_Stack5", "vector<float>", &Stats.IncidentE_Gamma_Stack5);
  RunBranch = theRunTree->Branch("DepositE_Gamma_Stack5", &Stats.DepositE_Gamma_Stack5, "DepositE_Gamma_Stack5/F");
  RunBranch = theRunTree->Branch("IncidentE_Elec_Stack6", &Stats.IncidentE_Elec_Stack6, "IncidentE_Elec_Stack6/F");
  RunBranch = theRunTree->Branch("DepositE_Elec_Stack6", &Stats.DepositE_Elec_Stack6, "DepositE_Elec_Stack6/F");
  RunBranch = theRunTree->Branch("IncidentE_Gamma_Stack6", "vector<float>", &Stats.IncidentE_Gamma_Stack6);
  RunBranch = theRunTree->Branch("DepositE_Gamma_Stack6", &Stats.DepositE_Gamma_Stack6, "DepositE_Gamma_Stack6/F");
  RunBranch = theRunTree->Branch("IncidentE_Elec_Stack7", &Stats.IncidentE_Elec_Stack7, "IncidentE_Elec_Stack7/F");
  RunBranch = theRunTree->Branch("DepositE_Elec_Stack7", &Stats.DepositE_Elec_Stack7, "DepositE_Elec_Stack7/F");
  RunBranch = theRunTree->Branch("IncidentE_Gamma_Stack7", "vector<float>", &Stats.IncidentE_Gamma_Stack7);
  RunBranch = theRunTree->Branch("DepositE_Gamma_Stack7", &Stats.DepositE_Gamma_Stack7, "DepositE_Gamma_Stack7/F");


  //set the random seed to the CPU clock
  //G4Random::setTheEngine(new CLHEP::HepJamesRandom);
  G4long seed = time(NULL);
  //G4Random::setTheSeed(seed);
  G4Random::setTheSeed(1651827053);
  G4cout << "seed = " << seed << G4endl;

  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  if (G4VVisManager::GetConcreteInstance()){
    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI->ApplyCommand("/vis/scene/notifyHandlers");
  }

  InitialiseHistos();
  for(G4int i = 0; i<Nombre_IP;i++){
    E_dep_electrons[i] = 0.;
    E_dep_gammas[i] = 0.;
    E_dep_tot[i] = 0.;
  }


}  //end BeginOfRunAction



void  ENLCEDRICSimRunAction::EcrireDistribElectrons(G4int num_IP, G4double Energie)
{
  HistoDistribElectrons[num_IP]->Fill(Energie);
}

void  ENLCEDRICSimRunAction::EcrireDistribGammas(G4int num_IP, G4double Energie)
{
  HistoDistribGammas[num_IP]->Fill(Energie);
}

void  ENLCEDRICSimRunAction::InitialiseHistos() {

  for (int i =0 ; i<Nombre_IP;i++) {
    char nom_histo[50];
    char titre[50];

    ////histo electrons
    sprintf(nom_histo,"distribution_electrons_%d",i+1);
    sprintf(titre,"Distribution Electrons IP %d",i+1);
    HistoDistribElectrons[i] = new TH1D(nom_histo,titre,1000,0,50);
    HistoDistribElectrons[i]->GetXaxis()->SetTitle("Energie(MeV)");
    HistoDistribElectrons[i]->GetYaxis()->SetTitle("dN/dE");

    ////histo gammas
    sprintf(nom_histo,"distribution_gammas_%d",i+1);
    sprintf(titre,"Distribution Gammas IP %d",i+1);
    HistoDistribGammas[i] = new TH1D(nom_histo,titre,1000,0,50);
    HistoDistribGammas[i]->GetXaxis()->SetTitle("Energie(MeV)");
    HistoDistribGammas[i]->GetYaxis()->SetTitle("dN/dE");
  }
}//fin InitialiseHistos

//-----------------------------------------------------
//  EndOfRunAction:  used to calculate the end time and
//  to write information to the run tree.
//-----------------------------------------------------
void ENLCEDRICSimRunAction::EndOfRunAction(const G4Run*aRun){

  TH1D* histo_edep_electrons = new TH1D("edep_electrons","energie deposee par des electrons",7,0.5,7.5);
  histo_edep_electrons ->GetXaxis()->SetTitle("numero de l'IP");
  histo_edep_electrons ->GetYaxis()->SetTitle("Energie deposee(keV)");
  TH1D* histo_edep_gammas = new TH1D("edep_gammas","energie deposee par des photons",7,0.5,7.5);
  histo_edep_gammas ->GetXaxis()->SetTitle("numero de l'IP");
  histo_edep_gammas ->GetYaxis()->SetTitle("Energie deposee(keV)");
  TH1D* histo_edep_tot = new TH1D("edep_totale","energie totale deposee",7,0.5,7.5);
  histo_edep_tot ->GetXaxis()->SetTitle("numero de l'IP");
  histo_edep_tot ->GetYaxis()->SetTitle("Energie deposee(keV)");

  for (G4int i =0 ; i<Nombre_IP;i++) {
    //    G4cout<<"depot alpha_electron "<<i<<" "<<E_dep_electrons[i]<<"\t depot alpha_gamma "<<i<<" "<<E_dep_gammas[i]<<G4endl;
    histo_edep_electrons->SetBinContent(i+1,E_dep_electrons[i]);
    histo_edep_gammas->SetBinContent(i+1,E_dep_gammas[i]);
    histo_edep_tot->SetBinContent(i+1,E_dep_tot[i]);
    G4cout << "Edeptot[" << i << "] = " << E_dep_tot[i] << G4endl;
  }

  //update the temp root file
  G4String fileName = suffixe+".root";
  //f = new TFile(fileName,"update");
  f->Write();
  //theRunTree->Write();

  f->Close();

  if (G4VVisManager::GetConcreteInstance()){
    G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
  }

  //display run time and write to file Rntime.out
  time_t end = time(NULL);
  G4int elapsed = end-start;
  G4cout << "Run Completed in " << elapsed/3600
  << ":" << (elapsed%3600)/60 << ":"
  << ((elapsed%3600)%60) << G4endl;

  // Output the time in the file Runtime.out
  std::ofstream timeout;
  timeout.open("Runtime.out",std::ios::app);
  timeout << "Run " << aRun->GetRunID()
  << ": " <<elapsed/3600
  << ":" <<(elapsed%3600)/60
  << ":" <<((elapsed%3600)%60) << G4endl;
  timeout.close();

  G4cout<<"Leaving Run Action"<<G4endl;
}

//---------------------------------------------------------
//  For each event update the statistics in the Run tree
//---------------------------------------------------------

void ENLCEDRICSimRunAction::UpdateStatistics(RunTally aRunTally){
  Stats = aRunTally;
  theRunTree->Fill();
}
